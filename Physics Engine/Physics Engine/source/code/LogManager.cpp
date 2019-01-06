/*
	Author: Mohamed Kazma
	Description: Logger abstraction API to be used by the MTRX Engine
*/

#include <LogManager.h>

namespace MTRX
{
	LogManager::LogManager()
	{
		mtrxSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>();
		mtrxLogger = spdlog::rotating_logger_mt("MTRXLogger", mtrxSink, 5); // Create logger 
		
	}

	LogManager::~LogManager()
	{
	}
}