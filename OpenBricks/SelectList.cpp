#include "SelectList.h"

SelectList::SelectList()
{
  _currentItem = 0;
}

SelectList::~SelectList()
{
  for (std::map<int, Item*>::iterator it = items.begin(); it != items.end(); ++it) {
    delete (*it).second;
  }
}

void SelectList::update()
{
  for (std::map<int, Item*>::iterator it = items.begin(); it != items.end(); ++it) {
    (*it).second->update();
  }
  Item::update();
}

void SelectList::render()
{
  for (std::map<int, Item*>::iterator it = items.begin(); it != items.end(); ++it) {
    (*it).second->render();
  }
  Item::render();
}

void SelectList::selectNextItem()
{
  items[_currentItem]->setFocus(false);
  if (_currentItem < items.size() - 1) {
    ++_currentItem;
  } else {
    _currentItem = 0;
  }
  items[_currentItem]->setFocus(true);
  if (!items[_currentItem]->isEnabled()) {
    selectNextItem();
  }
}

void SelectList::selectPreviousItem()
{
  items[_currentItem]->setFocus(false);
  if (_currentItem > 0) {
    --_currentItem;
  } else {
    _currentItem = items.size() - 1;
  }
  items[_currentItem]->setFocus(true);
  if (!items[_currentItem]->isEnabled()) {
    selectPreviousItem();
  }
}

int SelectList::getCurrentItem()
{
  return _currentItem;
}
