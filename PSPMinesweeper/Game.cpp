#include "Game.h"
#include "Ressource.h"
#include "Save.h"
#include "rules.h"

Game::Game(int x, int y, int mines, int mode, int level) : board_(x, y)
{
  getExternalData();
  //Copy function arguments
  mines_ = mines;
  mode_ = mode;
  level_ = level;
  //Initialize flags
  initFlags();
  //Initialize rules
  if (mode_ == CLASSIC) { lifes_ = 1;}
  if (mode_ == SURVIVAL) {
    switch (level_) {
      case EASY: lifes_ = EASY_LIFES;break;
      case MEDIUM: lifes_ = MEDIUM_LIFES;break;
      case HARD: lifes_ = HARD_LIFES;break;
    }
    board_.newBoard(SURVIVAL_STARTING_LENGTH, SURVIVAL_STARTING_HEIGHT);   
    mines_ = SURVIVAL_STARTING_MINES;
  }
}

Game::~Game() {}

void Game::getExternalData()
{
  sonar_ = Ressource::GetInstance()->sonar_;
  win_ = Ressource::GetInstance()->win_;
  bomb_ = Ressource::GetInstance()->bomb_;
  tile_ = Ressource::GetInstance()->tile_;
  heart_ = Ressource::GetInstance()->heart_;
  backgroundpic_ = Ressource::GetInstance()->backgroundpic_;
  ltn_ = Ressource::GetInstance()->ltn_;
}

void Game::initFlags()
{
  flag_counter_ = 0;
  state_ = RUNNING;
  on_board_ = false;
  is_new_hi_ = false;
  is_started_ = false;
  is_finished_ = false;
}

void Game::generateGame()
{
  int xrand, yrand, temp_mines;
  chrono_.startTimer();
  is_started_ = true;
  temp_mines = mines_;
  while (temp_mines > 0) {
    xrand = Ressource::GetInstance()->getRandomNum(0, board_.size_.x);
    yrand = Ressource::GetInstance()->getRandomNum(0, board_.size_.y);
    //Avoid placing mine around current player cursor position
    if ((abs(xrand - cursor_.x) > 1) || (abs(yrand - cursor_.y) > 1)) {
      if (board_.cells_[xrand][yrand].value == 0) {
        board_.cells_[xrand][yrand].value = 15;
        temp_mines--;
      }
    }
  }
  //Precalculate numbers inside cells
  for (int i=0; i<board_.size_.x; i++) {
    for (int j=0; j<board_.size_.y; j++) {
      if (board_.cells_[i][j].value == 15) {
        for (int k=-1; k<2; k++) {
          for (int l=-1; l<2; l++) {
            if (((i+k) >= 0) && ((i+k) < board_.size_.x) && ((j+l) >= 0) && ((j+l) < board_.size_.y)) {
              if (board_.cells_[i+k][j+l].value != 15) {
                (board_.cells_[i+k][j+l].value)++;
              }
            }
          }
        }
      }
    }
  }
}

void Game::discoverBlankCells(int x, int y)
{
  for (int i =-1; i<2; i++) {
    for (int j =-1; j<2; j++) {
      if (((i+x) >= 0)  &&  ((i+x) < board_.size_.x)  &&  ((j+y) >= 0) && ((j+y) < board_.size_.y)) {
        if (board_.cells_[x+i][y+j].discovered == 0) {
          board_.cells_[x+i][y+j].discovered = 1;
          board_.cells_[x+i][y+j].flag = 0;
          if (board_.cells_[x+i][y+j].value == 0) {
            discoverBlankCells(x+i, y+j);
          }
        }
      }
    }
  }
}

void Game::refreshFlagCounter()
{
  flag_counter_ = 0;
  for (int i=0; i<board_.size_.x; i++) {
    for (int j=0; j<board_.size_.y; j++) {
      if (board_.cells_[i][j].flag == 1) {
        flag_counter_++;
      }
    } 
  }
}

void Game::drawImageFrameXY(OSL_IMAGE *img, int frame, int x, int y)
{
  oslSetImageFrame(img, frame);
  oslDrawImageXY(img, x ,y);
}

void Game::checkIfWin()
{
  int discovered_cells = 0, total_cells;
  total_cells = board_.size_.x * board_.size_.y;
  for (int i=0; i<board_.size_.x; i++) {
    for (int j=0; j<board_.size_.y; j++) {
      discovered_cells += board_.cells_[i][j].discovered ;
    }
  }
  if ((total_cells - discovered_cells) == mines_) {
    
    for (int i=0; i<board_.size_.x; i++) {
      for (int j=0; j<board_.size_.y; j++) {
        if (board_.cells_[i][j].value == 15) {
          board_.cells_[i][j].flag = 1;
        }
      }
    }
    oslPlaySound(win_, 2);
    onWin();
  }
}

void Game::onBoardEnded()
{
  if (mode_ == CLASSIC) {
    is_finished_ = true;
  }
  if (mode_ == SURVIVAL) {
    if (state_ == WIN) {
      if (board_.size_.x == SURVIVAL_MAX_HEIGHT) {
        is_finished_ = true;
      } else {
        //Level up
        board_.newBoard(board_.size_.x+2, board_.size_.y+2);
        mines_ += SURVIVAL_ADD_MINES;
        initFlags();
      }
    }
    if (state_ == LOSE) {
      lifes_--;
      if (lifes_ == 0) {
        is_finished_ = true;
      } else {
        //Restart board
        board_.newBoard(board_.size_.x, board_.size_.y);
        initFlags();
      }
    }
  }
}

void Game::onWin()
{
  state_ = WIN;
  chrono_.pauseTimer();
  if (((mode_ == SURVIVAL) && (board_.size_.x == SURVIVAL_MAX_HEIGHT)) || (mode_ == CLASSIC)) {
    Savemanager save;
    is_new_hi_ = save.checkHighscore(chrono_.getTimer(), level_, mode_);
  }
}

void Game::onLose()
{
  state_ = LOSE;
  chrono_.pauseTimer();
  //Show all mines
  board_.cells_[cursor_.x][cursor_.y].value = 16;
  for (int i=0; i<board_.size_.x; i++) {
    for (int j=0; j<board_.size_.y; j++) {
      if (board_.cells_[i][j].value == 15) {
        board_.cells_[i][j].discovered = true;
      }
      else {
        if (board_.cells_[i][j].flag == 1) {
          board_.cells_[i][j].value = 17;
          board_.cells_[i][j].discovered = true;
        }
      }
    }
  }
}

void Game::onCrossPressed()
{
  if ((state_ == WIN) || (state_ == LOSE)) {
    onBoardEnded();
  } else {
    if (on_board_) {
      if (!is_started_) {
        generateGame();
      }
      if (!board_.cells_[cursor_.x][cursor_.y].discovered) {
        if (board_.cells_[cursor_.x][cursor_.y].flag != 1) {
          board_.cells_[cursor_.x][cursor_.y].discovered = true;
          board_.cells_[cursor_.x][cursor_.y].flag = 0;
          if (board_.cells_[cursor_.x][cursor_.y].value == 0) { //Blank cell discovered
            oslPlaySound(sonar_, 1);
            discoverBlankCells(cursor_.x, cursor_.y);
          }
          if (board_.cells_[cursor_.x][cursor_.y].value == 15) { //Stepped on a mine
            onLose();
            oslPlaySound(bomb_, 2); //Boom
          }
        }
      }
    }
  }
  refreshFlagCounter();
}

void Game::onSquarePressed()
{
  if ((state_ != WIN) && (state_ != LOSE)) {
    if (on_board_) {
      if (is_started_) {
        if (!board_.cells_[cursor_.x][cursor_.y].discovered) {
          board_.cells_[cursor_.x][cursor_.y].flag++;
          if (board_.cells_[cursor_.x][cursor_.y].flag == 3) {
            board_.cells_[cursor_.x][cursor_.y].flag = 0;
          }
        }
      }
    }
  }
  refreshFlagCounter();
}

void Game::onPause()
{
  if ((state_ != WIN) && (state_ != LOSE)) {
    if (is_started_) {
      int skip = 0;
      OSL_CONTROLLER* pad = oslReadKeys();
      chrono_.addTimer(1);
      chrono_.pauseTimer();
      while ((!osl_quit) && (!pad->pressed.triangle)) {
        if (!skip) {
          pad = oslReadKeys();
          oslStartDrawing();
          oslDrawFillRect(0, 0, 480, 272, BLACK);
          intraFontSetStyle(ltn_, 0.7f, WHITE, BLACK, INTRAFONT_ALIGN_CENTER);
          intraFontPrint(ltn_, 240, 134, "Game paused");
          intraFontSetStyle(ltn_, 0.5f, WHITE, blinkingEffect(1, 1), INTRAFONT_ALIGN_CENTER);
          intraFontPrint(ltn_, 240, 146, "Press Triangle to resume");
          oslEndDrawing();
        }
        oslEndFrame();
        skip = oslSyncFrame();
      }
      chrono_.startTimer();
    }
  }
}

void Game::update(OSL_CONTROLLER* pad)
{
  mouse_.update(pad);
  //Is the mouse over the board
  on_board_ = board_.isOver(mouse_.getX(), mouse_.getY());
  //Calculate current pointed cell
  cursor_.x = (mouse_.getX() - board_.pos_.x) / TILE_SIZE;
  cursor_.y = (mouse_.getY() - board_.pos_.y) / TILE_SIZE;
  //Player has won ?
  if ((state_ != WIN) && (state_ != LOSE)) {
    checkIfWin();
  }
  //Verifying user input
  if (pad->pressed.square) {
    onSquarePressed();
  }
  if (pad->pressed.cross) {
    onCrossPressed();
  }
  if (pad->pressed.triangle) {
    onPause();
  }
}

void Game::display()
{
  oslDrawImage(backgroundpic_);
  //Draw each cell one by one
  for (int i=0; i<board_.size_.x; i++) {
    for (int j=0; j<board_.size_.y; j++) {
      if (board_.cells_[i][j].discovered) {
        drawImageFrameXY(tile_, board_.cells_[i][j].value, board_.pos_.x + i*TILE_SIZE, board_.pos_.y + j*TILE_SIZE);
      } else {
        drawImageFrameXY(tile_, board_.cells_[i][j].flag*2+9, board_.pos_.x + i*TILE_SIZE, board_.pos_.y + j*TILE_SIZE);
      }
    }
  }
  //Display highlighted cell if cursor is on board_
  if ((state_ != WIN) && (state_ != LOSE)) {
    if (on_board_ && !board_.cells_[cursor_.x][cursor_.y].discovered) {
      drawImageFrameXY(tile_, board_.cells_[cursor_.x][cursor_.y].flag*2+10, board_.pos_.x + cursor_.x*TILE_SIZE, board_.pos_.y + cursor_.y*TILE_SIZE);
    }
  }
  mouse_.display();
  //Info Bar
  oslDrawFillRect(0, 253, 480, 272, 0x6F000000);
  //Display clock
  if ((mode_ == SURVIVAL) || (is_started_)) {
    timeToText(chrono_.getTimer(), temp_text_);
    intraFontSetStyle(ltn_, 0.7f, ALTBLACK, BLACK, INTRAFONT_ALIGN_CENTER);
    intraFontPrint(ltn_, 240, 267, temp_text_);
  }
  //Display flag counter OR win/lose notification
  if (state_ == RUNNING) {
    intraFontSetStyle(ltn_, 0.7f, ALTBLACK, BLACK, INTRAFONT_ALIGN_LEFT);
    intraFontPrintf(ltn_, 10, 267, "Mines: %i", mines_ - flag_counter_);   
  } else {
    if (state_ == LOSE) {
      if (lifes_ == 1) {
        intraFontSetStyle(ltn_, 0.7f, RED, BLACK, INTRAFONT_ALIGN_LEFT);
        intraFontPrint(ltn_, 10, 267, "You Lose !");
      } else {
        intraFontSetStyle(ltn_, 0.7f, RED, BLACK, INTRAFONT_ALIGN_LEFT);
        intraFontPrint(ltn_, 10, 267, "Try again !");
      }
    }
    if (state_ == WIN) {
      if ((mode_ == SURVIVAL) && (board_.size_.x != SURVIVAL_MAX_HEIGHT)) {
        intraFontSetStyle(ltn_, 0.7f, GREEN, BLACK, INTRAFONT_ALIGN_LEFT);
        intraFontPrint(ltn_, 10, 267, "Good job !");
      } else {
        intraFontSetStyle(ltn_, 0.7f, GREEN, BLACK, INTRAFONT_ALIGN_LEFT);
        intraFontPrint(ltn_, 10, 267, "You Win !");
      }
      if (is_new_hi_) {
        intraFontSetStyle(ltn_, 0.7f, ALTBLACK, BLACK, INTRAFONT_ALIGN_LEFT);
        intraFontPrint(ltn_, 267, 267, "Highscore !");
      }
    }
  }
  //Display life counter if needed
  if (mode_ == SURVIVAL) {
    oslDrawImage(heart_);
    intraFontSetStyle(ltn_, 0.7f, ALTBLACK, BLACK, INTRAFONT_ALIGN_RIGHT);
    intraFontPrintf(ltn_, 193, 267, "%i", lifes_);
  }
  //Display battery life
  if (scePowerGetBatteryLifePercent() >= 0) {
    intraFontSetStyle(ltn_, 0.7f, ALTBLACK, BLACK, INTRAFONT_ALIGN_RIGHT);
    intraFontPrintf(ltn_, 470, 267, "Battery: %i%%", scePowerGetBatteryLifePercent());
  }
}

bool Game::isFinished()
{
  return is_finished_;
}
