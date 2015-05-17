#include "Menu.h"
#include "ScoreBoard.h"

Menu::Menu()
{
  _ft = oslLoadFontFile("font/font.oft");
  oslSetFont(_ft);
  //Load textures
  _background = oslLoadImageFilePNG((char*)"media/menu_background.png", OSL_IN_RAM, OSL_PF_8888);
  _tile = oslLoadImageFilePNG((char*)"media/tile.png", OSL_IN_RAM, OSL_PF_8888);
  oslSetImageFrameSize(_tile, Game::BrickSize, Game::BrickSize);
  //Load sounds
  _switch = oslLoadSoundFile("sfx/shortbip.wav", OSL_FMT_NONE);
  _validate = oslLoadSoundFile("sfx/validate.wav", OSL_FMT_NONE);
  //Create items
  //Main menu
  _speedBar = new ProgressBar(1, 10, MenuOffsetX + 43, MenuOffsetY + MenuItemSpacingY * 2 + 4);
  _levelBar = new ProgressBar(1, 10, MenuOffsetX + 43, MenuOffsetY + MenuItemSpacingY * 3 + 4);
  _modeText = new Text("TEXT", MenuOffsetX + 38, MenuOffsetY + MenuItemSpacingY);
  _modeText->setColor(RGBA(255, 255, 255, 0));
  _menus[Main] = new SelectList();
  _menus[Main]->items[0] = new Text("New Game", MenuOffsetX, MenuOffsetY);
  _menus[Main]->items[1] = new Text("Mode:", MenuOffsetX, MenuOffsetY + MenuItemSpacingY);
  _menus[Main]->items[1]->addChild(_modeText);
  _menus[Main]->items[2] = new Text("Speed", MenuOffsetX, MenuOffsetY + MenuItemSpacingY * 2);
  _menus[Main]->items[2]->addChild(_speedBar);
  _menus[Main]->items[3] = new Text("Level", MenuOffsetX, MenuOffsetY + MenuItemSpacingY * 3);
  _menus[Main]->items[3]->addChild(_levelBar);
  _menus[Main]->items[4] = new Text("Hiscores", MenuOffsetX, MenuOffsetY + MenuItemSpacingY * 4);
  _menus[Main]->items[5] = new Text("Options", MenuOffsetX, MenuOffsetY + MenuItemSpacingY * 5);
  _menus[Main]->items[6] = new Text("Quit", MenuOffsetX, MenuOffsetY + MenuItemSpacingY * 6);
  _menus[Main]->items[_menus[Main]->getCurrentItem()]->setFocus(true);
  //Option menu
  for (int i = 0; i < 7; ++i) {
    _optSwitch[i] = new Switch(MenuOffsetX + OptSwitchOffsetX, MenuOffsetY + MenuItemSpacingY * i);
    _optSwitch[i]->setState(true);
  }
  _menus[Option] = new SelectList();
  _menus[Option]->items[0] = new Text("Clear blur", MenuOffsetX, MenuOffsetY + MenuItemSpacingY * 0);
  _menus[Option]->items[0]->addChild(_optSwitch[0]);
  _menus[Option]->items[1] = new Text("Grid", MenuOffsetX, MenuOffsetY + MenuItemSpacingY * 1);
  _menus[Option]->items[1]->addChild(_optSwitch[1]);
  _menus[Option]->items[2] = new Text("Piece shadow", MenuOffsetX, MenuOffsetY + MenuItemSpacingY * 2);
  _menus[Option]->items[2]->addChild(_optSwitch[2]);
  _menus[Option]->items[3] = new Text("Score updates", MenuOffsetX, MenuOffsetY + MenuItemSpacingY * 3);
  _menus[Option]->items[3]->addChild(_optSwitch[3]);
  _menus[Option]->items[4] = new Text("Show next piece", MenuOffsetX, MenuOffsetY + MenuItemSpacingY * 4);
  _menus[Option]->items[4]->addChild(_optSwitch[4]);
  _menus[Option]->items[5] = new Text("Bright blocks", MenuOffsetX, MenuOffsetY + MenuItemSpacingY * 5);
  _menus[Option]->items[5]->addChild(_optSwitch[5]);
  _menus[Option]->items[6] = new Text("Soft-drop", MenuOffsetX, MenuOffsetY + MenuItemSpacingY * 6);
  _menus[Option]->items[6]->addChild(_optSwitch[6]);
  _menus[Option]->items[_menus[Option]->getCurrentItem()]->setFocus(true);
  //Hiscores
  _menus[Hiscores] = new SelectList();
  _menus[Hiscores]->items[0] = new Text("Classic", MenuOffsetX, MenuOffsetY);
  _menus[Hiscores]->items[0]->addChild(new ScoreBoard(ScoreBoardOffsetX, ScoreBoardOffsetY));
  _menus[Hiscores]->items[1] = new Text("Garbage", MenuOffsetX, MenuOffsetY + MenuItemSpacingY);
  _menus[Hiscores]->items[1]->addChild(new ScoreBoard(ScoreBoardOffsetX, ScoreBoardOffsetY));
  _menus[Hiscores]->items[_menus[Hiscores]->getCurrentItem()]->setFocus(true);
  //Configure menu
  readOptFile();
  _fadeStatus = FadingIn;
  _fadeAlpha = 0xff;
  _currentMenu = Main;
  setMode(Classic); //setMode() calls _items-dependant functions
  setMenuAutoRepeat();
  //FIXME showIntro();
}

Menu::~Menu()
{
  oslDeleteFont(_ft);
  oslDeleteSound(_validate);
  oslDeleteSound(_switch);
  oslDeleteImage(_background);
  oslDeleteImage(_tile);
  for (std::map<int, SelectList*>::iterator it = _menus.begin(); it != _menus.end(); ++it) {
    delete (*it).second;
  }
}

void Menu::update(OSL_CONTROLLER* pad)
{
  //Update ms status
  _msPresent = isMemoryStickPresent();
  //Compute fades
  if (_fadeStatus == FadingIn) {
    _fadeAlpha -= 4;
    if (_fadeAlpha <= 0) {
      _fadeAlpha = 0;
      _fadeStatus = FadedIn;
    }
  }
  if (_fadeStatus == FadingOut) {
    _fadeAlpha += 4;
    if (_fadeAlpha >= 0xff) {
      _fadeAlpha = 0xff;
      _fadeStatus = FadedOut;
    }
  }
  int currentItem = _menus[_currentMenu]->getCurrentItem();
  //Manage background controls
  if (pad->pressed.select)
    _em.switchAttrac();
  _em.moveAttracPt(pad->analogX / 20, pad->analogY / 20);
  //Test for input
  if (pad->pressed.down || pad->pressed.R) {
    oslPlaySound(_switch, 2);
    _menus[_currentMenu]->selectNextItem();
  }
  if (pad->pressed.up || pad->pressed.L) {
    oslPlaySound(_switch, 2);
    _menus[_currentMenu]->selectPreviousItem();
  }
  if (_currentMenu == Main) {
    if (pad->pressed.right) {
      if (currentItem == 2) {_speedBar->addValue(1);}
      if (currentItem == 3) {_levelBar->addValue(1);}
    }
    if (pad->pressed.left) {
      if (currentItem == 2) {_speedBar->addValue(-1);}
      if (currentItem == 3) {_levelBar->addValue(-1);}
    }
    if (pad->pressed.cross) {
      oslPlaySound(_validate, 1);
      if (currentItem == 0) {
        startGame();
      }
      if (currentItem == 1) {
        if (_mode < Game::GameModes - 1) {
          ++_mode;
        } else {
          _mode = 0;
        }
        setMode(_mode);
      }
      if (currentItem == 4 && _msPresent) {
        _currentMenu = Hiscores;
      }
      if (currentItem == 5) {
        _currentMenu = Option;
        readOptFile();
      }
      if (currentItem == 6) {
        _fadeStatus = FadingOut;
        osl_quit = true;
      }
    }
  }
  else if (_currentMenu == Option) {
    if (pad->pressed.cross) {
      oslPlaySound(_validate, 1);
      _optSwitch[currentItem]->switchState();
    }
    if (pad->pressed.circle) {
      oslPlaySound(_switch, 2);
      _currentMenu = Main;
      writeOptFile();
    }
  }
  else if (_currentMenu == Hiscores) {
    if (pad->pressed.cross) {
      oslPlaySound(_validate, 1);
    }
    if (pad->pressed.circle) {
      oslPlaySound(_switch, 2);
      _currentMenu = Main;
    }
  }
  //Update items
  _menus[_currentMenu]->update();
  //Update background animation
  _em.update();
}

void Menu::render()
{
  oslStartDrawing();
  oslClearScreen(RGB(0, 0, 0));
  //Render background
  oslDrawImage(_background);
  /* FIXME render particules
  for (std::vector<Particle*>::iterator it = _em._particules.begin(); it != _em._particules.end(); ++it) {
    drawImageFrameXY(_tile, (*it)->type, (*it)->pos.x, (*it)->pos.y);
  }*/
  //Menu space
  oslDrawFillRect(0, 0, 140, 272 , 0x8f000000);
  oslDrawLine(140, 0, 140, 272, VerticalLineColor);
  //Draw cursor
  int currentItem = _menus[_currentMenu]->getCurrentItem();
  oslDrawGradientRect(0, MenuOffsetY + MenuItemSpacingY * currentItem - 1, MenuOffsetX + 140, MenuOffsetY + MenuItemSpacingY * currentItem + 15, CursorColorUp, CursorColorUp & 0x00ffffff, CursorColorDown, CursorColorDown & 0x00ffffff);
  //Render items
  _menus[_currentMenu]->render();
  //Draw ms warning
  if (!_msPresent) {
    oslSetTextColor(0xff0000ff);
    oslDrawFillRect(0, 257, 480, 272, 0x2f0000ff);
    oslDrawString(170, 257, "WARNING: ms unplugged");
  }
  //Draw fade mask
  oslDrawFillRect(0, 0, 480, 272 , _fadeAlpha << 24);
  oslEndDrawing();
}

void Menu::startGame()
{
  _game.newGame(_mode, _speedBar->getValue(), _levelBar->getValue());
  int skip = 0;
  OSL_CONTROLLER* pad;
  while (!osl_quit && !_game.isEnded()) {
    if (!skip) {
      pad = oslReadKeys();
      _game.update(pad);
      _game.render();
    }
    oslEndFrame();
    skip = oslSyncFrame();
  }
  setMenuAutoRepeat();
}

void Menu::showIntro()
{
  OSL_IMAGE* intro = oslLoadImageFilePNG((char*)"media/intro.png", OSL_IN_RAM, OSL_PF_8888);
  int skip = 0;
  int t = 0;
  int a = 0xff;
  while (t < 192) {
    if (!skip) {
      //Fade
      if (t < 128) {
        a -= 4;
        if (a < 0) {
          a = 0;
        }
      }
      if (t > 128) {
        a += 4;
        if (a > 255) {
          a = 255;
        }
      }
      //Draw
      oslStartDrawing();
      oslDrawImage(intro);
      oslDrawFillRect(0, 0, 480, 272 , a << 24);
      oslEndDrawing();
      ++t;
    }
    oslEndFrame();
    skip = oslSyncFrame();
  }
  oslDeleteImage(intro);
}

void Menu::setMode(int mode)
{
  _mode = mode;
  if (_mode == Classic) {
    _modeText->setText("Classic");
    _menus[Main]->items[3]->disable();
  }
  if (_mode == Garbage) {
    _modeText->setText("Garbage");
    _menus[Main]->items[3]->enable();
  }
}

void Menu::setMenuAutoRepeat()
{
  oslSetKeyAutorepeat(OSL_KEYMASK_RIGHT|OSL_KEYMASK_LEFT, 10, 3);
}

void Menu::readOptFile()
{
  Options tmp;
  tmp = getGameConfig();
  _optSwitch[0]->setState(tmp.flags & OPT_SHOW_BLUR);
  _optSwitch[1]->setState(tmp.flags & OPT_SHOW_GRID);
  _optSwitch[2]->setState(tmp.flags & OPT_SHOW_SHADOW);
  _optSwitch[3]->setState(tmp.flags & OPT_SHOW_SCORE_UP);
  _optSwitch[4]->setState(tmp.flags & OPT_SHOW_NEXT);
  _optSwitch[5]->setState(tmp.brick_type);
  _optSwitch[6]->setState(tmp.flags & OPT_SOFT_DROP);
}

void Menu::writeOptFile()
{
  Options	tmp;

  tmp.flags = 0;
  if (_optSwitch[0]->getState()) {tmp.flags |= OPT_SHOW_BLUR;}
  if (_optSwitch[1]->getState()) {tmp.flags |= OPT_SHOW_GRID;}
  if (_optSwitch[2]->getState()) {tmp.flags |= OPT_SHOW_SHADOW;}
  if (_optSwitch[3]->getState()) {tmp.flags |= OPT_SHOW_SCORE_UP;}
  if (_optSwitch[4]->getState()) {tmp.flags |= OPT_SHOW_NEXT;}
  tmp.brick_type = _optSwitch[5]->getState();
  if (_optSwitch[6]->getState()) {tmp.flags |= OPT_SOFT_DROP;}
  writeGameConfigFile(tmp);
}
