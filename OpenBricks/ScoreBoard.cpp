#include "ScoreBoard.h"
#include "Text.h"

ScoreBoard::ScoreBoard(int x, int y)
{
  _pos.x = x;
  _pos.y = y;
  // TODO generate children
  for (int i = 0; i < MAX_SCORES; ++i)
  {
    addChild(_names[i] = new Text("n00b101", _pos.x + ScoreOffsetX, _pos.y + i * ScoreOffsetY));
  }
}

ScoreBoard::~ScoreBoard() {}

void ScoreBoard::update()
{
  Item::update();
}

void ScoreBoard::render()
{
  if (isFocused())
  {
    oslDrawFillRect(_pos.x, _pos.y, _pos.x + Width, _pos.y + Height, BackColor);
    // TODO
    Item::render();
  }
}
