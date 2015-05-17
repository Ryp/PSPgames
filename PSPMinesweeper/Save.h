#ifndef __SAVE_H__
#define __SAVE_H__

#include <stdio.h>
#include <stdlib.h>

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>

#include "structs.h"

class Savemanager
{
private:
  FILE* data_;
  scoreboard scores_;
  bool loaded_;
public:
  Savemanager();
  ~Savemanager();
  bool checkHighscore(int score, char level, char mode);
  scoreboard getHighscores();
  bool isLoaded();
};

#endif
