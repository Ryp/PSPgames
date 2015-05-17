#include "Board.h"
#include "rules.h"

Board::Board(int x, int y)
{
  size_.x = x;
  size_.y = y;
  calculateBoardPos();
  allocBoard();
  resetBoard();
}

Board::~Board()
{
  deleteBoard();
}

void Board::newBoard(int x, int y)
{
  deleteBoard();
  size_.x = x;
  size_.y = y;
  calculateBoardPos();
  allocBoard();
  resetBoard();
}

bool Board::isOver(int x, int y)
{
  return (((x - pos_.x) >= 0) && ((x - pos_.x) < size_.x*TILE_SIZE) && ((y - pos_.y) >= 0) && ((y - pos_.y) < size_.y*TILE_SIZE));
}

void Board::allocBoard()
{
  cells_ = new cell*[size_.x];
  for (int i=0; i<size_.x;i++) {
    cells_[i] = new cell[size_.y];
  }
}

void Board::deleteBoard()
{
  for (int i=0; i<size_.x; i++) {
    delete[] cells_[i];
  }
  delete[] cells_;
}

void Board::resetBoard()
{
  for (int i=0; i<size_.x;i++) {
    for (int j=0; j<size_.y;j++) {
      cells_[i][j].value = 0;
      cells_[i][j].discovered = 0;
      cells_[i][j].flag = 0;     
    }
  }
}

void Board::calculateBoardPos()
{
  pos_.x = (480 - TILE_SIZE * size_.x) / 2;
  pos_.y = (272 - TILE_SIZE * size_.y) / 2;
}
