#ifndef __STRUCTS_H__
#define __STRUCTS_H__

typedef struct {
  int x;
  int y;
} coordinates;

typedef struct {  
  int value;
  bool discovered;
  char flag;
} cell;

typedef struct {
  int classic[3];
  int survival[3];
} scoreboard;

enum colors {
  RED = 0xFF0000FF,
  GREEN = 0xFF00FF00,
  BLUE =  0xFFFF0000,
  WHITE = 0xFFFFFFFF,
  LITEGRAY = 0xFFBFBFBF,
  GRAY =  0xFF7F7F7F,
  DARKGRAY = 0xFF3F3F3F,    
  BLACK = 0xFF000000,
  ALTBLACK = 0x7FFFFFFF,
  GOLD = 0xFF17D0FD,
};

enum difficulty {
  CUSTOM,
  EASY,
  MEDIUM,
  HARD,
};

enum gamemode {
  CLASSIC,
  SURVIVAL,
};

enum gamestate {
  RUNNING,
  LOSE,
  WIN,
};

#endif