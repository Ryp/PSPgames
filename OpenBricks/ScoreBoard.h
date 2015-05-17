#ifndef __SCOREBOARD_H__
#define __SCOREBOARD_H__

#include <Item.h>
#include "structs.h"
#include "Text.h"

class ScoreBoard : public Item
{
public:
  ScoreBoard(int x, int y);
  virtual ~ScoreBoard();
  void update();
  void render();
  static const int Height = 150;
  static const int Width = 200;
  static const unsigned BackColor= 0x9f000000;
  static const int ScoreOffsetX = 10;
  static const int ScoreOffsetY = 16;

private:
  Point _pos;
  Text* _names[MAX_SCORES];
};

#endif
