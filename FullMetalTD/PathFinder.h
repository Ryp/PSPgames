/*
 * PathFinder.h 
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

#ifndef __PATHFINDER_H__
#define __PATHFINDER_H__

#include <iostream>
#include <list>
#include <map>
#include <stdlib.h>

#include "structs.h"
#include "GameCell.h"

typedef int t_cost_type;                         

typedef struct {
  t_2dindex parent;
  t_cost_type loc_cost;
  t_cost_type mvt_cost;
  t_cost_type tot_cost;
} t_node;

typedef std::map< int, t_node > t_nodelist;

class PathFinder
{
public:
  PathFinder();
  /**
   * Find shortest path between two position on a map
   * Note: this algorithm doesn't modify any of its arguments passed
   * @param **board - map containing movement costs for each cell
   * @param size - size of the map
   * @param start - starting point
   * @param dest - destination point
   * @return true if a path was found (recover it with getPath function)
   */
  bool findPath(GameCell** terrain, const t_2dindex& size, const t_2dindex& start, const t_2dindex& dest);
  /**
   * Return path under the form of a std::list of t_2dindex
   * Note: path doesn't include the start position
   * @return path
   */
  t_path getPath();
private:
  int getManhattanDistance(const t_2dindex& a, const t_2dindex& b);
  t_2dindex getBestOpenPos();
  void addToClosedList(const t_2dindex& n);
  void addAdjacentNodes(const t_2dindex& n);
  int toKey(const t_2dindex& index) const;
  t_2dindex toIndex(const int& key) const;
  bool isOpen(const t_2dindex& n);
  bool isClosed(const t_2dindex& n);
  void buildPath();
  
  GameCell** _terrain;
  t_2dindex _terrain_size;
  t_2dindex _start;
  t_2dindex _dest;
  t_nodelist _open;
  t_nodelist _closed;
  t_path _path;
  bool _isFound;
};

#endif
