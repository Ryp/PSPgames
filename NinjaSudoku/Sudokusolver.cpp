#include "Sudokusolver.h"

Sudokusolver::Sudokusolver(cell **input)
{
  int i, j, k;
  input_ = input;
  resetBoard();
  for (i=0; i<9; i++) {
    for (j=0; j<9; j++) {
      if (input_[i][j].locked) {
        board_[i][j].possib[input_[i][j].value - 1] = true;
      } else {
        for (k=0; k<9; k++) {
          board_[i][j].possib[k] = true;
        }
      }
    }
  }
}

Sudokusolver::~Sudokusolver() {}

void Sudokusolver::resetBoard()
{
  int i, j, k;
  for (i=0; i<9; i++) {
    for (j=0; j<9; j++) {
      for (k=0; k<9; k++) {
        board_[i][j].possib[k] = false;
      } 
      board_[i][j].locked = false;
    }
  }
}
 
void Sudokusolver::solverPutNumber(int x, int y, int n)
{
  int u, v, i;
  u = (x/3)*3;
  v = (y/3)*3;
  for (i=0; i<9; i++) {
    board_[x][y].possib[i] = false;
    board_[x][i].possib[n] = false;
    board_[i][y].possib[n] = false;
    board_[u+i/3][v+i%3].possib[n] = false;
  }
  board_[x][y].possib[n] = true;
  board_[x][y].locked = true;
}

bool Sudokusolver::humanSolver()
{
  bool success;
  //Try all known methods with increasing complexity to solve puzzle
  do {
    do {
      do {
        
      } while (humanSolverBasicMethod());
    } while (humanSolverLoneRangerMethod()); 
  } while (humanSolverMethod3());
  //Finished
  if (isFull()) {
    success = true;
  } else {
    success = false;
  }
  returnBoard();
  return success;
}

bool Sudokusolver::humanSolverBasicMethod()
{
  int i, j, k, t, count;
  bool result = false;
  for (i=0; i<9; i++) {
    for (j=0; j<9; j++) {
      if (!board_[i][j].locked) {
        t = 0;
        count = 0;
        for (k=0; k<9; k++) {
          if (board_[i][j].possib[k]) {
            t = k;
            count++;
          }
        }
        if (count == 1) {
          solverPutNumber(i, j, t);
          result = true;
        }
      }
    }
  }
  return result;
}

bool Sudokusolver::humanSolverLoneRangerMethod()
{
  int i, j, k, l, t, count;
  bool result = false;
  bool match;
  for (i=0; i<9; i++) {
    for (k=0; k<9; k++) {
      //Check rows
      match = true;
      for (j=0; j<9; j++) {
        if (board_[i][j].possib[k] && board_[i][j].locked) {
          match = false; 
        }
      }
      if (match) {
        t = 0;
        count = 0;
        for (j=0; j<9; j++) {
          if (board_[i][j].possib[k]) {
            t = j;
            count++;
          }
        }
        if (count == 1) {
          solverPutNumber(i, t, k);
          result = true;
        }
      }
      //Check columns
      match = true;
      for (j=0; j<9; j++) {
        if (board_[j][i].possib[k] && board_[j][i].locked) {
          match = false;
        }
      }
      if (match) {
        t = 0;
        count = 0;
        for (j=0; j<9; j++) {
          if (board_[j][i].possib[k]) {
            t = j;
            count++;
          }
        }
        if (count == 1) {
          solverPutNumber(t, i, k);
          result = true;
        }
      }
    }
  }  
  //Check blocks
  for (i=0; i<3; i++) {
    for (j=0; j<3; j++) {
      for (k=0; k<9; k++) {
        match = true;
        for (l=0; l<9; l++) {
          if (board_[j*3+l%3][i*3+l/3].possib[k] && board_[j*3+l%3][i*3+l/3].locked) {
            match = false;
          }
        }
        if (match) {
          t = 0;
          count = 0;
          for (l=0; l<9; l++) {
            if (board_[j*3+l%3][i*3+l/3].possib[k]) {
              t = l;
              count++;
            }
          }
          if (count == 1) {
            solverPutNumber(j*3+t%3, i*3+t/3, k);
            result = true;
          }
        }
      }
    }
  }
  return result;
}

bool Sudokusolver::humanSolverMethod3()
{
  int i, j;
  bool result = false;
  for (i=0; i<9; i++) {
    for (j=0; j<9; j++) {
      /* TODO Search in a block for N cells sequence with N sames possibilities
      * If found, other cells inside the block cannot contain same possibilities as the sequence
      */
    }
  }
  return result;
}

int Sudokusolver::getNumber(int x, int y)
{
  int i, number = 0;
  for (i=0; i<9; i++) {
    if (board_[x][y].possib[i]) {
      number = i + 1;
    }
  }
  return number;
}

void Sudokusolver::returnBoard()
{
  int i, j, k;
  for (i=0; i<9; i++) {
    for (j=0; j<9; j++) {
      if (!input_[i][j].locked) {
        /*if (board_[i][j].locked) {
          input_[i][j].value = getNumber(i, j);
        } else {*/
          for (k=0; k<9; k++) {
            input_[i][j].possib[k] = board_[i][j].possib[k];
          }
        /*}*/
      }
    }
  }
}

bool Sudokusolver::isFull()
{
  int i, j;
  bool result = true;
  for (i=0; i<9; i++) {
    for (j=0; j<9; j++) {
      if (!board_[i][j].locked) {
        result = false;
      }
    }
  }
  return result;
}
