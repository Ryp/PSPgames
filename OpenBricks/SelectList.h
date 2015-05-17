#ifndef __SELECTLIST_H__
#define __SELECTLIST_H__

#include <map>
#include "Item.h"
#include "oslib/oslib.h"

class SelectList : public Item
{
public:
  SelectList();
  virtual ~SelectList();
  void update();
  void render();
  int getCurrentItem();
  void selectNextItem();
  void selectPreviousItem();
  std::map<int, Item*> items;
private:
  unsigned _currentItem;
};

#endif
