#pragma once

#include<iostream>
#include<string>
#include<chrono>
#include<map>

#ifdef LOGGINGDLL_EXPORTS
#define LOGGING_API __declspec(dllexport)
#else
#define LOGGING_API __declspec(dllimport)
#endif

class LOGGING_API LoggerClass
{
public:
	enum class Level
	{
		INFO,
		WARNING,
		ERROR,

	};
	LoggerClass();
	LoggerClass(std::ostream&);
	void Log(const std::string& message, Level level = Level::INFO);
	void Log(const char* message, Level level = Level::INFO);
	char* GetCurrentTime();
	std::ostream& GetFlux();
	std::string ConvertLevelToString(Level);

private:
	std::ostream& m_outFlux;
};

