#ifndef __VECTOR_H__
#define __VECTOR_H__

class Vector
{
public:
  Vector(float vx = 0, float vy = 0);
  Vector(const Vector& other);
  virtual ~Vector();
  virtual Vector& operator=(const Vector& other);
  virtual Vector& operator+=(const Vector& other);
  virtual Vector operator+(const Vector& other);
  virtual float operator*(const Vector& other);
  void set(const Vector& other);
  float x;
  float y;
};

#endif
