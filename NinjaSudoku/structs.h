#ifndef __STRUCTS_H__
#define __STRUCTS_H__

enum difficulty {
  EASY,
  MEDIUM,
  HARD,
  EXPERT
};

enum status {
  RUNNING,
  WIN
};

enum colors {
  RED = 0xFF0000FF,
  DARKRED = 0xFF00008F,
  GREEN = 0xFF00FF00,
  BLUE =  0xFFFF0000,
  WHITE = 0xFFFFFFFF,
  LITEGRAY = 0xFFBFBFBF,
  GRAY =  0xFF7F7F7F,
  DARKGRAY = 0xFF3F3F3F,    
  BLACK = 0xFF000000,
  ALTBLACK = 0x7FFFFFFF
};

typedef struct {
  bool possib[9];
  bool locked;
} solvercell;

typedef struct {
  int value;
  bool possib[9];
  bool locked;
} cell;

typedef struct {
  int x;
  int y;
} coordinates;

#endif
