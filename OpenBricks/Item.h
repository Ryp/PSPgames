#ifndef __ITEM_H__
#define __ITEM_H__

#include <list>

class Item
{
public:
  Item();
  virtual ~Item();
  virtual void update();
  virtual void render();
  void setFocus(bool focusState);
  void addChild(Item* child);
  void enable();
  void disable();
  bool isEnabled() const;
  bool isFocused() const;
  static const int DisabledAlpha = 0x3f;
  static const int FocusOnAlpha = 0xff;
  static const int FocusOffAlpha = 0x7f;
  static const int FadeSpeed = 6;
protected:
  int _focusAlpha;
private:
  bool _enabled;
  bool _focused;
  int _targetAlpha;
  std::list<Item*> _children;
};

#endif
