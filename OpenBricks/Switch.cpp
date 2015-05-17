#include "Switch.h"

Switch::Switch(int x, int y) : Text("NoState", x, y)
{
  setState(false);
}

Switch::~Switch() {}

void Switch::update()
{
  Text::update();
}

void Switch::render()
{
  Text::render();
}


void Switch::switchState()
{
  setState(!_state);
}

bool Switch::getState()
{
  return _state;
}

void Switch::setState(bool state)
{
  _state = state;
  if (state) {
    setColor(ColorOn);
    setText("On");
  } else {
    setColor(ColorOff);
    setText("Off");
  }
}
