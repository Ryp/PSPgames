/*
 * GraphicEngine.h 
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

#ifndef __GRAPHICENGINE_H__
#define __GRAPHICENGINE_H__

#include "oslib/oslib.h"
#include "structs.h"
#include "LogicEngine.h"

enum Tex {
  UI_CURSOR_NORMAL,
  UI_CURSOR_RED,
  UI_CURSOR_GREEN,
  DEBUG_CELLMARKER,
  T_CANNON,
  E_BOO
};

typedef OSL_IMAGE* t_image;
typedef OSL_COLOR t_color;

class GraphicEngine
{
public:
  GraphicEngine(LogicEngine* logic_engine);
  ~GraphicEngine();
  void render();
private:
  void drawStringWithZoom(int a, int b, const char* str);
  void drawLineWithZoom(int a, int b, int u, int v, t_color color);
  void drawRectWithZoom(int a, int b, int u, int v, t_color color);
  void drawImageXYWithZoom(t_image image , int x, int y);
  void drawImageXYAlphaWithZoom(t_image image , int alpha, int x, int y);

  LogicEngine* _logic_engine;
  std::map<Tex, t_image> _textures;
};

#endif
