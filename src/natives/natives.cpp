/**************************************
*  Natives Source Code File
***************************************/

#include "natives.hpp"
#include "../utilities/utilities.hpp"
#include "libcron/include/libcron/Cron.h"

libcron::Cron<> CronThread;
unsigned int ticks = 0;
std::map<int, std::string> CronList;

bool processed = false;
unsigned int cronID = 0;

cell Natives::SetLogLevel(AMX* amx, cell* params) 
{
	Utilities::prepareLogging(Utilities::GetInteger(amx, params, 1));
	return 1;
}

// native CronID: CreateCron(const cron_name[], const cron_settings[], const callback[], const args[], {Float,_}:...);
cell Natives::CreateCron(AMX* amx, cell* params)
{
	std::string cron_name = Utilities::GetString(amx, params, 1);
	std::string cron_settings = Utilities::GetString(amx, params, 2);
	std::string cron_callback = Utilities::GetString(amx, params, 3);
	std::string cron_args = Utilities::GetString(amx, params, 4);

	Utilities::Callback* callback = new Utilities::Callback(amx, cron_callback);
	callback->addFromFormat(amx, cron_args.c_str(), params, 4);

	bool schedule_generated = CronThread.add_schedule(cron_name, cron_settings, [cron_name, cron_settings, cron_args, callback](auto&) {
		callback->exec(cron_args.c_str());
		char debugMessage[128];
		snprintf(debugMessage, sizeof debugMessage, "CronJob %s with task \"%s\" has been executed.", cron_name.c_str(), cron_settings.c_str());
		Utilities::WriteDebugLog(debugMessage); 
	});

	if (schedule_generated) {
		++cronID;
		CronList.insert(std::make_pair(cronID, cron_name));
		char debugMessage[128];
		snprintf(debugMessage, sizeof debugMessage, "CronJob %d (%s) with task \"%s\" has been created.", cronID, cron_name.c_str(), cron_settings.c_str());
		Utilities::WriteDebugLog(debugMessage);
	}
	else {
		char errorMessage[128];
		snprintf(errorMessage, sizeof errorMessage, "CronJob %s with task \"%s\" failed to create.", cron_name.c_str(), cron_settings.c_str());
		Utilities::WriteErrorLog(errorMessage);
	}
	return schedule_generated;
}

// native DeleteCron(CronID: cronid);
cell Natives::DeleteCron(AMX* amx, cell* params)
{
	unsigned int cronid = Utilities::GetInteger(amx, params, 1);
	if (CronList.find(cronid) == CronList.end()) {
		char message[64];
		snprintf(message, sizeof message, "CronJob %d doesn't exists.", cronid);
		Utilities::WriteWarningLog(message);
		return 0;
	}

	std::string cronName = CronList[cronid];
	CronThread.remove_schedule(cronName);
	char message[128];
	snprintf(message, sizeof message, "CronJob %d (%s) has been deleted.", cronid, cronName.c_str());
	Utilities::WriteDebugLog(message);
	return 1;
}

void Natives::ProcessCronTick()
{
	ticks++;
	if (ticks % 100 == 0) {
		CronThread.tick();
		ticks = 0;
	}
}