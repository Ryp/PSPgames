/*
 * GraphicObject.h
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

#ifndef __GRAPHICOBJECT_H__
#define __GRAPHICOBJECT_H__

#include "structs.h"

class GraphicObject
{
public:
  GraphicObject(float x, float y);
  ~GraphicObject();
  /**
   * Compares X and Y coordinates according to the display order
   * @param GraphicObject - class to compare with
   */
  bool operator<(const GraphicObject& g) const;
  float getPosX() const;
  float getPosY() const;
protected:
  t_2dvect _pos;
private:
};

#endif
