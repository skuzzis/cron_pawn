/**************************************
*  Natives Header File
***************************************/

#ifndef _natives_h

#define _natives_h

#include <string>
#include <amx/amx2.h>
#include "../../src/common/common.hpp"

namespace Natives {
	cell SetLogLevel(AMX* amx, cell* params);
	cell CreateCron(AMX* amx, cell* params);
	cell DeleteCron(AMX* amx, cell* params);

	void ProcessCronTick();
}

#endif