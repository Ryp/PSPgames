/*
 * gfx.h 
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

#ifndef __GFX_H__
#define __GFX_H__

#include <oslib/oslib.h>

void blurDrawBufferHorizontally(int radius, OSL_IMAGE* blurBuffer);

void blurDrawBufferVertically(int radius, OSL_IMAGE* blurBuffer);

void blurDrawBuffer(int radius, OSL_IMAGE* blurBuffer);

void drawImageFrameXY(OSL_IMAGE *img, int frame, int x, int y);

#endif
