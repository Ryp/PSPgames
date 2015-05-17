#include "Cannon.h"

Cannon::Cannon(int x, int y) : Tower(x, y)
{
  _reloadtime = 0;
  _has_target = false;
}

Cannon::~Cannon(){}

void Cannon::update()
{
  if (_reloadtime > 0) {
    _reloadtime--;
  }
  if (_has_target) {
    if (!isTargetValid()) {
      searchForEnemy();
    }
  } else {
    searchForEnemy();
  }
  if (_has_target) {
    onEnemySpotted();
  }
}

bool Cannon::isTargetValid()
{
  bool rslt = false;
  t_2dvect temp;
  float distance;
  if (!(_target->isDead() || _target->isDead())) {
    temp.x = _target->getPosX() - _pos.x;
    temp.y = _target->getPosY() - _pos.y;
    distance = getVectNorm(temp);
    if (distance < CANNON_FAR_RANGE) {
      if (distance > CANNON_CLOSE_RANGE) {
        rslt = true;
      }
    }
  }
  return rslt;
}

void Cannon::searchForEnemy()
{
  t_2dvect temp;
  float distance;
  _has_target = false;
  for (std::list<Enemy>::iterator i = _enemylist->begin(); i != _enemylist->end(); ++i) {
    if (!((*i).isDead() || (*i).isArrived())) {
      temp.x = (*i).getPosX() - _pos.x;
      temp.y = (*i).getPosY() - _pos.y;
      distance = getVectNorm(temp);
      if (distance < CANNON_FAR_RANGE) {
        if (distance > CANNON_CLOSE_RANGE) {
          _target = i;
          _has_target = true;
        }
      }
    }
  }
}

void Cannon::onEnemySpotted()
{
  //Calc tower direction and enemy direction
  t_2dvect e, t;
  e.x = (*_target).getPosX() - _pos.x;
  e.y = (*_target).getPosY() - _pos.y;
  t.x = vfpu_cosf(_angle);
  t.y = vfpu_sinf(_angle);
  if (fabs(get2VectAngle(e, t)) < 2 * CANNON_ROT_SPEED) {
    //Target set commander !
    _angle = getVectAngle(e);
    //Got ammo ?
    if (_reloadtime == 0) {
      //UNLEASHING KHAOS !!!
      (*_target).setDamage(CANNON_DAMAGE);
      _reloadtime = CANNON_RELOAD_DELAY;
    }
  } else {
    //Fuck, he's behind me !
    if (vectprod(e, t) > 0) {
      //Turn one way...
      _angle = vfpu_fmodf(_angle - CANNON_ROT_SPEED, 2*M_PI);
    } else {
      //...Or the other
      _angle = vfpu_fmodf(_angle + CANNON_ROT_SPEED, 2*M_PI);
    }
  }
}
