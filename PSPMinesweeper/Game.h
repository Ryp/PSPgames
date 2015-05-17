#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <stdlib.h>
#include <new>

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <psppower.h>

#include <oslib/oslib.h>

#include "Timer.h"
#include "Board.h"
#include "Mouse.h"
#include "structs.h"

class Game
{
private:
  /**Get data from ressource loader*/ 
  void getExternalData();
  /**Prepare flags for a new game*/
  void initFlags();
  /**Fill board according to cursor position*/
  void generateGame();
  /**Recursive algorithm for discovering connected blank cells*/
  void discoverBlankCells(int x, int y);
  /**Counter current number of flags*/
  void refreshFlagCounter();
  /**Function using oslib image tile options*/
  void drawImageFrameXY(OSL_IMAGE *img, int frame, int x, int y);
  /**Check if the player has won*/
  void checkIfWin();
  void onBoardEnded();
  void onWin();
  void onLose();
  void onCrossPressed();
  void onSquarePressed();
  void onPause();
  Board board_;
  Timer chrono_;
  Mouse mouse_;
  OSL_SOUND *sonar_, *win_, *bomb_;
  OSL_IMAGE *tile_, *heart_, *mousepic_, *backgroundpic_;
  intraFont* ltn_;
  coordinates cursor_;
  char temp_text_[40];
  int state_;
  int mode_;
  int level_;
  int mines_;
  int lifes_;
  int flag_counter_;
  bool on_board_; //Set to true if pointer is on board
  bool is_new_hi_;
  bool is_started_;
  bool is_finished_;
public:
  Game(int x, int y, int mines, int mode, int level);
  ~Game();
  void update(OSL_CONTROLLER* pad);
  void display();
  bool isFinished();
};

#endif