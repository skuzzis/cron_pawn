#if defined _cron_pawn_inc
	#endinput
#endif

#define _cron_pawn_inc

#define LOG_NONE                    0x00000000
#define LOG_ERROR                   0x00000500
#define LOG_WARNING                 0x08000000
#define LOG_DEBUG                   0x00000001

native cron_pawn_SetLogLevel(loglevel = LOG_ERROR | LOG_WARNING);
native CronID: CreateCron(const cron_name[], const cron_settings[], const callback[], const args[], {Float,_}:...);
native DeleteCron(CronID: cronid);