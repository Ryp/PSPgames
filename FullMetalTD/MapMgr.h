/*
 * MapMgr.h 
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

#ifndef __MAPMGR_H__
#define __MAPMGR_H__

#include <pspiofilemgr.h>
#include <list>
#include <iostream>
#include <map>
#include "konstants.h"
#include "structs.h"
#include "GameCell.h"

class MapMgr
{
public:
  MapMgr();
  ~MapMgr();
  void loadMap(const char* name);
  bool isLoaded() const;
  GameCell** getBoard() const;
  
  GameCell** _board;
  std::map< int, std::pair< t_2dindex, t_2dindex > > _portals;
  std::list<t_2dindex> _walls;
  t_wavelist _wave_list;
  t_2dindex _size;
private:
  void allocBoard();
  void deleteBoard();
  
  SceUID _fd;
  bool _loaded;
};

#endif
