#include "main.h"
#include "routines.h"

#include "Menu.h"

#define HB_MAJOR_VERSION 1
#define HB_MINOR_VERSION 2

PSP_MODULE_INFO("OpenBricks", 0, HB_MAJOR_VERSION, HB_MINOR_VERSION);
PSP_HEAP_SIZE_KB(20480);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int main()
{
  SetupCallbacks();
  oslInit(1);
  oslInitGfx(OSL_PF_8888, 1);
  oslInitAudio();
  oslSetQuitOnLoadFailure(1);
  oslSetFrameskip(1);
  oslSetMaxFrameskip(4);
  intraFontInit();
  {
    Menu menu;
    int skip = 0;
    OSL_CONTROLLER* pad;
    while (!osl_quit) {
      if (!skip) {
        pad = oslReadKeys();
        menu.update(pad);
        menu.render();
      }
      oslEndFrame();
      skip = oslSyncFrame();
    }
  }
  //Unload all ressources
  intraFontShutdown();
  oslEndGfx();
  oslDeinitAudio();
  oslQuit();
  sceKernelExitGame();
  return 0;
}
