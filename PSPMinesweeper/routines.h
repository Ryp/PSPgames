#ifndef __ROUTINES_H__
#define __ROUTINES_H__

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>

int exit_callback(int arg1, int arg2, void *common);

int CallbackThread(SceSize args, void *argp);

int SetupCallbacks(void);

#endif
