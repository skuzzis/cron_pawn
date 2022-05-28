/**************************************
*  Common Header File
***************************************/

extern void** ppPluginData;
extern void* pAMXFunctions;
typedef void (*logprintf_t)(const char* szFormat, ...);
extern logprintf_t logprintf;

#ifndef _common_h

#define _common_h

const char PLUGIN_NAME[] = "cron_pawn"; 

#endif
