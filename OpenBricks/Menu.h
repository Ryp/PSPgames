#ifndef __MENU_H__
#define __MENU_H__

#include <oslib/oslib.h>
#include <vector>
#include "gfx.h"
#include "Game.h"
#include "Item.h"
#include "ProgressBar.h"
#include "Text.h"
#include "Emitter.h"
#include "datamgr.h"
#include "SelectList.h"
#include "Switch.h"

enum Fade {
  FadingIn,
  FadedIn,
  FadingOut,
  FadedOut,
};

enum MenuType {
  Main,
  Option,
  Hiscores,
};

class Menu
{
public:
  Menu();
  virtual ~Menu();
  void update(OSL_CONTROLLER* pad);
  void render();
  static const int MenuOffsetX = 12;
  static const int MenuOffsetY = 5;
  static const int MenuItemSpacingY = 17;
  static const int CursorSize = 5;
  static const unsigned CursorColorUp = 0xff0000af;
  static const unsigned CursorColorDown = 0xff00005f;
  static const unsigned VerticalLineColor = 0xbf000000;
  static const int OptSwitchOffsetX = 105;
  static const int ScoreBoardOffsetX = 200;
  static const int ScoreBoardOffsetY = 20;
private:
  void startGame();
  void showIntro();
  void setMode(int mode);
  void setMenuAutoRepeat();
  void readOptFile();
  void writeOptFile();
  OSL_FONT *_ft;
  OSL_SOUND *_validate, *_switch;
  OSL_IMAGE *_tile, *_background;
  Emitter _em;
  Game _game;
  std::map<int, SelectList*> _menus;
  ProgressBar *_speedBar, *_levelBar;
  std::map<int, Switch*> _optSwitch;
  Text *_modeText;
  int _fadeStatus;
  int _fadeAlpha;
  int _currentMenu;
  int _mode;
  bool _msPresent;
};

#endif
