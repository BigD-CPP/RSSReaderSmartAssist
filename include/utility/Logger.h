#ifndef _LOGGER_H_
#define _LOGGER_H_ 

#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

enum LogTypeEnum
{
	LT_INFO = 0,
	LT_WARNING = 1,
	LT_ERROR = 2,
	LogTypeEnum_count = 3
};

class CLogger
{
public:
	CLogger();
	~CLogger();

	void wlog(string header, string message, bool wfile_enable = false);
	void elog(string header, string message, bool wfile_enable = false);
	void ilog(string header, string message, bool wfile_enable = false);

private:
	const string LogTypeEnum_str[LogTypeEnum_count] {"[I]", "[W]", "[E]"};

	void log(string header, string message, bool wfile_enable, LogTypeEnum err_type);
};

extern CLogger* mLoggerIns;

#endif
