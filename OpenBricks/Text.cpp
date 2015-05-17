#include "Text.h"

Text::Text(const char* txt, int x, int y)
{
  setText(txt);
  _pos.x = x;
  _pos.y = y;
  _color = 0xffffff;
}

Text::~Text() {}

void Text::update()
{
  Item::update();
}

void Text::render()
{
  oslSetTextColor(_color | (_focusAlpha << 24));
  oslSetBkColor(0);
  oslDrawString(_pos.x, _pos.y, _text);
  //Render Children
  Item::render();
}

void Text::setText(const char* txt)
{
  strcpy(_text, txt);
}

void Text::setColor(int color)
{
  _color = color;
}
