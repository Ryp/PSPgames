/*
 * Cannon.h
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

#ifndef __CANNON_H__
#define __CANNON_H__

#include "list"

#include "geometry.h"
#include "structs.h"

#include "Tower.h"
#include "Enemy.h"

class Cannon : public Tower
{
public:
  Cannon(int x, int y);
  ~Cannon();
  virtual void update();
private:
  bool isTargetValid();
  void searchForEnemy();
  void onEnemySpotted();
  bool _has_target;
  int _reloadtime;
  std::list<Enemy>::iterator _target;
};

#endif
