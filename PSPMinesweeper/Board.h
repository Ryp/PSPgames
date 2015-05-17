#ifndef __BOARD_H__
#define __BOARD_H__

#include <stdio.h>
#include <stdlib.h>
#include <new>

#include "structs.h"

class Board
{
public:
  Board(int x, int y);
  ~Board();
  void newBoard(int x, int y);
  bool isOver(int x, int y);
  coordinates size_;
  coordinates pos_;
  cell** cells_;
private:
  void allocBoard();
  void deleteBoard();
  void resetBoard();
  void calculateBoardPos();
};

#endif