#ifndef __SUDOKU_H__
#define __SUDOKU_H__

#include "Randgenerator.h"
#include "structs.h"

class Sudokupuzzle
{
private:
  void loadGridA();
  void loadGridEaster();
  void resetSudoku();
  void lockSudoku();
  void changeNumber(int mode);
  bool isFull();
  bool isSolved();
  bool backtrack(int i, int j, int n);
  void drawImageFrameXY(OSL_IMAGE *img, int frame, int x, int y); 
  OSL_IMAGE *backgroundpic_, *bignumbers_, *grid_, *selected_, *smallnumbers_;
  OSL_IMAGE *osk_numbers_, *osk_back_, *osk_selected_;
  intraFont *ltn_;
  Randgenerator generator_;
  cell **board_;
  coordinates cursor_;
  int status_;
public:
  Sudokupuzzle(int level);
  ~Sudokupuzzle();
  void update(OSL_CONTROLLER* pad);
  void display();
};

#endif
