/*
 * geometry.h 
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

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <oslib/oslib.h>
#include "structs.h"
#include "konstants.h"
#include "pspvfpu.h"

/** 2D Geometry functions optimised for PSP System
 */

/**
 * Get angle of a 2D vector
 * @param v - input vector
 * @return angle
 */
float getVectAngle(const t_2dvect& v);

/**
 * Get the norm from a 2D vector
 * @param v - input vector
 * @return vector norm
 */
float getVectNorm(const t_2dvect& v);

/**
 * Get angle between 2 2D vectors
 * @param v1 - first vector
 * @param v2 - second vector
 * @return angle between v1 and v2
 */
float get2VectAngle(const t_2dvect& v1, const t_2dvect& v2);

/**
 * Get dot product of 2 2D vectors
 * @param v1 - first vector
 * @param v2 - second vector
 * @return dot product of v1 by v2
 */
float dot(const t_2dvect& v1, const t_2dvect& v2);

/**
 * Get vector product of 2 2D vectors
 * @param v1 - first vector
 * @param v2 - second vector
 * @return vector product of v1 by v2
 */
float vectprod(const t_2dvect& v1, const t_2dvect& v2);

/**
 * Normalize a vector
 * @param v - input vector
 */
void normalizeVect(t_2dvect& v);


#endif
