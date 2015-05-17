#ifndef __BATTERYICON_H__
#define __BATTERYICON_H__

#include "oslib/oslib.h"
#include "psppower.h"
#include <map>

enum BattPng {
  Back,
  AcBack,
  AcIcon,
  Low,
  Half,
  Good,
  Full,
};

class BatteryIcon
{
public:
  BatteryIcon(int x, int y);
  virtual ~BatteryIcon();
  void render();
private:
  std::map<int, OSL_IMAGE*> _sprites;
  bool _battPresent;
  bool _acPresent;
  int _chargePct;
  int _x;
  int _y;
};

#endif
