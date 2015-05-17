#include "main.h"
#include "routines.h"
#include "constants.h"
#include "Ressource.h"
#include "Sudoku.h"
#include "structs.h"

#define OSL_KEYMASK_DPAD OSL_KEYMASK_UP|OSL_KEYMASK_RIGHT|OSL_KEYMASK_DOWN|OSL_KEYMASK_LEFT

PSP_MODULE_INFO("NinjaSudoku", 0, HB_MAJOR_VERSION, HB_MINOR_VERSION);
PSP_HEAP_SIZE_KB(20480);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int main(int argc, char **argv)
{
  SetupCallbacks();
  oslInit(1);
  oslInitGfx(OSL_PF_8888, 1);
  oslSetQuitOnLoadFailure(1);
  oslSetFrameskip(1);
  oslSetMaxFrameskip(1);
  oslSetKeyAutorepeat(OSL_KEYMASK_DPAD, 20, 3);
  intraFontInit();
  {
    Ressource::GetInstance();
    Sudokupuzzle session(EASY);
    int skip = 0;
    OSL_CONTROLLER* pad = oslReadKeys();
    while (!osl_quit) {
      if (!skip) {
        pad = oslReadKeys();
        session.update(pad);
        //Display
        oslStartDrawing();
        oslDrawImage(Ressource::GetInstance()->backgroundpic_);
        session.display();
        oslEndDrawing();
      }
      oslEndFrame();
      skip = oslSyncFrame();
    }
  }
  //Unload all ressources
  intraFontShutdown();
  oslEndGfx();
  oslQuit();
  sceKernelExitGame();
  return 0;
}

 
