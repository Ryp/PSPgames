#ifndef __DATAMGR_H__
#define __DATAMGR_H__

#include <iostream>
#include <fstream>
#include "pspmscm.h"
#include "pspiofilemgr.h"
#include "structs.h"

Options	getGameConfig();
Options	getDefaultGameConfig();
bool	writeGameConfigFile(const Options& source);
bool	isMemoryStickPresent();

#endif
