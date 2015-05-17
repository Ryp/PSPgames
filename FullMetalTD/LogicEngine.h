/*
 * LogicEngine.h 
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

#ifndef __LOGICENGINE_H__
#define __LOGICENGINE_H__

#include "oslib/oslib.h"
#include <list>

#include "structs.h"
#include "MapMgr.h"
#include "PathFinder.h"
#include "Enemy.h"
#include "AudioEngine.h"
#include "IGameObserver.h"
#include "Tower.h"
#include "Cannon.h"

enum Gamestatus {
  PLAYING,
  WON,
  LOST
};

class LogicEngine : public IGameObserver
{
public:
  friend class GraphicEngine;
  ~LogicEngine();
  LogicEngine();
  void update(OSL_CONTROLLER* pad);
private:
  void notifyDeath();
  void notifyArrival();
  void setNewGame(const char* mapname);
  void setNewWave();
  void updateViewport();
  void updateCursor();
  void updateGame();
  float getCursorScrPosX() const;
  float getCursorScrPosY() const;
  
  AudioEngine _audio_engine;
  MapMgr _map_mgr;
  std::list<Enemy>* _enemy_list;
  std::list<Tower*>* _tower_list;
  
  Gamestatus _status;
  t_viewport _viewport;
  t_2dindex _cursor;
  int _cursoralpha;
  int _towerselect;
  bool _paused;
  int _gamespeed;
  int _lifes;
  int _score;
  int _money;
  int _points;
  int _wave;
  int _wave_delay;
};

#endif
