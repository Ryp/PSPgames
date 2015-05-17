#include "main.h"
#include "routines.h"
#include "konstants.h"

#include "InputMgr.h"
#include "LogicEngine.h"
#include "GraphicEngine.h"

PSP_MODULE_INFO("FullMetalTD", 0, HB_MAJOR_VERSION, HB_MINOR_VERSION);
PSP_HEAP_SIZE_KB(20480);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int main()
{
  SetupCallbacks();
  oslInit(1);
  oslSetFrameskip(1);
  oslSetMaxFrameskip(1);
  {
    InputMgr input_mgr;
    LogicEngine logic_engine;
    GraphicEngine graphic_engine(&logic_engine);
    int skip = 0; //For Vsync
    //Game Loop
    while (!osl_quit) {
      if (!skip) {
        input_mgr.readKeys();
        logic_engine.update(input_mgr.getKeys());
        graphic_engine.render();
      }
      oslEndFrame();
      skip = oslSyncFrame();
    }
  }
  oslQuit();
  sceKernelExitGame();
  return 0;
}
