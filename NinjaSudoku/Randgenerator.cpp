#include "Randgenerator.h"

Randgenerator::Randgenerator()
{
  sceKernelUtilsMt19937Init(&ctx_, time(NULL));
}

int Randgenerator::rand(int lo, int size)
{
  u32 rand_val = sceKernelUtilsMt19937UInt(&ctx_);
  rand_val = lo + rand_val % size;
  return (int)rand_val;
}
