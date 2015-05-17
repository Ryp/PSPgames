#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Vector.h"
#include <math.h>

class Particle
{
public:
  Particle(int t, float m, float x = 0, float y = 0, float vx = 0, float vy = 0);
  int type;
  float mass;
  Vector pos;
  Vector v;
};

#endif
