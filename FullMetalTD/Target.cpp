#include "Target.h"

Target::~Target() {}

IGameObserver* Target::_observer = 0;

void Target::registerObserver(IGameObserver* obs)
{
  _observer = obs;
}

void Target::notifyDeath() const
{
  (*_observer).notifyDeath();
}

void Target::notifyArrival() const
{
  (*_observer).notifyArrival();
}
