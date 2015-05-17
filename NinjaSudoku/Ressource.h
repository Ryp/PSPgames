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
public:
  static Ressource * GetInstance();
  OSL_SOUND *click_; //Sound files pointers
  OSL_IMAGE *backgroundpic_, *bignumbers_, *grid_, *selected_, *smallnumbers_; //Image files pointers
  OSL_IMAGE *osk_numbers_, *osk_back_, *osk_selected_;
  intraFont *ltn_;
private:
  static Ressource * Instance_;
  ~Ressource();
  Ressource();
};

int blinkingEffect(int item, int flag);

#endif

