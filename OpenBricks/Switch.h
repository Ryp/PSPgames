#ifndef __SWITCH_H__
#define __SWITCH_H__

#include <Text.h>

class Switch : public Text
{
public:
  Switch(int x, int y);
  virtual ~Switch();
  virtual void update();
  virtual void render();
  void switchState();
  bool getState();
  void setState(bool state);
  static const int ColorOn = 0x00ff00;
  static const int ColorOff = 0x0000ff;
private:
  bool _state;
};

#endif
