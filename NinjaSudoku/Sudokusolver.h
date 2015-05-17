#ifndef __SUDOKUSOLVER_H__
#define __SUDOKUSOLVER_H__

#include "structs.h"

class Sudokusolver
{
private:
  void resetBoard();
  void generateFullBoard();
  void solverPutNumber(int x, int y, int n);
  bool humanSolverBasicMethod();
  bool humanSolverLoneRangerMethod();
  bool humanSolverMethod3();
  int getNumber(int x, int y);
  void returnBoard();
  bool isFull();
  bool isValid();
  cell **input_;
  solvercell board_[9][9];
public:
  Sudokusolver(cell **input);
  ~Sudokusolver();
  bool humanSolver();
};

#endif
