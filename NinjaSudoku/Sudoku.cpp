#include "Sudoku.h"
#include "Sudokusolver.h"
#include "constants.h"
#include "Ressource.h"

Sudokupuzzle::Sudokupuzzle(int level)
{
  backgroundpic_ = Ressource::GetInstance()->backgroundpic_;
  bignumbers_ = Ressource::GetInstance()->bignumbers_;
  grid_ = Ressource::GetInstance()->grid_;
  selected_ = Ressource::GetInstance()->selected_;
  smallnumbers_ = Ressource::GetInstance()->smallnumbers_;
  osk_numbers_ = Ressource::GetInstance()->osk_numbers_;  
  osk_back_ = Ressource::GetInstance()->osk_back_;  
  osk_selected_ = Ressource::GetInstance()->osk_selected_;  
  ltn_ = Ressource::GetInstance()->ltn_;
  //Alloc board
  board_ = new cell*[9];
  for (int i=0; i<9;i++) {
    board_[i] = new cell[9];
  }
  //Reset values
  resetSudoku();
  //Generate sudoku
  loadGridEaster();
  //Lock starting numbers
  lockSudoku();
  //Set status
  status_ = RUNNING;
  //Set cursor position
  cursor_.x = 4;
  cursor_.y = 4;
}

Sudokupuzzle::~Sudokupuzzle() 
{
  for (int i=0; i<9; i++) {
    delete[] board_[i];
  }
  delete[] board_;
}

void Sudokupuzzle::loadGridA()
{
  board_[0][0].value = 6;
  board_[0][1].value = 4;
  board_[0][4].value = 1;
  board_[0][5].value = 2;
  board_[0][6].value = 8;
  board_[0][8].value = 3;
  board_[1][2].value = 2;
  board_[1][3].value = 9;
  board_[1][8].value = 5;
  board_[2][0].value = 5;
  board_[2][5].value = 4;
  board_[2][7].value = 2;
  board_[3][0].value = 7;
  board_[3][2].value = 1;
  board_[3][4].value = 8;
  board_[3][7].value = 9;
  board_[4][0].value = 2;
  board_[4][3].value = 3;
  board_[4][5].value = 5;
  board_[4][8].value = 6;
  board_[5][1].value = 5;
  board_[5][4].value = 9;
  board_[5][6].value = 3;
  board_[5][8].value = 7;
  board_[6][1].value = 1;
  board_[6][3].value = 7;
  board_[6][8].value = 4;
  board_[7][0].value = 3;
  board_[7][5].value = 8;
  board_[7][6].value = 2;
  board_[8][0].value = 9;
  board_[8][2].value = 4;
  board_[8][3].value = 6;
  board_[8][4].value = 5;
  board_[8][7].value = 1;
  board_[8][8].value = 8;
}

void Sudokupuzzle::loadGridEaster()
{
  board_[0][0].value = 1;
  board_[8][0].value = 2;
  board_[1][1].value = 9;
  board_[3][1].value = 4;
  board_[7][1].value = 5;
  board_[2][2].value = 6;
  board_[6][2].value = 7;
  board_[1][3].value = 5;
  board_[3][3].value = 9;
  board_[5][3].value = 3;
  board_[4][4].value = 7;
  board_[3][5].value = 8;
  board_[4][5].value = 5;
  board_[7][5].value = 4;
  board_[0][6].value = 7;
  board_[6][6].value = 6;  
  board_[1][7].value = 3;
  board_[5][7].value = 9;
  board_[7][7].value = 8;
  board_[2][8].value = 2;
  board_[8][8].value = 1;
}

void Sudokupuzzle::resetSudoku()
{
  int i, j, k;
  for (i=0; i<9; i++) {
    for (j=0; j<9; j++) {
      for (k=0; k<9; k++) {
        board_[i][j].possib[k] = false;
      }
      board_[i][j].value = 0;
      board_[i][j].locked = false;
    }
  }
}

void Sudokupuzzle::lockSudoku()
{
  int i, j;
  for (i=0; i<9; i++) {
    for (j=0; j<9; j++) {
      if (board_[i][j].value != 0) {
        board_[i][j].locked = true;
      }
    }
  }
}

void Sudokupuzzle::changeNumber(int mode)
{
  int skip = 0;
  int x, y;
  bool done = false;
  OSL_CONTROLLER* pad = oslReadKeys();
  if (mode == 1) {
    while ((!osl_quit) && (!done)) {
      if (!skip) {
        pad = oslReadKeys();
        //Get joypad input
        x = pad->analogX / 70;
        y = - pad->analogY / 70;
        if (pad->pressed.square) {
          board_[cursor_.x][cursor_.y].value = 0;
          done = true;
        }
        if (pad->pressed.circle) {
          done = true;
        }
        if (pad->pressed.cross) {
          board_[cursor_.x][cursor_.y].value = (1+x)%3 + (1-y)*3 + 1;
          done = true;
        }
        oslStartDrawing();
        oslDrawImage(backgroundpic_);
        display();
        oslDrawImageXY(osk_back_, OSK_XPOS, OSK_YPOS);
        oslDrawImageXY(osk_selected_, OSK_XPOS + (1+x) * OSK_CELL_SIZE, OSK_YPOS + (1-y) * OSK_CELL_SIZE);
        oslDrawImageXY(osk_numbers_, OSK_XPOS, OSK_YPOS);
        oslEndDrawing();
      }
      oslEndFrame();
      skip = oslSyncFrame();
    } 
  }
  if (mode == 2) {
    while ((!osl_quit) && (pad->held.R) && (!done)) {
      if (!skip) {
        pad = oslReadKeys();
        //Get joypad input
        x = pad->analogX / 70;
        y = - pad->analogY / 70;
        if (pad->pressed.square) {
          for (int i=0; i<9; i++) {
            board_[cursor_.x][cursor_.y].possib[i] = false;
          }
        }
        if (pad->pressed.circle) {
          for (int i=0; i<9; i++) {
            board_[cursor_.x][cursor_.y].possib[i] = true;
          }
        }
        if (pad->pressed.cross) {
          board_[cursor_.x][cursor_.y].possib[(1+x)%3 + (1-y)*3] = !board_[cursor_.x][cursor_.y].possib[(1+x)%3 + (1-y)*3]; //FIXME
        }
        oslStartDrawing();
        oslDrawImage(backgroundpic_);
        display();
        oslDrawImageXY(osk_back_, OSK_XPOS, OSK_YPOS);
        oslDrawImageXY(osk_selected_, OSK_XPOS + (1+x) * OSK_CELL_SIZE, OSK_YPOS + (1-y) * OSK_CELL_SIZE);
        oslDrawImageXY(osk_numbers_, OSK_XPOS, OSK_YPOS);
        oslEndDrawing();
      }
      oslEndFrame();
      skip = oslSyncFrame();
    }
  }
}

bool Sudokupuzzle::isFull()
{
  int i, j;
  bool result = true;
  for (i=0; i<9; i++) {
    for (j=0; j<9; j++) {
      if (board_[i][j].value == 0) {
        result = false;
      }
    }
  }
  return result;
}

bool Sudokupuzzle::isSolved()
{
  int i, j, k;
  int t1, t2;
  bool valid = true;
  if (isFull()) {
    /* Board is full, so it is valid if the sum of each sector = 45 TODO Demonstrate this result
     */
    for (i=0; i<9; i++) {
      t2 = t1 = 0;
      for (j=0; j<9; j++) {
        t1 += board_[i][j].value;
        t2 += board_[j][i].value;
      }
      if ((t1 != 45) || (t2 != 45)) {
        valid = false;
      }
    }
    //Check subsections
    for (i=0; i<3; i++) {
      for (j=0; j<3; j++) {
        t1 = 0;
        for (k=0; k<9; k++) {
          t1 += board_[3*i + k%3][3*j + k/3].value;
        }
        if (t1 != 45) {
          valid = false;
        }
      }
    }
  } else {
    valid = false;
  }
  return valid;
}

bool Sudokupuzzle::backtrack(int u, int v, int n)
{
  bool result = false;
  int i, j, k, p, x, y, t;
  board_[u][v].value = n;
  board_[u][v].locked = true;
  Sudokusolver Solver(board_);
  Solver.humanSolver();
  /*
  oslStartDrawing();
  oslDrawImage(Ressource::GetInstance()->backgroundpic_);
  display();
  oslEndDrawing();
  sceKernelDelayThread(40000);
  oslSwapBuffers();
  */
  if (isFull()) {
    //Cas de base
    if (isSolved()) {
      result = true;
    } else {
      result = false;
    }
  } else {
    result = true;
    //Cas récursif
    //Choisir la case avec le moins de candidats
    t = 10;
    x = 1;
    y = 1;
    for (i=0; i<9; i++) {
      for (j=0; j<9; j++) {
        if (board_[i][j].value == 0) {
          p = 0;
          for (k=0; k<9; k++) {
            if (board_[i][j].possib[k]) {
              p++;
            }
          }
          if (p == 0) {
            result = false;
          }
          if (p < t) {
            t = p;
            x = i;
            y = j;
          }  
        }
      }
    }
    if (result) {
      result = false;
      k = 0;
      while ((k < 9) && (!result)) {
        if (board_[x][y].possib[k]) {
          result = backtrack(x, y, k+1);
        }
        k++;
      }
    }
  }
  if (!result) {
    board_[u][v].value = 0;
    board_[u][v].locked = false;
  }
  return result;
}

void Sudokupuzzle::drawImageFrameXY(OSL_IMAGE *img, int frame, int x, int y)
{
  oslSetImageFrame(img, frame);
  oslDrawImageXY(img, x ,y);
}

void Sudokupuzzle::update(OSL_CONTROLLER* pad)
{
  if (status_ == WIN) {
    if (pad->pressed.cross) {
      status_ = RUNNING;
      //Reset values
      resetSudoku();
      //Generate sudoku
      loadGridEaster();
      //Lock starting numbers
      lockSudoku();
    }
  }
  if (status_ == RUNNING) {
    if (isSolved()) {
      status_ = WIN;
    }
    if (pad->pressed.cross) {
      if (!board_[cursor_.x][cursor_.y].locked) {
        changeNumber(1);
      }
    }
    if (pad->pressed.R) {
      if (!board_[cursor_.x][cursor_.y].value != 0) {
        changeNumber(2);
      }
    }
    if (pad->pressed.circle) {
      backtrack(0, 0, 1);
    }
    if (pad->pressed.up) {
      if (cursor_.y == 0) {cursor_.y = 8;} else {cursor_.y--;}
    }
    if (pad->pressed.down) {
      if (cursor_.y == 8) {cursor_.y = 0;} else {cursor_.y++;}
    }
    if (pad->pressed.left) {
      if (cursor_.x == 0) {cursor_.x = 8;} else {cursor_.x--;}
    }
    if (pad->pressed.right) {
      if (cursor_.x == 8) {cursor_.x = 0;} else {cursor_.x++;}
    }
  }
}

void Sudokupuzzle::display()
{
  int i, j, k, u, v;
  oslDrawImage(grid_);
  oslDrawImageXY(selected_, SU_XPOS + SU_YLINE_SIZE * (cursor_.x / 3) + cursor_.x * (1+SU_CELL_SIZE), SU_YPOS + SU_XLINE_SIZE * (cursor_.y / 3) + cursor_.y * (1+SU_CELL_SIZE));
  for (i=0; i<9; i++) {
    for (j=0; j<9; j++) {
      u = SU_XPOS + SU_YLINE_SIZE*(i/3) + i*(1+SU_CELL_SIZE);
      v = SU_YPOS + SU_XLINE_SIZE*(j/3) + j*(1+SU_CELL_SIZE);
      if (board_[i][j].value != 0) {
        drawImageFrameXY(bignumbers_, board_[i][j].value - 1, u, v);
      }
      else {
        for (k=0; k<9; k++) {
          if (board_[i][j].possib[k]) {
            drawImageFrameXY(smallnumbers_, k, 1+u+(1+SU_MINI_SIZE)*(k%3), 1+v+(1+SU_MINI_SIZE)*(k/3));
          }
        }
      }
    }
  }
}
