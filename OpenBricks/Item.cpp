#include "Item.h"

Item::Item()
{
  _enabled = false;
  _focusAlpha = DisabledAlpha;
  enable();
}

Item::~Item()
{
  for (std::list<Item*>::iterator it = _children.begin(); it != _children.end(); ++it) {
    delete (*it);
  }
}

void Item::update()
{
  //Compute Focus Alpha
  if (_focusAlpha != _targetAlpha) {
    if (_focusAlpha < _targetAlpha) {
      _focusAlpha += FadeSpeed;
      if (_focusAlpha > _targetAlpha) {
        _focusAlpha = _targetAlpha;
      }
    }
    if (_focusAlpha > _targetAlpha) {
      _focusAlpha -= FadeSpeed;
      if (_focusAlpha < _targetAlpha) {
        _focusAlpha = _targetAlpha;
      }
    }
  }
  //Update Children
  for (std::list<Item*>::iterator it = _children.begin(); it != _children.end(); ++it) {
    (*it)->update();
  }
}

void Item::render()
{
  //Render Children
  for (std::list<Item*>::iterator it = _children.begin(); it != _children.end(); ++it) {
    (*it)->render();
  }
}

void Item::setFocus(bool focusState)
{
  if (_enabled) {
    _focused = focusState;
    if (_focused) {
      _targetAlpha = FocusOnAlpha;
    } else {
      _targetAlpha = FocusOffAlpha;
    }
  }
  for (std::list<Item*>::iterator it = _children.begin(); it != _children.end(); ++it) {
    (*it)->setFocus(focusState);
  }
}

void Item::addChild(Item* child)
{
  _children.push_front(child);
}

void Item::enable()
{
  if (!_enabled) {
    _enabled = true;
    setFocus(false);
  }
  for (std::list<Item*>::iterator it = _children.begin(); it != _children.end(); ++it) {
    (*it)->enable();
  }
}

void Item::disable()
{
  if (_enabled) {
    setFocus(false);
    _enabled = false;
    _targetAlpha = DisabledAlpha;
  }
  for (std::list<Item*>::iterator it = _children.begin(); it != _children.end(); ++it) {
    (*it)->disable();
  }
}

bool Item::isEnabled() const
{
  return _enabled;
}

bool Item::isFocused() const
{
  return _focused;
}
