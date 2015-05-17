#include "Particle.h"

Particle::Particle(int t, float m, float x, float y, float vx, float vy) : pos(x, y), v(vx, vy)
{
  mass = m;
  type = t;
}
