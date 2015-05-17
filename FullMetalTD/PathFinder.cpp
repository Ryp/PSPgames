#include "PathFinder.h"
#include <stdio.h>

PathFinder::PathFinder() {}

bool PathFinder::findPath(GameCell** terrain, const t_2dindex& size, const t_2dindex& start, const t_2dindex& dest)
{
  _terrain = terrain;
  _terrain_size.x = size.x;
  _terrain_size.y = size.y;
  _start.x = start.x;
  _start.y = start.y;
  _dest.x = dest.x;
  _dest.y = dest.y;
  _open.clear();
  _closed.clear();
  _path.clear();
  {
    t_node tmp;
    tmp.parent.x = _start.x;
    tmp.parent.y = _start.y;
    tmp.loc_cost = tmp.mvt_cost = tmp.tot_cost = 0;
    //Put start into the open list to start A* algorythm
    _open[toKey(_start)] = tmp;
  }
  t_2dindex current;
  do {
    current = getBestOpenPos();
    addToClosedList(current);
    addAdjacentNodes(current);    
  } while (!((current.x == _dest.x) && (current.y == _dest.y)) && (!_open.empty()));
  if ((current.x == _dest.x) && (current.y == _dest.y)){
    buildPath();
    _isFound = true;
  } else {
    _isFound = false;
  }
  return (_isFound);
}

t_path PathFinder::getPath()
{
  return (_path);
}

int PathFinder::getManhattanDistance(const t_2dindex& a, const t_2dindex& b)
{
  return (abs(b.x - a.x) + abs(b.y - a.y));
}

t_2dindex PathFinder::getBestOpenPos()
{
  t_cost_type cost = _open.begin()->second.tot_cost;
  t_2dindex node = toIndex(_open.begin()->first);
  for (t_nodelist::iterator it = _open.begin(); it != _open.end(); ++it) {
    if (it->second.tot_cost < cost) {
      cost = it->second.tot_cost;
      node = toIndex(it->first);
    }
  }
  return (node);
}

void PathFinder::addToClosedList(const t_2dindex& p)
{
  _closed[toKey(p)] = _open[toKey(p)];
  if (_open.erase(toKey(p)) == 0) {
    std::cerr << "Error: Node absent from open list" << std::endl;
  }
}

void PathFinder::addAdjacentNodes(const t_2dindex& n)
{
  t_2dindex p;
  for (p.x = (n.x - 1); p.x <= (n.x + 1); ++p.x) {
    for (p.y = (n.y - 1); p.y <= (n.y + 1); ++p.y) {
      if ((p.x >= 0) && (p.x < _terrain_size.x) && (p.y >= 0) && (p.y < _terrain_size.y)) {
        if ((abs(n.x - p.x) ^ abs(n.y - p.y)) && (!_terrain[p.x][p.y].isBlocked())) {
          if (!isClosed(p)) {
            t_node tmp;
            tmp.loc_cost = getManhattanDistance(p, _dest);
            tmp.mvt_cost = _closed.find(toKey(n))->second.mvt_cost + _terrain[p.x][p.y].getCost();
            tmp.tot_cost = tmp.loc_cost + tmp.mvt_cost;
            tmp.parent = n;
            if (isOpen(p)) {
              if (tmp.tot_cost < _open[toKey(p)].tot_cost) {
                _open[toKey(p)] = tmp;
              }
            } else {
              _open[toKey(p)] = tmp;
            }
          }
        }
      }
    }
  }
}

int PathFinder::toKey(const t_2dindex& index) const
{
  return (index.x + _terrain_size.x * index.y);
}

t_2dindex PathFinder::toIndex(const int& key) const
{
  t_2dindex result;
  result.y = key / _terrain_size.x;
  result.x = key - (result.y * _terrain_size.x);
  return (result);
}

bool PathFinder::isOpen(const t_2dindex& n)
{
  t_nodelist::iterator i = _open.find(toKey(n));
  return (i != _open.end());
}

bool PathFinder::isClosed(const t_2dindex& n)
{
  t_nodelist::iterator i = _closed.find(toKey(n));
  return (i != _closed.end());
}

void PathFinder::buildPath()
{
  t_node& tmp = _closed[toKey(_dest)];
  t_2dindex n;
  t_2dindex prec;
  prec.x = tmp.parent.x;
  prec.y = tmp.parent.y;
  _path.push_front(_dest);
  do {
    n.x = prec.x;
    n.y = prec.y;
    _path.push_front(n);
    tmp = _closed[toKey(tmp.parent)];
    prec.x = tmp.parent.x;
    prec.y = tmp.parent.y;
  } while ((prec.x != _start.x) || (prec.y != _start.y));
}
