#ifndef __RANDGENERATOR_H__
#define __RANDGENERATOR_H__

#include <stdio.h>
#include <stdlib.h>

#include <pspkernel.h>
#include <pspdebug.h>

#include <oslib/oslib.h>

class Randgenerator
{
public:
  Randgenerator();
  int rand(int lo, int size);
private:
  SceKernelUtilsMt19937Context ctx_;
};

#endif