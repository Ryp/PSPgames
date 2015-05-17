#ifndef __EMITTER_H__
#define __EMITTER_H__

#include "oslib/oslib.h"
#include <vector>
#include "Particle.h"
#include "Randgenerator.h"

class Emitter
{
public:
  Emitter();
  virtual ~Emitter();
  void update();
  void moveAttracPt(float x, float y);
  void switchAttrac();
  std::vector<Particle*> _particules;
  static const float AttractionForce = 1.50f;
  static const float BorderFriction = 0.90f;
private:
  bool _repulsive;
  Randgenerator _rg;
  Vector _gravity;
  Vector _attracPointPos;
  Vector _thrustResult;
};

#endif
