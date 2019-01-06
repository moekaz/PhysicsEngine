/*
	Author: Mohamed Kazma
	Description: A logger class that allows us to log information to a log file
	Uses the library spdlog with a wrapper to be used within our API 
*/

#pragma once

#include <PrecompiledHeader.h>

namespace MTRX
{
	class LogManager
	{
	public:
	
	private:
		std::shared_ptr<spdlog::logger> mtrxLogger; // Store a pointer to the logger that the engine will be using
		std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> mtrxSink; // Create a log sink to be used by the logger to log information onto
		LogManager();
		~LogManager();

	protected:
	};
}