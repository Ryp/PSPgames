#include "GraphicObject.h"

GraphicObject::GraphicObject(float x, float y)
{
  _pos.x = x;
  _pos.y = y;
}

GraphicObject::~GraphicObject() {}

bool GraphicObject::operator<(const GraphicObject& g) const
{
  if (_pos.y < g.getPosY()) {
    return true;
  }
  else if (_pos.y > g.getPosY()) {
    return false;
  }
  else {
    if (_pos.x < g.getPosX()) {
      return true;
    } else {
      return false;
    }
  }
}

float GraphicObject::getPosX() const
{
  return _pos.x;
}

float GraphicObject::getPosY() const
{
  return _pos.y;
}
