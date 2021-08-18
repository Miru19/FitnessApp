#include "pch.h"
#include "CppUnitTest.h"

#include"../LoggingDLL/Logger.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MinesweeperUnitTests
{
	TEST_CLASS(LoggerUnitTest)
	{
	public:

		TEST_METHOD(CheckConvertLevelToStringLoger)
		{
			LoggerClass logger;
			std::string error = logger.ConvertLevelToString(LoggerClass::Level::ERROR);
			std::string warning = logger.ConvertLevelToString(LoggerClass::Level::WARNING);
			std::string info = logger.ConvertLevelToString(LoggerClass::Level::INFO);

			Assert::IsTrue(error == "ERROR");
			Assert::IsTrue(warning == "WARNING");
			Assert::IsTrue(info == "INFO");

		}
		TEST_METHOD(ConstructorAndLogFunction)
		{
			std::stringstream result;
			std::string info;
			std::string error;
			std::string warning;
			LoggerClass loggerInfo(result);
			loggerInfo.Log("test", LoggerClass::Level::INFO);
			std::getline(result, info);
			info.clear();
			std::getline(result, info);
			Assert::IsTrue(info == "[INFO] test");

			std::stringstream resultError;
			LoggerClass loggerError(resultError);
			loggerError.Log("test", LoggerClass::Level::ERROR);
			std::getline(resultError, error);
			error.clear();
			std::getline(resultError, error);
			Assert::IsTrue(error == "[ERROR] test");

			std::stringstream resultWarning;
			LoggerClass loggerWarning(resultWarning);
			loggerWarning.Log("test", LoggerClass::Level::WARNING);
			std::getline(resultWarning, warning);
			warning.clear();
			std::getline(resultWarning, warning);
			Assert::IsTrue(warning == "[WARNING] test");
		}
		TEST_METHOD(GetCurrentTimeTest)
		{
			LoggerClass logger;
			std::string time, resultStr, expectedStr;
			std::stringstream expectedResult, resultObtained;
			time = logger.GetCurrentTime();
			char* currentTime;
			currentTime = new char[26];
			auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			ctime_s(currentTime, 26 * sizeof(char), &timenow);
			expectedResult << currentTime;
			resultObtained << time;

			expectedResult >> expectedStr;
			resultObtained >> resultStr;
			Assert::IsTrue(expectedStr == resultStr);
			expectedStr.clear();
			resultStr.clear();

			expectedResult >> expectedStr;
			resultObtained >> resultStr;
			Assert::IsTrue(expectedStr == resultStr);
			expectedStr.clear();
			resultStr.clear();

			expectedResult >> expectedStr;
			resultObtained >> resultStr;
			Assert::IsTrue(expectedStr == resultStr);
			expectedStr.clear();
			resultStr.clear();

			expectedResult >> expectedStr;
			resultObtained >> resultStr;

			expectedStr.clear();
			resultStr.clear();

			expectedResult >> expectedStr;
			resultObtained >> resultStr;
			Assert::IsTrue(expectedStr == resultStr);
			expectedStr.clear();
			resultStr.clear();

		}
		TEST_METHOD(GetFluxTest)
		{
			std::stringstream flux;
			std::string expectedResult,resultObtained;
			LoggerClass logger(flux);
			logger.Log("test", LoggerClass::Level::INFO);
			expectedResult = flux.str();
			logger.GetFlux().put('c');
			resultObtained = flux.str();
			expectedResult.push_back('c');
			Assert::IsTrue(expectedResult==resultObtained);

		}
		
	};
}