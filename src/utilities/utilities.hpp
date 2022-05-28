/**************************************
*  Utilities Header File
***************************************/

#ifndef _utilities_h

#define _utilities_h

#include <string>
#include <amx/amx2.h>
#include <deque>
#include <set>
#include "../../src/common/common.hpp"

#define LOG_NONE                    0x00000000
#define LOG_ERROR                   0x00000500
#define LOG_WARNING                 0x08000000
#define LOG_DEBUG                   0x00000001

namespace Utilities {
	std::string GetString(AMX* amx, cell* params, int offset);
	int GetInteger(AMX* amx, cell* params, int offset);
	float GetFloat(AMX* amx, cell* params, int offset);

	int GenerateDirectories(const char* location);
	void prepareLogging(int log_level);

	void WriteDebugLog(char* text);
	void WriteWarningLog(char* text);
	void WriteErrorLog(char* text);

	int RandomNumber(int max);

	class Callback {
	public:
		Callback(AMX* amx);

		Callback(AMX* amx, std::string name);
		Callback* setName(std::string name);
		Callback* addFromFormat(AMX* amx, const char* format, cell* params, unsigned int param_offset);
		Callback* addParameter(int parameter);
		Callback* addParameter(std::string parameter);
		Callback* addParameter(float parameter);

		std::string getName() { return this->name; }

		Callback* exec(const char* format);

	private:
		std::set<AMX*> amx_list;
		std::string name;
		std::deque< int > intParameters;
		std::deque< float > floatParameters;
		std::deque< std::string > stringParameters;
	};
}

#endif