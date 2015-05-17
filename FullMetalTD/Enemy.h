/*
 * Enemy.h
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

#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <math.h>
#include "structs.h"
#include "Target.h"
#include "GraphicObject.h"

class Enemy : public GraphicObject, Target
{
public:
  /**
   * Class constructor
   * @param pos - starting position
   * @param health
   * @param speed
   * @param path - path followed (can be empty)
   */
  Enemy(const t_2dindex& pos, int health, float speed, const t_path& path);
  ~Enemy();
  void update();
  void setDamage(int damage);
  void setGlue(int coeff, int time);
  int getAlpha() const;
  int getHp() const;
  int getMaxHp() const;
  bool isGlued() const;
  bool isDead() const;
  bool isArrived() const;
private:
  /**
   * Determines whether the enemy is close to the targeted node or not
   */
  bool isOnTarget() const;
  /**
   * Change current targeted node to the next one
   */
  void setNextNode();
  /**
   * Change movement direction according to the targeted node
   */
  void setDirection();
  t_path _path; //Path to follow
  t_2dindex _target; //Targeted node
  int _hp; //Health
  int _max_hp;
  float _speed; //Speed after calculation (glue, etc...)
  float _speed_coeff; //Glue coefficient
  int _glue_time; //Glue time
  t_2dindex _direction; //Movement direction
  int _alpha;
  bool _is_arrived;
  bool _is_dead;
};

#endif
