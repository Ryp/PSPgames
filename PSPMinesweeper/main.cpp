#include "main.h"
#include "routines.h"
#include "Ressource.h"
#include "Menu.h"
#include "rules.h"

#define OSL_KEYMASK_DPAD OSL_KEYMASK_UP|OSL_KEYMASK_RIGHT|OSL_KEYMASK_DOWN|OSL_KEYMASK_LEFT

PSP_MODULE_INFO("PSPMinesweeper", 0, HB_MAJOR_VERSION, HB_MINOR_VERSION);
PSP_HEAP_SIZE_KB(20480);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int main(int argc, char **argv)
{
  SetupCallbacks();
  oslInit(1);
  oslInitGfx(OSL_PF_8888, 1);
  oslSetQuitOnLoadFailure(1);
  oslSetFrameskip(1);
  oslSetMaxFrameskip(4);
  oslSetKeyAutorepeat(OSL_KEYMASK_DPAD, 20, 3);
  intraFontInit();
  {
    Ressource::GetInstance();
    Menu menu;
    int skip = 0;
    OSL_CONTROLLER* pad = oslReadKeys();
    while (!osl_quit) {
      if (!skip) {
        pad = oslReadKeys();
        menu.update(pad);
        oslStartDrawing();
        menu.display();
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
