#include "geometry.h"

float getVectAngle(const t_2dvect& v)
{
  return vfpu_atan2f(v.y, v.x);
}

float getVectNorm(const t_2dvect& v)
{
  return sqrt(v.x * v.x + v.y * v.y);
}

float get2VectAngle(const t_2dvect& v1, const t_2dvect& v2)
{
  return (vfpu_atan2f(v2.x, v2.y) - vfpu_atan2f(v1.x, v1.y));
}

float dot(const t_2dvect& v1, const t_2dvect& v2)
{
  return v1.x * v2.x + v1.y * v2.y;
}

float vectprod(const t_2dvect& v1, const t_2dvect& v2)
{
  return v1.x * v2.y - v1.y * v2.x;
}

void normalizeVect(t_2dvect& v)
{
  float n = getVectNorm(v);
  v.x /= n;
  v.y /= n;
}
