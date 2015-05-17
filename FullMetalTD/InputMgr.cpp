#include "InputMgr.h"

#define OSL_KEYMASK_DPAD OSL_KEYMASK_UP|OSL_KEYMASK_RIGHT|OSL_KEYMASK_DOWN|OSL_KEYMASK_LEFT

InputMgr::InputMgr()
{
  //Set key autorepeat
  oslSetKeyAutorepeat(OSL_KEYMASK_DPAD, 20, 3);
  _pad = oslReadKeys();
}

void InputMgr::readKeys()
{
  _pad = oslReadKeys();
}

OSL_CONTROLLER* InputMgr::getKeys()
{
  return _pad;
}
