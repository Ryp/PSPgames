#ifndef __RESSOURCE_H__
#define __RESSOURCE_H__

#include <stdio.h>
#include <stdlib.h>
#include <new>

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>

#include <oslib/oslib.h>

class Ressource
{
private:
  static Ressource * Instance_;
  ~Ressource();
  Ressource();
  SceKernelUtilsMt19937Context ctx_;
public:
  static Ressource * GetInstance();
  int getRandomNum(int lo, int size);
  OSL_SOUND *click_, *sonar_, *win_, *bomb_; //Sound files pointers
  OSL_IMAGE *tile_, *heart_, *mousepic_, *backgroundpic_; //Image files pointers
  intraFont *ltn_;
};

int blinkingEffect(int item, int flag);

void timeToText(int seconds, char *string);

#endif