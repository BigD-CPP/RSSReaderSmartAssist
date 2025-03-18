#include "utility/Logger.h"

CLogger* mLoggerIns;

CLogger::CLogger()
{
}

CLogger::~CLogger()
{
}

void CLogger::log(string header, string message, bool wfile_enable, LogTypeEnum err_type)
{
	auto now = system_clock::now();  // Get current time
	auto time_t_now = system_clock::to_time_t(now);  // Convert to time_t
	auto timeInfo = localtime(&time_t_now);

	cout << std::setfill('0') << std::setw(2) << timeInfo->tm_hour << ":"
		<< std::setfill('0') << std::setw(2) << timeInfo->tm_min << ":"
		<< std::setfill('0') << std::setw(2) << timeInfo->tm_sec
		<< " " << LogTypeEnum_str[err_type] << " | "
		<< header << " | "
		<< message
		<< endl;

	if (wfile_enable)
	{
		//TODO: not developed !!
		cerr << "not developed !!" << endl;
	}
}

void CLogger::wlog(string header, string message, bool wfile_enable)
{
	log(header, message, wfile_enable, LT_WARNING);
}

void CLogger::elog(string header, string message, bool wfile_enable)
{
	log(header, message, wfile_enable, LT_ERROR);
	throw runtime_error(message);
}

void CLogger::ilog(string header, string message, bool wfile_enable)
{
	log(header, message, wfile_enable, LT_INFO);
}

