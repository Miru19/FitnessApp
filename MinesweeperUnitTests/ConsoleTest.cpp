#include "pch.h"
#include "CppUnitTest.h"

#include"../LoggingDLL/Logger.h"
#include "..\Minesweeper\Console.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MinesweeperUnitTests
{
	TEST_CLASS(ConsoleUnitTests)
	{
	public:

		TEST_METHOD(TestSetUserNameAndGetUserName)
		{
			Console consoleTest;
			consoleTest.SetUserName("TestUser");
			std::string expectedName;
			expectedName = consoleTest.GetUserName();
			Assert::IsTrue(expectedName == "TestUser");
		}
		TEST_METHOD(TestConstructors)
		{
			Console testDefaultConstructor, testParamConstructor("TestUser");
			Assert::AreEqual(testDefaultConstructor.GetBombsNumber(), 0);
			Assert::AreEqual(testDefaultConstructor.GetColumn(), 0);
			Assert::AreEqual(testDefaultConstructor.GetRow(), 0);
			Assert::IsTrue(testDefaultConstructor.GetGameType()== GameType::None);
			
			Assert::AreEqual(testParamConstructor.GetBombsNumber(), 0);
			Assert::AreEqual(testParamConstructor.GetColumn(), 0);
			Assert::AreEqual(testParamConstructor.GetRow(), 0);
			Assert::IsTrue(testParamConstructor.GetGameType() == GameType::None);
			Assert::IsTrue(testParamConstructor.GetUserName()=="TestUser");
		}
		TEST_METHOD(TestCheckCustom)
		{
			Console testConsole("TestUser");
			bool result;
			testConsole.SetRow(4);
			testConsole.SetColumn(4);
			testConsole.SetBombsNumber(4);
			result = testConsole.CheckCustom();
			Assert::IsTrue(result);

			testConsole.SetRow(0);
			testConsole.SetColumn(4);
			testConsole.SetBombsNumber(4);
			result = testConsole.CheckCustom();
			Assert::IsFalse(result);

			testConsole.SetRow(4);
			testConsole.SetColumn(0);
			testConsole.SetBombsNumber(4);
			result = testConsole.CheckCustom();
			Assert::IsFalse(result);

			testConsole.SetRow(4);
			testConsole.SetColumn(4);
			testConsole.SetBombsNumber(27);
			result = testConsole.CheckCustom();
			Assert::IsFalse(result);
		}
		TEST_METHOD(TestingSettersAndGetters)
		{
			Console testConsole;
			FetchGameType values(5, 5, 5),result;
			testConsole.SetBombsNumber(10);
			testConsole.SetUserName("TestUser");
			testConsole.SetColumn(10);
			testConsole.SetRow(10);

			Assert::AreEqual(testConsole.GetBombsNumber(), 10);
			Assert::AreEqual(testConsole.GetColumn(), 10);
			Assert::AreEqual(testConsole.GetRow(), 10);
			Assert::IsTrue(testConsole.GetUserName() == "TestUser");
			
			testConsole.SetValues(values);
			result = testConsole.GetValue();
			Assert::AreEqual(result(GameType::Custom, "boardRow"), 5);
			Assert::AreEqual(result(GameType::Custom, "boardColumn"), 5);
			Assert::AreEqual(result(GameType::Custom, "bombNumber"), 5);
		}
		TEST_METHOD(TestCustomInitialization)
		{
			Console testConsole;
			FetchGameType result;
			testConsole.SetBombsNumber(10);
			testConsole.SetColumn(10);
			testConsole.SetRow(10);
			testConsole.SetGameType(GameType::Custom);
			testConsole.CustomInitialization();
			result = testConsole.GetValue();

			Assert::AreEqual(result(GameType::Custom, "boardRow"), 10);
			Assert::AreEqual(result(GameType::Custom, "boardColumn"), 10);
			Assert::AreEqual(result(GameType::Custom, "bombNumber"), 10);
		}
	};
}
