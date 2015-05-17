#include "GameCell.h"

GameCell::GameCell() 
{
  _tower = 0;
}

GameCell::~GameCell()
{
  delTower();
}

bool GameCell::hasTower() const
{
  return (_tower != 0);
}

void GameCell::setTower(Tower* t)
{
  if (_tower == 0) {
    _tower = t;
  }
}

void GameCell::delTower()
{
  if (_tower != 0) {
    delete _tower;
    _tower = 0;
  }
}
