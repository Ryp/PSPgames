/*
 * konstants.h 
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

#ifndef __KONSTANTS_H__
#define __KONSTANTS_H__

#define HB_MAJOR_VERSION 1
#define HB_MINOR_VERSION 2

//File IO Related
#define O_RDONLY    0x0001 
#define O_WRONLY    0x0002 
#define O_RDWR      0x0003 
#define O_NBLOCK    0x0010 
#define O_APPEND    0x0100
#define O_CREAT     0x0200 
#define O_TRUNC     0x0400 
#define O_NOWAIT    0x8000 

//Controller
#define ANALOG_DEAD_ZONE 50

//AI
#define NODE_DEFAULT_COST 1

//SCREEN
#define PSP_SCR_HEIGHT 272
#define PSP_SCR_WIDTH 480

//REAL PIXEL SIZE
#define FIELD_HEIGHT 544
#define FIELD_WIDTH 960

#define HP_OFFSETY 8
#define HP_WIDTH 20.0f
#define HP_HEIGHT 5

#define GAME_MAXSPEED 3

#define CURSOR_BLINK_SPEED 8 //Must be a divisor of 512
#define VIEWPORT_FOCUS_ZONE 0.4 //Percentage of screen where the cursor doesn't affect viewport position
#define VIEWPORT_FRICTION 0.5
#define ZOOM_MAX 1.0
#define ZOOM_MIN 0.5
#define ZOOM_SPEED 0.03

//GAME RELATED CONSTANTS

#define WAVE_MAX 20
#define WAVE_DELAY 120

#define STARTING_MONEY 10
#define STARTING_LIFES 20
#define STARTING_POINTS 0

#define TOWER_MAX_LEVEL 3
#define TOWER_NBR 5

#define BOARD_CELL_SIZE 40
#define BOARD_OFFSETX 50
#define BOARD_OFFSETY 50

#define CANNON_ROT_SPEED 0.06
#define CANNON_FAR_RANGE 5.0f
#define CANNON_CLOSE_RANGE 0.5f
#define CANNON_RELOAD_DELAY 8
#define CANNON_DAMAGE 2

#define GLUE_BUY_COST 10
#define GLUE_UPGRADE_COST 5
#define GLUE_FIRE_RATE 1
#define GLUE_ROTATION_RATE 2
#define GLUE_VISCOSITY 10
#define GLUE_VISCOSITY_BONUS 20
#define GLUE_RANGE 40
#define GLUE_RANGE_BONUS 5

#define TESLA_BUY_COST 50
#define TESLA_UPGRADE_COST 25
#define TESLA_FIRE_RATE 1
#define TESLA_DAMAGE 100
#define TESLA_DAMAGE_BONUS 50
#define TESLA_RANGE 40
#define TESLA_RANGE_BONUS 5

#endif 
