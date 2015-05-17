#include "Tower.h"

std::list<Enemy>* Tower::_enemylist = 0;

Tower::Tower(int x, int y) : GraphicObject(x, y)
{
  _angle = 0;
  _level = 1;
  _is_level_max = false;
}

Tower::~Tower() {}

void Tower::registerEnemyList(std::list<Enemy>* list)
{
  _enemylist = list;
}

float Tower::getAngle()
{
  return _angle;
}


void Tower::levelUp()
{
  if (!_is_level_max) {
    ++_level;
    if (_level == TOWER_MAX_LEVEL) {
      _is_level_max = true;
    }
  }
}

bool Tower::isLevelMax()
{
  return _is_level_max;
}