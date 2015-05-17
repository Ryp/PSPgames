#ifndef __MOUSE_H__
#define __MOUSE_H__

#include <stdio.h>
#include <stdlib.h>
#include <new>

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>

#include <oslib/oslib.h>

#include "structs.h"

class Mouse
{
private:
  OSL_IMAGE *mousepic_;
  int mod_;
public:
  Mouse();
  ~Mouse();
  int getX();
  int getY();
  void update(OSL_CONTROLLER* pad);
  void display();
};

#endif