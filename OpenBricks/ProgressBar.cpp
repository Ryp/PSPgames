#include "ProgressBar.h"

ProgressBar::ProgressBar(int minValue, int maxValue, int x, int y)
{
  _minValue = minValue;
  _maxValue = maxValue;
  setValue(minValue);
  
  _pos.x = x;
  _pos.y = y;
  
  _currentX = 0;
  calcColor();
}

ProgressBar::~ProgressBar() {}

void ProgressBar::update()
{
  if (_currentX != _targetX) {
    if (abs(_currentX - _targetX) == 1) {
      _currentX = _targetX;
    } else {
      _currentX = (_currentX + _targetX) / 2;
    }
  }
  calcColor();
  Item::update();
}

void ProgressBar::render()
{
  oslDrawRect(_pos.x - 1, _pos.y - 1, _pos.x + BarLength + 1, _pos.y + BarHeight + 1, BarBackColor + (_focusAlpha << 24));
  oslDrawFillRect(_pos.x, _pos.y, _pos.x + _currentX, _pos.y + BarHeight, _color + (_focusAlpha << 24));
  //Render Children
  Item::render();
}

int ProgressBar::getValue()
{
  return _value;
}

void ProgressBar::setValue(int v)
{
  //Check bounds
  if (v < _minValue) {
    _value = _minValue;
  }
  else if (v > _maxValue) {
    _value = _maxValue;
  } else {
    _value = v;
  }
  //Update state
  _targetX = (BarLength / _maxValue) * _value;
}

void ProgressBar::addValue(int n)
{
  setValue(_value + n);
}

void ProgressBar::calcColor()
{
  //_color = ((200 - _currentX) << 8) + _currentX + 55;
  _color = BarPrimaryColor;
}
