#include "pch.h"
#include "CppUnitTest.h"

#include "../Minesweeper/Board.h"
#include "../Minesweeper/Board.cpp"
#include "../Minesweeper/GameType.h"
#include "../Minesweeper/GameType.cpp"
#include "../Minesweeper/FetchGameType.h"
#include "../Minesweeper/FetchGameType.cpp"
#include"../LoggingDLL/Logger.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MinesweeperUnitTests
{
	TEST_CLASS(BoardTest)
	{
	public:

		TEST_METHOD(CheckGameType)
		{
			FetchGameType values;
			Board boardEasy(GameType::Easy, values);
			Assert::AreEqual(boardEasy.GetNumberOfBombs(), 10);
			Assert::AreEqual(boardEasy.GetBoardSizeRow(), 9);
			Assert::AreEqual(boardEasy.GetBoardSizeColumn(), 9);

			Board boardIntermediate(GameType::Intermediate, values);
			Assert::AreEqual(boardIntermediate.GetNumberOfBombs(), 46);
			Assert::AreEqual(boardIntermediate.GetBoardSizeRow(), 16);
			Assert::AreEqual(boardIntermediate.GetBoardSizeColumn(), 16);

			Board boardAdvanced(GameType::Advanced, values);
			Assert::AreEqual(boardAdvanced.GetNumberOfBombs(), 99);
			Assert::AreEqual(boardAdvanced.GetBoardSizeRow(), 24);
			Assert::AreEqual(boardAdvanced.GetBoardSizeColumn(), 24);

			FetchGameType value1(15, 19, 20);
			Board boardCustom(GameType::Custom, value1);
			Assert::AreEqual(boardCustom.GetNumberOfBombs(), 20);
			Assert::AreEqual(boardCustom.GetBoardSizeRow(), 15);
			Assert::AreEqual(boardCustom.GetBoardSizeColumn(), 19);
		}

		TEST_METHOD(Print)
		{
			FetchGameType values;
			Board board(GameType::Easy, values);
			std::stringstream stream;
			stream << board;
			Assert::AreEqual<std::string>("Board size: 9\nNumber of bombs: 10\nGame type: Easy\n", stream.str());
		}
		TEST_METHOD(CopyConstructor)
		{
			FetchGameType values;
			Board boardTest1(GameType::Easy, values), boardTest2;
			boardTest2 = boardTest1;
			Board boardTest3(boardTest1);
			Assert::IsTrue(boardTest1 == boardTest2);
			Assert::IsTrue(boardTest1 == boardTest3);
		}

		TEST_METHOD(GenerateBombs)
		{
			FetchGameType values;
			std::vector<std::pair<int, int>>bombsPositions;
			Board board(GameType::Easy, values);
			board.InitializeMatrix();
			board.MarkBombs();
			board.GenerateMatrixValues();
			board.GenerateMatrixCell();
			for (int row = 0; row < board.GetBoardSizeRow(); row++)
			{
				for (int column = 0; column < board.GetBoardSizeColumn(); column++)
				{
					if (board.GetBoardValue(row, column) == 9)
						bombsPositions.push_back(std::make_pair(row, column));
				}
			}
			for (auto position : bombsPositions)
			{
				Assert::IsTrue(board.GetBoardCell(position.first, position.second).GetType() == CellType::Bomb);
			}
			Assert::IsTrue(bombsPositions.size() == board.GetNumberOfBombs());
		}

		TEST_METHOD(ReplaceMineOnFirstMove)
		{
			FetchGameType values;
			std::vector<std::pair<int, int>>bombsPositions;
			Board board(GameType::Easy, values);
			board.InitializeMatrix();
			board.MarkBombs();
			board.GenerateMatrixValues();
			int row=0, column=0;
			const std::vector<std::vector<int>>matrix = board.GetMatrixValue();
			bool found = false;
			for (int indexRow = 0; indexRow < board.GetBoardSizeRow() && !found; indexRow++)
				for (int indexColumn = 0; indexColumn < board.GetBoardSizeRow(); indexColumn++)
				{
					if (matrix[indexRow][indexColumn] == 9)
					{
						row = indexRow;
						column = indexColumn;
						found = true;
						break;
					}
				}
			board.ReplaceMineOnFirstMove(row, column);
			const std::vector<std::vector<int>>newMatrix = board.GetMatrixValue();
			Assert::IsTrue(newMatrix[row][column] != 9);
		}

		TEST_METHOD(ShowMines)
		{
			FetchGameType values;
			std::vector<std::pair<int, int>>bombsPositions;
			Board board(GameType::Easy, values);
			board.InitializeMatrix();
			board.MarkBombs();
			board.GenerateMatrixValues();
			board.GenerateMatrixCell();
			for (int row = 0; row < board.GetBoardSizeRow(); row++)
			{
				for (int column = 0; column < board.GetBoardSizeColumn(); column++)
				{
					if (board.GetBoardValue(row, column) == 9)
						bombsPositions.push_back(std::make_pair(row, column));
				}
			}

			board.ShowMines();
			for (auto position : bombsPositions)
			{
				Assert::IsTrue(board.GetBoardCell(position.first, position.second).isHidden() == false);
			}
		}

		TEST_METHOD(CellTypeToString)
		{
			GameType gameType = GameType::Easy;
			Assert::IsTrue(ConvertGameTypeToString(gameType) == "Easy");
			gameType = GameType::Intermediate;
			Assert::IsTrue(ConvertGameTypeToString(gameType) == "Intermediate");
			gameType = GameType::Advanced;
			Assert::IsTrue(ConvertGameTypeToString(gameType) == "Advanced");
			gameType = GameType::Custom;
			Assert::IsTrue(ConvertGameTypeToString(gameType) == "Custom");
		}

		TEST_METHOD(StringToCellType)
		{
			std::string gameType = "Easy";
			Assert::IsTrue(ConvertingToGameType(gameType) == GameType::Easy);
			gameType = "Intermediate";
			Assert::IsTrue(ConvertingToGameType(gameType) == GameType::Intermediate);
			gameType = "Advanced";
			Assert::IsTrue(ConvertingToGameType(gameType) == GameType::Advanced);
			gameType = "Custom";
			Assert::IsTrue(ConvertingToGameType(gameType) == GameType::Custom);
		}
		TEST_METHOD(GenerateMatrixCell)
		{
			FetchGameType values;
			Board board(GameType::Easy, values);
			board.InitializeMatrix();
			board.MarkBombs();
			board.GenerateMatrixValues();
			board.GenerateMatrixCell();
			for (int indexRow = 0; indexRow < board.GetBoardSizeRow(); indexRow++)
				for (int indexColumn = 0; indexColumn < board.GetBoardSizeColumn(); indexColumn++)
				{
					int value = board.GetBoardValue(indexRow, indexColumn);
					switch (value)
					{
					case 0:
						Assert::IsTrue(board.GetBoardCell(indexRow, indexColumn).GetType() == CellType::Empty);
						break;
					case 9:
						Assert::IsTrue(board.GetBoardCell(indexRow, indexColumn).GetType() == CellType::Bomb);
						break;
					default:
						Assert::IsTrue(board.GetBoardCell(indexRow, indexColumn).GetType() == CellType::Number);
						break;
					}
				}
		}
		TEST_METHOD(BoardDefaultConstructor)
		{
			Board board;
			Assert::AreEqual(board.GetBoardSizeColumn(), 0);
			Assert::AreEqual(board.GetBoardSizeRow(), 0);
			Assert::AreEqual(board.GetNumberOfBombs(), 0);
			Assert::IsTrue(board.GetType() == GameType::None);

		}

		TEST_METHOD(ClickABomb)
		{
			FetchGameType values;
			Board board(GameType::Easy, values);
			board.InitializeMatrix();
			board.MarkBombs();
			board.GenerateMatrixValues();
			board.GenerateMatrixCell();
			int row = 0;
			int column = 0;
			board.SetFirstMove(false);
			for (int indexRow = 0; indexRow < board.GetBoardSizeRow(); indexRow++)
				for (int indexColumn = 0; indexColumn < board.GetBoardSizeColumn(); indexColumn++)
				{
					int value = board.GetBoardValue(indexRow, indexColumn);
					if (value == 9)
					{
						row = indexRow;
						column = indexColumn;
						break;
					}
				}
			Assert::IsTrue(board.OpenNeighboursOnClick(row, column));
		}

		TEST_METHOD(ClickAGoodCell)
		{
			FetchGameType values;
			Board board(GameType::Easy, values);
			board.InitializeMatrix();
			board.MarkBombs();
			board.GenerateMatrixValues();
			board.GenerateMatrixCell();
			int row = 0;
			int column = 0;
			board.SetFirstMove(false);
			for (int indexRow = 0; indexRow < board.GetBoardSizeRow(); indexRow++)
				for (int indexColumn = 0; indexColumn < board.GetBoardSizeColumn(); indexColumn++)
				{
					int value = board.GetBoardValue(indexRow, indexColumn);
					if (value != 9)
					{
						row = indexRow;
						column = indexColumn;
						break;
					}
				}
			Assert::IsFalse(board.OpenNeighboursOnClick(row, column));
		}

		TEST_METHOD(NumberOfFlags)
		{
			FetchGameType values;
			Board boardEasy(GameType::Easy, values);
			Assert::AreEqual(boardEasy.GetNumberOfFlags(), 10);

			Board boardIntermediate(GameType::Intermediate, values);
			Assert::AreEqual(boardIntermediate.GetNumberOfFlags(), 46);

			Board boardAdvanced(GameType::Advanced, values);
			Assert::AreEqual(boardAdvanced.GetNumberOfFlags(), 99);

			FetchGameType value1(15, 19, 20);
			Board boardCustom(GameType::Custom, value1);
			Assert::AreEqual(boardCustom.GetNumberOfFlags(), 20);
		}

		TEST_METHOD(YouLostMessage)
		{
			FetchGameType values;
			Board board(GameType::Easy, values);
			board.InitializeMatrix();
			board.MarkBombs();
			board.GenerateMatrixValues();
			board.GenerateMatrixCell();
			int row = 0;
			int column = 0;
			board.SetFirstMove(false);
			for (int indexRow = 0; indexRow < board.GetBoardSizeRow(); indexRow++)
				for (int indexColumn = 0; indexColumn < board.GetBoardSizeColumn(); indexColumn++)
				{
					int value = board.GetBoardValue(indexRow, indexColumn);
					if (value == 9)
					{
						row = indexRow;
						column = indexColumn;
						break;
					}
				}

			
			bool result=board.OpenNeighboursOnClick(row, column);
			
			Assert::AreEqual(result, true);
		}

		TEST_METHOD(CheckFlagsNumber)
		{
			FetchGameType values;
			Board board(GameType::Easy, values);
			board.InitializeMatrix();
			board.MarkBombs();
			board.GenerateMatrixValues();
			board.GenerateMatrixCell();
			board.GetBoardCell(0,0).SetCellFlag();
			board.SetNumberOfFlags(0, 0);
			Assert::AreEqual(board.GetNumberOfFlags(), 9);
			board.GetBoardCell(0, 0).SetCellFlag();
			board.SetNumberOfFlags(0, 0);
			Assert::AreEqual(board.GetNumberOfFlags(), 10);

		}
		
	};
}
