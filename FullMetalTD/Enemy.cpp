#include "Enemy.h"

Enemy::Enemy(const t_2dindex& pos, int health, float speed, const t_path& path) : GraphicObject(pos.x, pos.y)
{
  _hp = health;
  _max_hp = health;
  _speed = speed;
  _speed_coeff = 1.0f;
  _glue_time = 0;
  _path = path;
  _alpha = 0;
  _is_arrived = false;
  _is_dead = false;
  setNextNode();
}

Enemy::~Enemy() {}

void Enemy::update()
{
  if (!_is_arrived && !_is_dead) {
    //Fade in
    if (_alpha < 0xFF) {
      _alpha += 8;
      if (_alpha > 0xFF) {
        _alpha = 0xFF;
      }
    }
    //Update speed value
    if (_glue_time > 0) {
      --_glue_time;
      if (_glue_time == 0) {
        _speed_coeff = 1.0f;
      }
    }
    //Movement
    if (isOnTarget()) {
      //Update node
      _pos.x = _target.x;
      _pos.y = _target.y;
      setNextNode();
    } else {
      //Move
      _pos.x += (float)_direction.x * _speed * _speed_coeff;
      _pos.y += (float)_direction.y * _speed * _speed_coeff;
    }
  }
  if (_is_arrived) {
    //Fade out
    if (_alpha > 0) {
      _alpha -= 8;
      if (_alpha < 0) {
        _alpha = 0;
      }
    }
  }
  if (_is_dead) {
    //Fade out
    if (_alpha > 0) {
      _alpha -= 8;
      if (_alpha < 0) {
        _alpha = 0;
      }
    }
  }
}

void Enemy::setDamage(int damage)
{
  if ((!_is_dead) && (!_is_arrived)) {
    _hp -= damage;
    if (_hp <= 0) {
      _hp = 0;
      _is_dead = true;
      notifyDeath();
    }
  }
}

void Enemy::setGlue(int coeff, int time)
{
  _speed_coeff = coeff;
  _glue_time = time;
}

int Enemy::getAlpha() const
{
  return _alpha;
}

int Enemy::getHp() const
{
  return _hp;
}

int Enemy::getMaxHp() const
{
  return _max_hp;
}

bool Enemy::isGlued() const
{
  return (_speed_coeff < 1.0f);
}

bool Enemy::isDead() const
{
  return _is_dead;
}

bool Enemy::isArrived() const
{
  return _is_arrived;
}

bool Enemy::isOnTarget() const 
{
  float dx = (float)_target.x - _pos.x;
  float dy = (float)_target.y - _pos.y;
  return ((fabs(dx) < _speed * _speed_coeff) && (fabs(dy) < _speed * _speed_coeff));
}

void Enemy::setNextNode()
{
  if (!_path.empty()) {
    _target.x = _path.begin()->x;
    _target.y = _path.begin()->y;
    _path.pop_front();
    setDirection();
    _is_arrived = false;
  } else {
    _is_arrived = true;
    notifyArrival();
  }
}

void Enemy::setDirection()
{
  int dx = _target.x - (int)_pos.x;
  int dy = _target.y - (int)_pos.y;
  if (dx > 0) {
    _direction.x = 1;
    _direction.y = 0;
  }
  if (dx < 0) {
    _direction.x = -1;
    _direction.y = 0;
  }
  if (dy > 0) {
    _direction.x = 0;
    _direction.y = 1;
  }
  if (dy < 0) {
    _direction.x = 0;
    _direction.y = -1;
  }
}
