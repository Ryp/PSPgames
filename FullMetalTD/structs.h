/*
 * structs.h 
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

#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <list>

enum Color {
  RED = 0xFF0000FF,
  DARKRED = 0xFF00008F,
  GREEN = 0xFF00FF00,
  BLUE =  0xFFFF0000,
  WHITE = 0xFFFFFFFF,
  LITEGRAY = 0xFFBFBFBF,
  GRAY =  0xFF7F7F7F,
  DARKGRAY = 0xFF3F3F3F,    
  BLACK = 0xFF000000,
  TRANSPARENT = 0x00000000,
  ALTBLACK = 0x7FFFFFFF
};

enum EnemyType {
  GRUNT,
  TANK
};

typedef struct {
  int x;
  int y;
} t_2dindex;

typedef std::list< t_2dindex > t_path;

typedef struct {
  float x;
  float y;
} t_2dvect;

typedef struct {
  t_2dvect speed;
  t_2dvect origin;
  float zoom;
} t_viewport;

typedef struct {
  int waveNo;
  int portalNo;
  EnemyType type;
  int count;
  int rate;
  int delay;
} t_wave;

typedef struct std::list<t_wave> t_wavelist;

#endif
