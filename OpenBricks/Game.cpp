#include "Game.h"
#include "mp3player.h"
#include <pspaudio.h>
#include <pspaudiolib.h>

Game::Game() : _batt(BatteryIconX, BatteryIconY)
{
  _ltn = intraFontLoad("flash0:/font/ltn0.pgf", 0);
  //Init rand generator
  sceKernelUtilsMt19937Init(&_ctx, time(NULL));
  //Load sounds
  loadSound("sfx/pman.wav", LineClearBegin, 1);
  loadSound("sfx/tetris.wav", LineClearTetris, 1);
  loadSound("sfx/explode.wav", LineClearEnd, 1);
  loadSound("sfx/success.wav", LevelUp, 2);
  loadSound("sfx/shortbip.wav", RotatePiece, 4);
  loadSound("sfx/quietmove.wav", MovePiece, 3);
  loadSound("sfx/woosh1.wav", Pause, 6);
  loadSound("sfx/shortcrush.wav", PlacePiece, 5);
  //Load Drawbuffer
  _blurBuffer = oslCreateImage(480, 272, OSL_IN_VRAM, OSL_PF_8888);
  //Load textures
  _background = oslLoadImageFilePNG((char*)"media/game_background.png", OSL_IN_RAM, OSL_PF_8888);
  _tile = oslLoadImageFilePNG((char*)"media/tile_bright.png", OSL_IN_RAM, OSL_PF_8888);
  oslSetImageFrameSize(_tile, BrickSize, BrickSize);

  //Mp3 init
  pspAudioInit();
  MP3_Init(1);
  MP3_Load((char*)"sfx/intro.mp3");
  MP3_Play();
}

Game::~Game()
{
  oslDeleteImage(_background);
  oslDeleteImage(_tile);
  oslDeleteImage(_blurBuffer);
  intraFontUnload(_ltn);
  for (std::map<int, Sound>::iterator it = _sounds.begin(); it != _sounds.end(); ++it)
    oslDeleteSound((*it).second.soundData);

  //Mp3 unload
  MP3_Stop();
  MP3_FreeTune();
}

void Game::newGame(int mode, int speed, int level)
{
  //Set autorepeat
  oslSetKeyAutorepeat(OSL_KEYMASK_RIGHT | OSL_KEYMASK_LEFT | OSL_KEYMASK_DOWN, 10, 3);
  //Read game config
  _options = getGameConfig();
  _mode = mode;
  _speed = speed;
  _paused = false;
  _gameEnd = false;
  _score = 0;
  _lines = 0;
  for (int i = 0; i < GridWidth; ++i)
    for (int j = 0; j < GridHeight; ++j)
      _board[i][j] = 0;
  if (_mode == Garbage) {
    fillGarbage(level);
    _lines = GarbageModeLinesTarget;
  }
  _scoreText.clear();
  _linesCleared.clear();
  _status = Dropping;
  _tick = 0;
  _lcol = GridHeight - 1;
  _wt = 0;
  _nextPiece = getRand(7);
  popPiece();
}

bool Game::isEnded()
{
  return _gameEnd;
}

void Game::update(OSL_CONTROLLER* pad)
{
  //Test input
  //Press select to take a screenshot
//   if (pad->pressed.select) {
//     oslWriteImageFilePNG(OSL_SECONDARY_BUFFER, "screenshot.png", 0);
//   }
  //
  if ((_status == Dropping) || (_status == WaitForClear)) {
    if (pad->pressed.start) {
      _paused = !_paused;
      playSound(Pause);
    }
  }
  if (_status == Dropping) {
    if (!_paused) {
      //Manually increase/decrease speed
//       if (pad->pressed.R) {
//         ++_speed;
//       }
//       else if (pad->pressed.L) {
//         if (_speed > 1) {
//           --_speed;
//         }
//       }
      //
      if (pad->pressed.left) {
        requestLeft();
      }
      else if (pad->pressed.right) {
        requestRight();
      }
      if (pad->pressed.circle) {
        requestTurnClockwise();
      }
      else if (pad->pressed.cross) {
        requestTurnCounterClockwise();
      }
      if (pad->pressed.down) {
        requestDown(1);
      }
      else if (pad->pressed.up) {
        requestUp();
      }
    }
  }
  if (_status == Dropping) {
    if (!_paused) {
      ++_tick;
      if (_tick > getPushDownTickRate()) {
        _tick = 0;
        requestDown(0);
      }
      updateShadow();
    }
  }
  else if (_status == WaitForClear) {
    if (!_paused) {
      ++_tick;
      if (_tick > ClearTickCount) {
        _tick = 0;
        _status = Dropping;
        int lines = _linesCleared.size();
        if (lines > 0) {
          scoreLines(lines);
        }
        removeLines();
        popPiece();
      }
    }
  }
  else if (_status == Lost) {
    if (pad->pressed.cross) {
      _gameEnd = true;
    } else {
      ++_tick;
      if (_tick > 0) {
        _tick = 0;
        if (_lcol >= 0) {
          for (int i = 0; i < GridWidth; ++i) {
            _board[i][_lcol] = _currentPiece.type + 1;
          }
          --_lcol;
        }
      }
    }
  }
  else if (_status == Win) {
    if (pad->pressed.cross) {
      _gameEnd = true;
    } else {
      //Win animation
      if (_wt % 60 == 0) {
        _wt = 0;
        for (int i = 0; i < GridWidth; ++i) {
          for (int j = 0; j < GridHeight / 2 - 2; ++j) {
            _board[i][j] = getRand(7) + 1;
          }
          for (int j = GridHeight / 2 - 2; j < GridHeight / 2 + 2; ++j) {
            _board[i][j] = 0;
          }
          for (int j = GridHeight / 2 + 2; j < GridHeight; ++j) {
            _board[i][j] = getRand(7) + 1;
          }
        }
      }
      ++_wt;
    }
  }
  if (!_paused) {
    //Manage score text list
    std::list<ScoreText>::iterator it = _scoreText.begin();
    while (it != _scoreText.end()) {
      if ((*it).frame > ScoreMaxLife) {
        it = _scoreText.erase(it);
      } else {
        ++it;
      }
    }
    //Update every notification
    for (it = _scoreText.begin(); it != _scoreText.end(); ++it) {
      (*it).alpha = 240 - (*it).frame * 2;
      (*it).pos.y = ScoreTextOffsetY - (*it).frame / 6;
      ++(*it).frame;
    }
  }
}

void Game::render()
{
  char temp[40];
  oslStartDrawing();
  oslDrawImage(_background);
  //Draw board outline
  oslDrawRect(GridOffsetX - 1, GridOffsetY - 1, GridOffsetX + GridWidth * (BrickSize - 1) + 2, GridOffsetY + GridHeight *  (BrickSize - 1) + 2, BoardOutlineColor);
  //Draw board background
  oslDrawFillRect(GridOffsetX, GridOffsetY, GridOffsetX + GridWidth * (BrickSize - 1) + 1, GridOffsetY + GridHeight * (BrickSize - 1) + 1, BoardBackgroundColor);
  if (_options.flags & OPT_SHOW_GRID) {
    //Draw vertical helpers
    for (int i = 1; i < GridWidth; ++i) {
      oslDrawLine(GridOffsetX + i * (BrickSize - 1), GridOffsetY, GridOffsetX + i * (BrickSize - 1), GridOffsetY + GridHeight * (BrickSize - 1) + 1 , GridColor);
    }
    //Draw horizontal helpers
    for (int j = 1; j < GridHeight; ++j) {
      oslDrawLine(GridOffsetX, GridOffsetY + j * (BrickSize - 1), GridOffsetX + GridWidth * (BrickSize - 1) + 1, GridOffsetY + j * (BrickSize - 1), GridColor);
    }
  }
  if (!_paused)
    drawPieces();
  else {
    intraFontSetStyle(_ltn, 0.7f, 0xFFFFFFFF, 0xFF000000, 0);
    intraFontPrint(_ltn, GridOffsetX + 45, 140, "Pause");
  }
  if (_status == Win) {
    if ((_wt % 60) < 40) {
      intraFontSetStyle(_ltn, 0.7f, 0xFFFFFFFF, 0xFF000000, 0);
      intraFontPrint(_ltn, 135, 140, "You Win !");
    }
  }
  if (_options.flags & OPT_SHOW_SCORE_UP) {
    //Draw score messages
    for (std::list<ScoreText>::iterator it = _scoreText.begin(); it != _scoreText.end(); ++it) {
      intraFontSetStyle(_ltn, 0.6f, RGBA(0, 255, 0, (*it).alpha), 0xff000000, 0);
      intraFontPrint(_ltn, (*it).pos.x, (*it).pos.y, (*it).text);
    }
  }
  if (_options.flags & OPT_SHOW_NEXT) {
    //Draw next piece
    oslDrawRect(NextOffsetX - 1, NextOffsetY - 1, NextOffsetX + 4 * (BrickSize - 1) + 2, NextOffsetY + 4 * (BrickSize - 1) + 2, BoardOutlineColor);
    oslDrawFillRect(NextOffsetX, NextOffsetY, NextOffsetX + 4 * (BrickSize - 1) + 1, NextOffsetY + 4 * (BrickSize - 1) + 1, NextPieceBackgroundColor);
    Piece tmp;
    setPiece(tmp, _nextPiece, North, 0, 0, 0);
    for (int j = 0; j < 4; ++j) {
      for (int i = 0; i < 4; ++i) {
        if (tmp.array[i][j] != 0) {
          drawImageFrameXY(_tile, tmp.array[i][j] - 1, i * (BrickSize - 1) + NextOffsetX, j * (BrickSize - 1) + NextOffsetY);
        }
      }
    }
  }
  //Print scores
  intraFontSetStyle(_ltn, 0.6f, 0xFFFFFFFF, 0xFF000000, 0);
  sprintf(temp, "Score: %i", _score);
  //oslDrawString(TextOffsetX, TextOffsetY, temp);
  intraFontPrint(_ltn, TextOffsetX, TextOffsetY, temp);
  sprintf(temp, "Lines: %i", _lines);
  //oslDrawString(TextOffsetX, TextOffsetY + TextSpacingY, temp);
  intraFontPrint(_ltn, TextOffsetX, TextOffsetY + TextSpacingY, temp);
  sprintf(temp, "Speed: %i", _speed);
  //oslDrawString(TextOffsetX, TextOffsetY + TextSpacingY * 2, temp);
  intraFontPrint(_ltn, TextOffsetX, TextOffsetY + TextSpacingY * 2, temp);
  //Battery
  _batt.render();
  //oslSyncDrawing();
  if ((_status == WaitForClear) && (_tick > ClearTickCount - ClearBlurFrameCount) && !_paused) {
    if (_options.flags & OPT_SHOW_BLUR) {
      blurDrawBufferHorizontally(24, _blurBuffer);
    }
  }
  oslEndDrawing();
}

void Game::fillGarbage(int lines)
{
  for (int j = GridHeight - lines - GarbageModeMinHeight + 1; j < GridHeight; ++j) {
    for (int i = 0; i < GridWidth; ++i) {
      _board[i][j] = getRand(7) + 1;
    }
    _board[getRand(GridWidth)][j] = 0;
  }
  for (int n = 0; n < lines * GarbageModePorosity; ++n) {
    _board[getRand(GridWidth)][GridHeight - getRand(lines + GarbageModeMinHeight) - 1] = 0;
  }
}

int Game::getRand(int size)
{
  u32 rand_val = sceKernelUtilsMt19937UInt(&_ctx);
  return (int)(rand_val % size);
}

int Game::getPushDownTickRate()
{
  return (60 / _speed) + FrameOffset;
}

void Game::drawPieces()
{
  for (int j = 0; j < GridHeight; ++j) {
    bool clear = false;
    if (_status == WaitForClear) {
      for (std::list<int>::iterator it = _linesCleared.begin(); it != _linesCleared.end(); ++it) {
        if (*it == j) {
          clear = true;
        }
      }
    }
    for (int i = 0; i < GridWidth; ++i) {
      if (_board[i][j] != 0) {
        if (clear) {
          if ((_tick % 20) < 10) {
            //Draw nothing
          } else {
            drawImageFrameXY(_tile, _board[i][j] - 1, i * (BrickSize - 1) + GridOffsetX, j * (BrickSize - 1) + GridOffsetY);
          }
        } else {
          drawImageFrameXY(_tile, _board[i][j] - 1, i * (BrickSize - 1) + GridOffsetX, j * (BrickSize - 1) + GridOffsetY);
        }
      }
    }
  }
  if (_status == Dropping) {
    if (_options.flags & OPT_SHOW_SHADOW) {
      //Draw shadow
      oslSetAlpha(OSL_FX_ALPHA, PieceShadowAlpha);
      for (int j = 0; j < 4; ++j) {
        for (int i = 0; i < 4; ++i) {
          if (_shadow.array[i][j] != 0) {
            drawImageFrameXY(_tile, _shadow.array[i][j] - 1, (i + _shadow.pos.x) * (BrickSize - 1) + GridOffsetX, (j + _shadow.pos.y)  * (BrickSize - 1) + GridOffsetY);
          }
        }
      }
      oslSetAlpha(OSL_FX_RGBA, PieceShadowAlpha);
    }
    //Draw falling piece
    for (int j = 0; j < 4; ++j) {
      for (int i = 0; i < 4; ++i) {
        if (_currentPiece.array[i][j] != 0) {
          drawImageFrameXY(_tile, _currentPiece.array[i][j] - 1, (i + _currentPiece.pos.x) * (BrickSize - 1) + GridOffsetX, (j + _currentPiece.pos.y)  * (BrickSize - 1) + GridOffsetY);
        }
      }
    }
  }
}

bool Game::checkCollision(Piece& p)
{
  bool match = true; //Assume that this is true
  for (int j = 0; j < 4; ++j) {
    for (int i = 0; i < 4; ++i) {
      if (p.array[i][j] != 0) {
        if (i + p.pos.x >= GridWidth) {
          match = false;
        }
        if (i + p.pos.x < 0) {
          match = false;
        }
        if (j + p.pos.y >= GridHeight) {
          match = false;
        }
        if (j + p.pos.y < 0) {
          match = false;
        }
        if (_board[i+p.pos.x][j+p.pos.y] != 0) {
          match = false;
        }
      }
    }
  }
  return match;
}

void Game::checkForLines()
{
  _linesCleared.clear();
  for (int j = 0; j < GridHeight; ++j) {
    bool lineFull = true; //Assume that this is true
    for (int i = 0; i < GridWidth; ++i) {
      if (_board[i][j] == 0) {
        lineFull = false; //Contradiction found
      }
    }
    if (lineFull) {
      _linesCleared.push_front(j);
    }
  }
}

void Game::removeLines()
{
  for (std::list<int>::iterator line = _linesCleared.begin(); line != _linesCleared.end(); ++line) {
    for (int i = 0; i < GridWidth; ++i) {
      _board[i][*line] = 0;
    }
  }
  int n = 0;
  for (std::list<int>::iterator line = _linesCleared.begin(); line != _linesCleared.end(); ++line) {
    *line += n;
    for (int j = (*line - 1); j >= 0; --j) {
      for (int i = 0; i < GridWidth; ++i) {
        _board[i][j+1] = _board[i][j];
      }
    }
    for (int i = 0; i < GridWidth; ++i) {
      _board[i][0] = 0;
    }
    ++n;
  }
  if (_mode == Garbage) {
    if (_lines == 0) {
      _status = Win;
      _tick = 0;
    }
  }
}

void Game::scoreLines(int lines)
{
  int tmpScore;
  playSound(LineClearEnd);
  if (_mode == Classic) {
    _lines += lines;
    if (_lines >= (_speed * LinesBetweenLevels)) {
      ++_speed;
      onSpeedUp();
    }
  } else if (_mode == Garbage) {
    _lines -= lines;
    if (_lines < 0) {
      _lines = 0;
    }
  }
  lines -= 1;//Match with Tetris Enum
  int t;
  if (lines == Single) {t = 1;}
  if (lines == Double) {t = 4;}
  if (lines == Triple) {t = 8;}
  if (lines == Tetris) {t = 16;}
  tmpScore = _speed * 100 * t;
  _score += tmpScore;
  pushScoreNotification(tmpScore);
}

void Game::scoreDownBonus(int iter)
{
  int tmpScore = _speed * PushDownBonus * iter;
  _score += tmpScore;
  pushScoreNotification(tmpScore);
}

void Game::pushScoreNotification(int points)
{
  ScoreText tmp;
  sprintf(tmp.text, "+%i", points);
  tmp.alpha = 0xff;
  tmp.frame = 0;
  tmp.pos.x = ScoreTextOffsetX;
  tmp.pos.y = ScoreTextOffsetY;
  _scoreText.push_back(tmp);
}

void Game::onSpeedUp()
{
  playSound(LevelUp);
}

void Game::requestTurnClockwise()
{
  Piece tmp;
  int orientation = _currentPiece.orientation;
  if (orientation == 3) {
    orientation = 0;
  } else {
    ++orientation;
  }
  setPiece(tmp, _currentPiece.type, orientation, _currentPiece.pos.x, _currentPiece.pos.y, true);
  if (checkCollision(tmp)) {
    copyPiece(tmp, _currentPiece);
    playSound(RotatePiece);
  }
}

void Game::requestTurnCounterClockwise()
{
  Piece tmp;
  int orientation = _currentPiece.orientation;
  if (orientation == 0) {
    orientation = 3;
  } else {
    --orientation;
  }
  setPiece(tmp, _currentPiece.type, orientation, _currentPiece.pos.x, _currentPiece.pos.y, true);
  if (checkCollision(tmp)) {
    copyPiece(tmp, _currentPiece);
    playSound(RotatePiece);
  }
}

void Game::requestLeft()
{
  Piece tmp;
  setPiece(tmp, _currentPiece.type, _currentPiece.orientation, _currentPiece.pos.x - 1, _currentPiece.pos.y, 0);
  if (checkCollision(tmp)) {
    copyPiece(tmp, _currentPiece);
    playSound(MovePiece);
  }
}

void Game::requestRight()
{
  Piece tmp;
  setPiece(tmp, _currentPiece.type, _currentPiece.orientation, _currentPiece.pos.x + 1, _currentPiece.pos.y, 0);
  if (checkCollision(tmp)) {
    copyPiece(tmp, _currentPiece);
    playSound(MovePiece);
  }
}

void Game::requestDown(bool user)
{
  Piece tmp;
  setPiece(tmp, _currentPiece.type, _currentPiece.orientation, _currentPiece.pos.x, _currentPiece.pos.y + 1, 0);
  if (checkCollision(tmp)) {
    copyPiece(tmp, _currentPiece);
    if (user) {
      playSound(MovePiece);
      scoreDownBonus(1);
    }
  } else {
    placePiece();
    if ((_currentPiece.pos.x == BrickStartingPosX) && (_currentPiece.pos.y == BrickStartingPosY)) {
      _status = Lost;
      _tick = 0;
    } else {
      onReachBottom();
    }
  }
}

void Game::requestUp()
{
  Piece tmp;
  bool match;
  int n = 0;
  do {
    setPiece(tmp, _currentPiece.type, _currentPiece.orientation, _currentPiece.pos.x, _currentPiece.pos.y + 1, 0);
    match = checkCollision(tmp);
    if (match) {
      copyPiece(tmp, _currentPiece);
      ++n;
    }
  } while (match);
  if (n > 0) {
    scoreDownBonus(n);
  }
  if (_options.flags & OPT_SOFT_DROP) {
    _tick = 0;
  } else {
    onReachBottom();
  }
}

void Game::onReachBottom()
{
  placePiece();
  checkForLines();
  if (!_linesCleared.empty()) {
    _tick = 0;
    _status = WaitForClear;
    if (_linesCleared.size() == 4) {
      playSound(LineClearTetris);
    } else {
      playSound(LineClearBegin);
    }
  } else {
    popPiece();
  }
}

void Game::updateShadow()
{
  Piece tmp;
  bool match;
  copyPiece(_currentPiece, _shadow);
  do {
    setPiece(tmp, _shadow.type, _shadow.orientation, _shadow.pos.x, _shadow.pos.y + 1, 0);
    match = checkCollision(tmp);
    if (match) {
      copyPiece(tmp, _shadow);
    }
  } while (match);
}

void Game::placePiece()
{
  for (int j = 0; j < 4; ++j) {
    for (int i = 0; i < 4; ++i) {
      if (_currentPiece.array[i][j] != 0) {
        _board[i+_currentPiece.pos.x][j+_currentPiece.pos.y] = _currentPiece.array[i][j];
      }
    }
  }
  playSound(PlacePiece);
}

void Game::popPiece()
{
  setPiece(_currentPiece, _nextPiece, North, BrickStartingPosX, BrickStartingPosY, 0);
  _nextPiece = getRand(7);
  updateShadow();
}

void Game::copyPiece(const Piece& source, Piece& dest)
{
  dest.type = source.type;
  dest.orientation = source.orientation;
  dest.pos.x = source.pos.x;
  dest.pos.y = source.pos.y;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      dest.array[i][j] = source.array[i][j];
    }
  }
}

void Game::setPiece(Piece& dest, int type, int orientation, int x, int y, bool applyRotFix)
{
  dest.type = type;
  dest.orientation = orientation;
  dest.pos.x = x;
  dest.pos.y = y;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      dest.array[i][j] = 0;
    }
  }
  if (type == Bar) {
    if (dest.orientation == West) {dest.orientation = East;}
    if (dest.orientation == South) {dest.orientation = North;}
    if (dest.orientation == East) {
      for (int i = 0; i < 4; ++i) {
        dest.array[i][1] = type + 1;
      }
    }
    if (dest.orientation == North) {
      for (int j = 0; j < 4; ++j) {
        dest.array[1][j] = type + 1;
      }
    }
  }
  if (type == Quad) {
    if (dest.orientation == West) {dest.orientation = North;}
    if (dest.orientation == South) {dest.orientation = North;}
    if (dest.orientation == East) {dest.orientation = North;}
    if (dest.orientation == North) {
      for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
          dest.array[i+1][j+1] = type + 1;
        }
      }
    }
  }
  if (type == SReverse) {
    if (dest.orientation == West) {dest.orientation = East;}
    if (dest.orientation == South) {dest.orientation = North;}
    if (dest.orientation == East) {
      dest.array[2][0] = type + 1;
      dest.array[2][1] = type + 1;
      dest.array[1][1] = type + 1;
      dest.array[1][2] = type + 1;
    }
    if (dest.orientation == North) {
      dest.array[1][1] = type + 1;
      dest.array[2][1] = type + 1;
      dest.array[2][2] = type + 1;
      dest.array[3][2] = type + 1;
    }
  }
  if (type == SNormal) {
    if (dest.orientation == West) {dest.orientation = East;}
    if (dest.orientation == South) {dest.orientation = North;}
    if (dest.orientation == East) {
      dest.array[1][0] = type + 1;
      dest.array[1][1] = type + 1;
      dest.array[2][1] = type + 1;
      dest.array[2][2] = type + 1;
    }
    if (dest.orientation == North) {
      dest.array[0][2] = type + 1;
      dest.array[1][2] = type + 1;
      dest.array[1][1] = type + 1;
      dest.array[2][1] = type + 1;
    }
  }
  if (type == LNormal) {
    dest.array[1][1] = type + 1;
    if (dest.orientation == West) {
      dest.array[0][1] = type + 1;
      dest.array[2][1] = type + 1;
      dest.array[2][0] = type + 1;
    }
    if (dest.orientation == South) {
      dest.array[1][0] = type + 1;
      dest.array[1][2] = type + 1;
      dest.array[0][0] = type + 1;
    }
    if (dest.orientation == East) {
      dest.array[0][1] = type + 1;
      dest.array[2][1] = type + 1;
      dest.array[0][2] = type + 1;
    }
    if (dest.orientation == North) {
      dest.array[1][0] = type + 1;
      dest.array[1][2] = type + 1;
      dest.array[2][2] = type + 1;
    }
  }
  if (type == LReverse) {
    dest.array[2][1] = type + 1;
    if (dest.orientation == West) {
      dest.array[1][1] = type + 1;
      dest.array[3][1] = type + 1;
      dest.array[3][2] = type + 1;
    }
    if (dest.orientation == South) {
      dest.array[2][0] = type + 1;
      dest.array[2][2] = type + 1;
      dest.array[3][0] = type + 1;
    }
    if (dest.orientation == East) {
      dest.array[1][1] = type + 1;
      dest.array[3][1] = type + 1;
      dest.array[1][0] = type + 1;
    }
    if (dest.orientation == North) {
      dest.array[2][0] = type + 1;
      dest.array[2][2] = type + 1;
      dest.array[1][2] = type + 1;
    }
  }
  if (type == Pyramid) {
    dest.array[1][1] = type + 1;
    dest.array[1][0] = type + 1;
    dest.array[0][1] = type + 1;
    dest.array[2][1] = type + 1;
    dest.array[1][2] = type + 1;
    if (dest.orientation == West) {
      dest.array[0][1] = 0;
    }
    if (dest.orientation == South) {
      dest.array[1][2] = 0;
    }
    if (dest.orientation == East) {
      dest.array[2][1] = 0;
    }
    if (dest.orientation == North) {
      dest.array[1][0] = 0;
    }
  }
  //Apply fix when a piece is next to the side of the board and has to rotate
  if (applyRotFix) {
    if (dest.type == Bar) {
      if ((dest.orientation == East) && (dest.pos.x == -1)) {
        dest.pos.x = 0;
      }
      if ((dest.orientation == East) && (dest.pos.x >= GridWidth - 3)) {
        dest.pos.x = GridWidth - 4;
      }
    }
  }
}

void Game::loadSound(const char* filename, int index, int channel)
{
  Sound tmp;
  tmp.soundData = oslLoadSoundFile(filename, OSL_FMT_NONE);
  tmp.channel = channel;
  _sounds[index] = tmp;
}

void Game::playSound(int index)
{
  oslPlaySound(_sounds[index].soundData, _sounds[index].channel);
}

void Game::playSound(int index, int channel)
{
  oslPlaySound(_sounds[index].soundData, channel);
}
