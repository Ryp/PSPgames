#include "Emitter.h"

Emitter::Emitter() : _particules(150)
{
  _repulsive = 0;
  _gravity.x = 0.0f;
  _gravity.y = 0.02f;
  _attracPointPos.x = 300;
  _attracPointPos.y = 100;
  for (std::vector<Particle*>::iterator it = _particules.begin(); it != _particules.end(); ++it) {
    (*it) = new Particle(_rg.rand(0, 7), _rg.rand(3, 3), _rg.rand(0, 460), _rg.rand(0, 250));
  }
}

Emitter::~Emitter()
{
  for (std::vector<Particle*>::iterator it = _particules.begin(); it != _particules.end(); ++it) {
    delete (*it);
  }
}

void Emitter::update()
{
  for (std::vector<Particle*>::iterator it = _particules.begin(); it != _particules.end(); ++it) {
    //Calc forces
    float r = sqrt(pow(_attracPointPos.x - (*it)->pos.x, 2) + pow(_attracPointPos.y - (*it)->pos.y, 2));
    _thrustResult.x = -(*it)->mass * ((*it)->pos.x - _attracPointPos.x) * AttractionForce / pow(r, 2);
    _thrustResult.y = -(*it)->mass * ((*it)->pos.y - _attracPointPos.y) * AttractionForce / pow(r, 2);
    if (_repulsive)
    {
      _thrustResult.x *= -1;
      _thrustResult.y *= -1;
    }
    //Apply force
    (*it)->v += (_gravity + _thrustResult);


    //Move
    (*it)->pos += (*it)->v;
    //Check collisions
    if ((*it)->pos.x < 0) {
      (*it)->pos.x = 0;
      if ((*it)->v.x < 0) {
        (*it)->v.x *= -BorderFriction;
      } else {
        (*it)->v.x = 0;
      }
    }
    if ((*it)->pos.x > 466) {
      (*it)->pos.x = 466;
      if ((*it)->v.x > 0) {
        (*it)->v.x *= -BorderFriction;
      } else {
        (*it)->v.x = 0;
      }
    }
    if ((*it)->pos.y < 0) {
      (*it)->pos.y = 0;
      if ((*it)->v.y < 0) {
        (*it)->v.y *= -BorderFriction;
      } else {
        (*it)->v.y = 0;
      }
    }
    if ((*it)->pos.y > 258) {
      (*it)->pos.y = 258;
      if ((*it)->v.y > 0) {
        (*it)->v.y *= -BorderFriction;
      } else {
        (*it)->v.y = 0;
      }
    }
  }
}

void Emitter::moveAttracPt ( float x, float y )
{
  _attracPointPos.x += x;
  _attracPointPos.y += y;
  if (_attracPointPos.x > 480)
    _attracPointPos.x = 480;
  if (_attracPointPos.x < 1)
    _attracPointPos.x = 1;
  if (_attracPointPos.y > 272)
    _attracPointPos.y = 272;
  if (_attracPointPos.y < 1)
    _attracPointPos.y = 1;
}

void Emitter::switchAttrac()
{
  _repulsive = !_repulsive;
}
