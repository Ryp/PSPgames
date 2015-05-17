#ifndef __GAME_H__
#define __GAME_H__

#include <map>
#include <list>
#include "oslib/oslib.h"
#include <pspkernel.h>
#include "BatteryIcon.h"
#include "gfx.h"
#include "structs.h"
#include "datamgr.h"

class Game
{
public:
  Game();
  virtual ~Game();
  void newGame(int mode, int speed, int level);
  bool isEnded();
  void update(OSL_CONTROLLER* pad);
  void render();
  static const int BatteryIconX = 456;
  static const int BatteryIconY = 4;
  static const int GridWidth = 10;
  static const int GridHeight = 20;
  static const int BrickSize = 14;
  static const int BrickStartingPosX = 3;
  static const int BrickStartingPosY = 0;
  static const unsigned BoardBackgroundColor = 0xb0000000;
  static const unsigned BoardOutlineColor = 0x40aaaaaa;
  static const unsigned GridColor = 0x09FFFFFF;
  static const unsigned NextPieceBackgroundColor = 0x50000000;
  static const int GridOffsetX = 150;
  static const int GridOffsetY = 5;
  static const int NextOffsetX = 295;
  static const int NextOffsetY = 100;
  static const int TextOffsetX = 295;
  static const int TextOffsetY = 50;
  static const int TextSpacingY = 15;
  static const int ScoreTextOffsetX = 340;
  static const int ScoreTextOffsetY = 40;
  static const unsigned int ScoreMaxLife = 120;
  static const int ClearTickCount = 60;
  static const int ClearBlurFrameCount = 1;
  static const int PushDownBonus = 1;
  static const int FrameOffset = 2;
  static const int LinesBetweenLevels = 10;
  static const int GameModes = 2;
  static const int GarbageModeLinesTarget = 25;
  static const int GarbageModeMinHeight = 2;
  static const int GarbageModePorosity = 6;
  static const int PieceShadowAlpha = 0x4f;
private:
  void fillGarbage(int lines);
  int getRand(int size);
  int getPushDownTickRate();
  void drawPieces();
  bool checkCollision(Piece& p);
  void checkForLines();
  void removeLines();
  void scoreLines(int lines);
  void scoreDownBonus(int iter);
  void pushScoreNotification(int score);
  void onSpeedUp();
  void requestTurnClockwise();
  void requestTurnCounterClockwise();
  void requestLeft();
  void requestRight();
  void requestDown(bool user);
  void requestUp();
  void onReachBottom();
  void updateShadow();
  void placePiece();
  void popPiece();
  void copyPiece(const Piece& source, Piece& dest);
  void setPiece(Piece& dest, int type, int orientation, int x, int y, bool applyRotFix);
  void loadSound(const char* filename, int index, int channel);
  void playSound(int index);
  void playSound(int index, int channel);
  std::map<int, Sound> _sounds;
  OSL_IMAGE* _blurBuffer;
  OSL_IMAGE *_tile, *_background;
  intraFont* _ltn;
  BatteryIcon _batt;
  SceKernelUtilsMt19937Context _ctx;
  std::list<ScoreText> _scoreText;
  std::list<int> _linesCleared;
  GameStatus _status;
  Options _options;
  bool _paused;
  bool _gameEnd;
  int _mode;
  int _score;
  int _speed;
  int _lines;
  int _tick;
  int _board[GridWidth][GridHeight];
  int _nextPiece;
  Piece _currentPiece;
  Piece _shadow;
  int _lcol; //Used for lose event
  int _wt; //Used for win event
};

#endif
