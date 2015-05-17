#ifndef __PROGRESSBAR_H__
#define __PROGRESSBAR_H__

#include "Game.h"
#include "Item.h"

class ProgressBar : public Item
{
public:
  ProgressBar(int minValue, int maxValue, int x, int y);
  virtual ~ProgressBar();
  virtual void update();
  virtual void render();
  int getValue();
  void setValue(int v);
  void addValue(int n);
  static const int BarLength = 70;
  static const int BarHeight = 6;
  static const int BarPrimaryColor = 0x0f11dd;
  static const int BarBackColor = 0x9F9F9F;
private:
  void calcColor();
  int _minValue; 
  int _maxValue;
  int _value;
  
  Point _pos;
  int _currentX;
  int _targetX;
  
  int _color;
};

#endif
