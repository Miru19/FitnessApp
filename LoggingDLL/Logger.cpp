#include "Logger.h"

LoggerClass::LoggerClass()
	:m_outFlux{ std::cout }
{
}

LoggerClass::LoggerClass(std::ostream& outFlux)
	: m_outFlux{ outFlux }
{
}

void LoggerClass::Log(const std::string& message, Level level)
{
	Log(message.c_str(), level);
}

std::string LoggerClass::ConvertLevelToString(Level level)
{
	
	std::map<Level, std::string> mapDecision = {
		{Level::ERROR,"ERROR" },
		{Level::INFO, "INFO"},
		{Level::WARNING,"WARNING"},
		
	};
	return mapDecision[level];

}

void LoggerClass::Log(const char* message, Level level)
{
	m_outFlux << GetCurrentTime() << "[" << ConvertLevelToString(level) << "] " << message << std::endl << std::endl;

}

std::ostream& LoggerClass::GetFlux()
{
	return m_outFlux;
}


char* LoggerClass::GetCurrentTime()
{
	char* currentTime;
	currentTime = new char[26];

	auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	ctime_s(currentTime, 26 * sizeof(char), &timenow);

	return currentTime;
}

