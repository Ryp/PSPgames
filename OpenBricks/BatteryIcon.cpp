#include "BatteryIcon.h"

BatteryIcon::BatteryIcon(int x, int y)
{
  _x = x;
  _y = y;
  _sprites[Back] = oslLoadImageFilePNG((char*)"media/batt/batt_empty.png", OSL_IN_RAM, OSL_PF_8888);
  _sprites[AcBack] = oslLoadImageFilePNG((char*)"media/batt/batt_chargingback.png", OSL_IN_RAM, OSL_PF_8888);
  _sprites[AcIcon] = oslLoadImageFilePNG((char*)"media/batt/batt_ac_icon.png", OSL_IN_RAM, OSL_PF_8888);
  _sprites[Low] = oslLoadImageFilePNG((char*)"media/batt/batt_low.png", OSL_IN_RAM, OSL_PF_8888);
  _sprites[Half] = oslLoadImageFilePNG((char*)"media/batt/batt_half.png", OSL_IN_RAM, OSL_PF_8888);
  _sprites[Good] = oslLoadImageFilePNG((char*)"media/batt/batt_good.png", OSL_IN_RAM, OSL_PF_8888);
  _sprites[Full] = oslLoadImageFilePNG((char*)"media/batt/batt_full.png", OSL_IN_RAM, OSL_PF_8888);
}

BatteryIcon::~BatteryIcon()
{
  for (std::map<int, OSL_IMAGE*>::iterator it = _sprites.begin(); it != _sprites.end(); ++it) {
    oslDeleteImage((*it).second);
  }
}

void BatteryIcon::render()
{
  _battPresent = scePowerIsBatteryExist();
  _acPresent = scePowerIsPowerOnline();
  _chargePct = scePowerGetBatteryLifePercent();
  //Draw background
  oslDrawImageXY(_sprites[Back], _x, _y);
  //Draw orange background if on AC power
  if (_acPresent) {
    oslDrawImageXY(_sprites[AcBack], _x, _y);
  }
  //Draw battery life bar
  if (_battPresent) {
    if (_chargePct > 85) {
      oslDrawImageXY(_sprites[Full], _x, _y);
    }
    else if (_chargePct > 60) {
      oslDrawImageXY(_sprites[Good], _x, _y);
    }
    else if (_chargePct > 35) {
      oslDrawImageXY(_sprites[Half], _x, _y);
    }
    else if (_chargePct > 10) {
      oslDrawImageXY(_sprites[Low], _x, _y);
    } 
    else {
      //Blinking bar
      if ((clock() % CLOCKS_PER_SEC) > (CLOCKS_PER_SEC / 2)) {
        oslDrawImageXY(_sprites[Low], _x, _y);
      }
    }
  }
  //Draw AC power icon
  if (_acPresent && _battPresent) {
    oslDrawImageXY(_sprites[AcIcon], _x, _y);
  }
}
