#ifndef __MENU_H__
#define __MENU_H__

#include <stdio.h>
#include <stdlib.h>
#include <new>

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>

#include <oslib/oslib.h>

#include "structs.h"

class Menu
{
private:
  /**Get data from ressource loader*/ 
  void getExternalData();
  void newGame();
  void scoresMenu();
  void helpMenu();
  OSL_SOUND *click_;
  OSL_IMAGE *backgroundpic_;
  intraFont* ltn_;
  char temp_text_[40];
  coordinates size_;
  int mines_;
  int level_;
  int mode_;
  int min_mines_; 
  int max_mines_;
  int item_;
  int fade_alpha_;
  bool is_fadingin_;
  bool is_fadingout_;
public:
  Menu();
  void update(OSL_CONTROLLER* pad);
  void display();
};

#endif