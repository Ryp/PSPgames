#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include "oslib/oslib.h"
#include <vector>
#include <map>

enum Mode {
  Classic,
  Garbage,
};

enum ScoreType {
  Single,
  Double,
  Triple,
  Tetris,
};

enum Orientation {
  North,
  East,
  South,
  West,
};

enum BrickColor {
  Empty,
  Yellow,
  Black,
  Green,
  Red,
  Orange,
  Blue,
  Purple,
};

enum PieceType {
  Bar,
  Quad,
  SReverse,
  SNormal,
  LNormal,
  LReverse,
  Pyramid,
};

enum GameStatus {
  Dropping,
  WaitForClear,
  Lost,
  Win,
};

enum Sounds {
  LineClearBegin,
  LineClearEnd,
  LineClearTetris,
  LevelUp,
  MovePiece,
  RotatePiece,
  PlacePiece,
  Pause,
};

typedef struct {
  OSL_SOUND* soundData;
  int channel;
} Sound;

#define MAX_NAME_LENGTH		16
#define MAX_SCORES		8

typedef struct {
  char	name[MAX_NAME_LENGTH + 1];
  int	score;
}	Score;

#define OPT_NONE		(0)
#define OPT_SHOW_BLUR		(1 << 0)
#define OPT_SHOW_GRID		(1 << 1)
#define OPT_SHOW_SHADOW		(1 << 2)
#define OPT_SHOW_SCORE_UP	(1 << 3)
#define OPT_SHOW_NEXT		(1 << 4)
#define OPT_SOFT_DROP		(1 << 5)

typedef struct {
  char	flags;
  int	brick_type;
} Options;

typedef struct {
  int x;
  int y;
} Point;

typedef struct {
  int type;
  int orientation;
  Point pos;
  int array[4][4];
} Piece;

typedef struct {
  char text[40];
  unsigned char alpha;
  unsigned int frame;
  Point pos;
} ScoreText;


#endif
