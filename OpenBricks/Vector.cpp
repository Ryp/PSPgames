#include "Vector.h"

Vector::Vector(float vx, float vy)
{
  x = vx;
  y = vy;
}

Vector::Vector(const Vector& other)
{
  x = other.x;
  y = other.y;
}

Vector::~Vector() {}

Vector& Vector::operator=(const Vector& other)
{
  x = other.x;
  y = other.y;
  return *this;
}

Vector& Vector::operator+=(const Vector& other)
{
  x += other.x;
  y += other.y;
  return *this;
}

Vector Vector::operator+(const Vector& other)
{
  return Vector(x + other.x, y + other.y);
}

float Vector::operator*(const Vector& other)
{
  return (x * other.x + y * other.y);
}

void Vector::set(const Vector& other)
{
  x = other.x;
  y = other.y;
}
