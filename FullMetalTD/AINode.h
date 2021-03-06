/* 
 * AINode.h
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

#ifndef __AINODE_H__
#define __AINODE_H__

#include "konstants.h"

class AINode
{
public:
  AINode();
  bool isBlocked() const;
  void setBlocked(bool val);
  int getCost() const;
  void setCost(int val);
protected:
  bool _is_blocked;
  int _cost;
};

#endif
