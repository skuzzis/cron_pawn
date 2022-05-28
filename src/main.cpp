/**************************************
*  Main Source Code File
***************************************/

#include <amx/amx.h>
#include <plugincommon.h>
#include <thread>

#include "common/common.hpp"
#include "natives/natives.hpp"

unsigned int ms = 0;

logprintf_t logprintf;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() 
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void** ppData) 
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];
	return true;

}

extern "C" const AMX_NATIVE_INFO natives_listing[] = {
	{ "cron_pawn_SetLogLevel", Natives::SetLogLevel },
	{ "CreateCron", Natives::CreateCron },
	{ "DeleteCron", Natives::DeleteCron },
	{ NULL, NULL }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* amx) 
{

	return amx_Register(amx, natives_listing, (int)arraysize(natives_listing));
}

PLUGIN_EXPORT int PLUGIN_CALL Unload()
{
	return 1;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* amx)
{
	return 1;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	Natives::ProcessCronTick();
}