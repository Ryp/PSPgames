#ifndef __TEXT_H__
#define __TEXT_H__

#include "Item.h"
#include "oslib/oslib.h"
#include "structs.h"

class Text : public Item
{
public:
  Text(const char* txt, int x, int y);
  virtual ~Text();
  virtual void update();
  virtual void render();
  void setText(const char* txt);
  void setColor(int color);
private:
  char _text[60];
  Point _pos;
  int _color;
};

#endif
