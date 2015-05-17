/*
 * Tower.h
 * 
 * Copyright 2012 Ryp (ryp.sqrt@gmail.com)
 * 
 * https://github.com/Ryp/FullMetalTD
 * 
 * FullMetalTD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * FullMetalTD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __TOWER_H__
#define __TOWER_H__

#include "konstants.h"
#include "GraphicObject.h"
#include "Enemy.h"

class Tower : public GraphicObject
{
public:
  Tower(int x, int y);
  ~Tower();
  static void registerEnemyList(std::list<Enemy>* list);
  void levelUp();
  float getAngle();
  bool isLevelMax();
  virtual void update() = 0;
protected:
  static std::list<Enemy>* _enemylist;
  float _angle;
private:
  int _level;
  bool _is_level_max;
};

#endif
