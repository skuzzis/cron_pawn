/**************************************
*  Utilities Source Code File
***************************************/

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <cstdarg>
#include <time.h>
#include <fstream>
#include <random>
#include <experimental/filesystem>

#include "utilities.hpp"
#include <set>

int log_level = LOG_NONE;

std::string Utilities::GetString(AMX* amx, cell* params, int index) 
{
	return amx_GetCppString(amx, params[index]);
}

int Utilities::GetInteger(AMX* amx, cell* params, int offset) 
{
	if (offset == 1)
		return static_cast<int>(params[1]);

	cell* memory_addr = nullptr;
	
	amx_GetAddr(amx, params[offset], &memory_addr);
	int value = static_cast<int>(static_cast<cell>(*memory_addr));
	delete[] memory_addr;

	return value;
}

float Utilities::GetFloat(AMX* amx, cell* params, int offset) 
{
	cell* memory_addr = nullptr;

	amx_GetAddr(amx, params[offset], &memory_addr);
	float value = round(amx_ctof(static_cast<cell>(*memory_addr)) * 100) / 100;
	delete[] memory_addr;

	return value;
}

int Utilities::GenerateDirectories(const char* location)
{
	return (int)std::experimental::filesystem::create_directories(location);
}

void Utilities::prepareLogging(int log_lvl) 
{
	char folder_path[64];
	if ((log_lvl & LOG_ERROR) == LOG_ERROR)
	{
		snprintf(folder_path, sizeof folder_path, "./logs/%s/error", PLUGIN_NAME);
		Utilities::GenerateDirectories(folder_path);
		log_level |= LOG_ERROR;
	}
	if ((log_lvl & LOG_WARNING) == LOG_WARNING)
	{
		snprintf(folder_path, sizeof folder_path, "./logs/%s/warning", PLUGIN_NAME);
		Utilities::GenerateDirectories(folder_path);
		log_level |= LOG_WARNING;
	}
	if ((log_lvl & LOG_DEBUG) == LOG_DEBUG)
	{
		snprintf(folder_path, sizeof folder_path, "./logs/%s/debug", PLUGIN_NAME);
		Utilities::GenerateDirectories(folder_path);
		log_level |= LOG_DEBUG;
	}
}

void Utilities::WriteDebugLog(char* text) 
{
	if ((log_level & LOG_DEBUG) == LOG_DEBUG)
	{
		time_t now = time(0);
		tm* ltm = localtime(&now);

		char logFileName[100];
		snprintf(logFileName, sizeof(logFileName), "./logs/%s/debug/%02d-%02d-%d.log", PLUGIN_NAME, ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900);
		std::ofstream DebugFile(logFileName, std::ios_base::app);
		char logDate[100];
		snprintf(logDate, sizeof(logDate), "[%02d/%02d/%d %02d:%02d:%02d]", ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

		DebugFile << logDate << " " << std::string(text) << "\n";
		DebugFile.close();
	}
}

void Utilities::WriteWarningLog(char* text)
{
	if ((log_level & LOG_WARNING) == LOG_WARNING)
	{
		time_t now = time(0);
		tm* ltm = localtime(&now);

		char logFileName[100];
		snprintf(logFileName, sizeof(logFileName), "./logs/%s/warning/%02d-%02d-%d.log", PLUGIN_NAME, ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900);
		std::ofstream WarningFile(logFileName, std::ios_base::app);
		char logDate[100];
		snprintf(logDate, sizeof(logDate), "[%02d/%02d/%d %02d:%02d:%02d]", ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

		WarningFile << logDate << " " << std::string(text) << "\n";
		WarningFile.close();
	}
}

void Utilities::WriteErrorLog(char* text)
{
	if ((log_level & LOG_ERROR) == LOG_ERROR)
	{
		time_t now = time(0);
		tm* ltm = localtime(&now);

		char logFileName[100];
		snprintf(logFileName, sizeof(logFileName), "./logs/%s/error/%02d-%02d-%d.log", PLUGIN_NAME, ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900);
		std::ofstream ErrorFile(logFileName, std::ios_base::app);
		char logDate[100];
		snprintf(logDate, sizeof(logDate), "[%02d/%02d/%d %02d:%02d:%02d]", ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

		ErrorFile << logDate << " " << std::string(text) << "\n";
		ErrorFile.close();
	}
}

int Utilities::RandomNumber(int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> ran(0, max);
	return ran(gen);
}

Utilities::Callback::Callback(AMX* amx)
{
	this->amx_list.insert(amx);
}

Utilities::Callback::Callback(AMX* amx, std::string name)
{
	this->amx_list.insert(amx);
	this->name = name;
}

Utilities::Callback* Utilities::Callback::setName(std::string name)
{
	this->name = name;
	return this;
}

Utilities::Callback* Utilities::Callback::addFromFormat(AMX* amx, const char* format, cell* params, unsigned int param_offset)
{
	if (format == NULL)
		return this;

	cell* addr_ptr = NULL;
	unsigned int param_index = 1;
	unsigned int stringIndex = 0;

	while (stringIndex < strlen(format)) {
		switch (format[stringIndex])
		{
			case 'i':
			case 'd': {
				this->addParameter(Utilities::GetInteger(amx, params, param_index + param_offset));
				break;
			}
			case 'f': {
				this->addParameter(Utilities::GetFloat(amx, params, param_index + param_offset));
				break;
			}
			case 's': {
				this->addParameter(Utilities::GetString(amx, params, param_index + param_offset));
				break;
			}
		}

		++stringIndex;
		++param_offset;
	}

	return this;
}

Utilities::Callback* Utilities::Callback::addParameter(int parameter)
{
	this->intParameters.push_front(parameter);
	return this;
}

Utilities::Callback* Utilities::Callback::addParameter(std::string parameter)
{
	this->stringParameters.push_front(parameter);
	return this;
}

Utilities::Callback* Utilities::Callback::addParameter(float parameter)
{
	this->floatParameters.push_front(parameter);
	return this;
}

Utilities::Callback* Utilities::Callback::exec(const char* format)
{
	if (this->name.empty())
		return this;

	unsigned int stringArgs = 0;
	unsigned int intArgs = 0;
	unsigned int floatArgs = 0;

	for (AMX* amx : this->amx_list) {
		int functionIndex = 0;
		if (amx_FindPublic(amx, this->name.c_str(), &functionIndex) == AMX_ERR_NONE)
		{
			unsigned int stringIndex = strlen(format);
			while (stringIndex > 0) {
				switch (format[stringIndex - 1])
				{
					case 'i':
					case 'd': {
						amx_Push(amx, this->intParameters[intArgs++]);
						break;
					}
					case 'f': {
						amx_Push(amx, amx_ftoc(this->floatParameters[floatArgs++]));
						break;
					}
					case 's': {
						cell temporary_addr;
						amx_PushString(amx, &temporary_addr, nullptr, this->stringParameters[stringArgs++].c_str(), 0, 0);
						break;
					}
				}

				--stringIndex;
			}

			amx_Exec(amx, nullptr, functionIndex);
		}
	}

	return this;
}