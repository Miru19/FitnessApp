#include "Console.h"

Console::Console() :
	m_gameOver{ false }, m_gameWon{ false }, m_bombsNumber{ 0 }, m_column{ 0 }, m_gameType{ GameType::None }, m_row{ 0 }
{
}

Console::Console(const std::string& name) :
	m_userName{ name }, m_gameOver{ false }, m_gameWon{ false }, m_bombsNumber{ 0 }, m_column{ 0 }, m_gameType{ GameType::None }, m_row{ 0 }
{
}

void Console::GameInitialization()
{
	Board board(m_gameType, m_values);
	m_board = board;

	m_board.MarkBombs();
	m_board.GenerateMatrixValues();
	m_board.GenerateMatrixCell();
	std::string str = "Good luck " + GetUserName() + "! Game started!";
	std::cout << std::endl;
	m_logger.Log(str, LoggerClass::Level::INFO);
	start = std::clock();
}

int Console::GetChoosenMode()
{
	int option;
	std::cout << "Choose between the following game types: " << std::endl;
	std::cout << "1 - Easy Mode" << std::endl;
	std::cout << "2 - Intermediate Mode" << std::endl;
	std::cout << "3 - Hard Mode" << std::endl;
	std::cout << "4 - Custom Mode" << std::endl;
	std::cout << std::endl;

	std::cout << "Enter the number for your option: ";
	std::cin >> option;
	std::cout << std::endl;

	while (option != 1 && option != 2 && option != 3 && option != 4)
	{
		std::cout << "Please enter a valid number" << std::endl;
		std::cin >> option;
	}

	switch (option)
	{
	case 1:
	{
		m_logger.Log("Easy Mode choosen", LoggerClass::Level::INFO);
		m_gameType = GameType::Easy;
		return 1;
	}
	case 2:
	{
		m_logger.Log("Intermediate Mode choosen", LoggerClass::Level::INFO);
		m_gameType = GameType::Intermediate;
		return 2;
	}
	case 3:
	{
		m_logger.Log("Hard Mode choosen", LoggerClass::Level::INFO);
		m_gameType = GameType::Advanced;
		return 3;
	}
	case 4:
	{
		m_logger.Log("Custom Mode choosen", LoggerClass::Level::INFO);
		m_gameType = GameType::Custom;
		CustomValues();
		return 4;
	}
	default:
		m_logger.Log("Please enter a valid number", LoggerClass::Level::WARNING);
		return 0;
	}
}

void Console::ChoosePosition()
{
	int action = GetAction();
	Position position = GetPosition();
	auto& [row, column] = position;

	if (action == 1)
	{
		std::string str = m_userName + " pressed on row with number " + std::to_string((row)) + " and column with number " + std::to_string((column));
		m_logger.Log(str, LoggerClass::Level::INFO);
		m_gameOver = m_board.OpenNeighboursOnClick(row - 1, column - 1);

		if (m_gameOver)
		{
			int duration = (std::clock() - start) / CLOCKS_PER_SEC;
			std::string str = "Sorry, " + GetUserName() + ", you lost! " + "You played for " + std::to_string(duration) + " seconds.";
			m_logger.Log(str, LoggerClass::Level::INFO);
		}

		CheckIfWin();
	}
	else
	{
		if (m_board.GetNumberOfFlags() != 0 ||
			(m_board.GetNumberOfFlags() == 0 && m_board.GetBoardCell(row - 1, column - 1).IsFlag() == true))
		{
			m_board.GetBoardCell(row - 1, column - 1).SetCellFlag();
			m_board.SetNumberOfFlags(row - 1, column - 1);
		}

		std::string str = m_userName + " has " + std::to_string(m_board.GetNumberOfFlags()) + " flags left";
		m_logger.Log(str, LoggerClass::Level::INFO);
		CheckIfWin();
	}

}

void Console::PlayGame()
{
	GetChoosenMode();
	GameInitialization();
	PrintCells();

	while (!m_gameOver && !m_gameWon)
	{
		ChoosePosition();
		PrintCells();
	}
}

void Console::CustomValues()
{
	std::cout << "Please enter the row size: ";
	std::cin >> m_row;
	std::cout << "Please enter the column size: ";
	std::cin >> m_column;
	std::cout << "Please enter the number of bombs: ";
	std::cin >> m_bombsNumber;

	CustomInitialization();
}

void Console::PrintCells()
{
	int rowNumber = m_board.GetBoardSizeRow();
	int columnNumber = m_board.GetBoardSizeColumn();

	for (int indexRow = 0; indexRow < rowNumber; indexRow++)
	{
		for (int indexColumn = 0; indexColumn < columnNumber; indexColumn++)
		{
			auto cell = m_board.GetBoardCell(indexRow, indexColumn);
			if (cell.isHidden())
			{
				if (cell.IsFlag())
					std::cout << "!" << " ";
				else
					std::cout << "*" << " ";
			}
			else
			{
				auto cellType = cell.GetType();

				switch (cellType)
				{
				case CellType::Bomb:
				{
					std::cout << "@" << " ";
					break;
				}
				case CellType::Number:
				{
					std::cout << this->m_board.GetBoardValue(indexRow, indexColumn) << " ";
					break;
				}
				case CellType::Empty:
				{
					std::cout << "0" << " ";
					break;
				}
				}
			}

		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

Console::Position Console::GetPosition()
{
	int rowPosition, columnPosition;
	std::cout << "Enter the row position: ";
	std::cin >> rowPosition;
	std::cout << "Enter the column position: ";
	std::cin >> columnPosition;
	std::cout << std::endl;

	try
	{
		bool rowResponse = CheckRowNumber(rowPosition);
		bool columnResponse = CheckColumnNumber(columnPosition);

		switch (rowResponse)
		{
		case false:
			if (columnResponse)
				throw "Please enter a valid row number !";
			else
				throw "Please enter valid row and column numbers !";
			break;
		case true:
			if (!columnResponse)
				throw "Please enter a valid column number !";
			break;
		}
	}
	catch (const char* message)
	{
		m_logger.Log(message, LoggerClass::Level::WARNING);
		return this->GetPosition();
	}

	Position position(rowPosition, columnPosition);
	return position;
}

int Console::GetAction()
{
	int decision;
	std::cout << "Which action do you want to take" << std::endl;
	std::cout << "- 1: Select a cell" << std::endl;
	std::cout << "- 2: Add a flag on a cell" << std::endl;
	std::cin >> decision;

	while (decision != 1 && decision != 2)
	{
		m_logger.Log("Please, select a valid number!", LoggerClass::Level::WARNING);
		std::cin >> decision;
	}

	switch (decision)
	{
	case 1:
		return 1;
	case 2:
		return 2;
	}
}

bool Console::CheckCustom()
{
	if (m_row <= 0)
	{
		m_logger.Log("Number of rows should be greater than 0", LoggerClass::Level::WARNING);
		return false;
	}

	if (m_column <= 0)
	{
		m_logger.Log("Number of columns should be greater than 0", LoggerClass::Level::WARNING);
		return false;
	}

	if (m_row * m_column < m_bombsNumber)
	{
		m_logger.Log("RowNr * ColumnNr should be greater than the number of bombs", LoggerClass::Level::WARNING);
		return false;
	}

	return true;
}

void Console::CustomInitialization()
{
	while (!CheckCustom())
	{
		CustomValues();
	}

	FetchGameType values(m_row, m_column, m_bombsNumber);
	m_values = values;
}

bool Console::CheckRowNumber(int rowNumber)
{
	auto rowSize = m_board.GetBoardSizeRow();

	if (rowNumber < 1 || rowNumber > rowSize)
		return false;

	return true;

}

bool Console::CheckColumnNumber(int columnNumber)
{
	auto columnSize = m_board.GetBoardSizeColumn();
	if (columnNumber < 1 || columnNumber > columnSize)
		return false;

	return true;
}

void Console::CheckIfWin()
{
	if (!m_gameWon)
	{
		m_gameWon = m_board.CheckIfWin();
		if (m_gameWon)
		{
			int duration = (std::clock() - start) / CLOCKS_PER_SEC;
			std::string str = "Congratulations " + m_userName + ", you won! " + "You played for " + std::to_string(duration) + " seconds.";
			m_logger.Log(str, LoggerClass::Level::INFO);
		}
	}
}

void Console::SetUserName(const std::string& name)
{
	m_userName = name;
}

std::string Console::GetUserName()
{
	return m_userName;
}

GameType Console::GetGameType()
{
	return m_gameType;
}

void Console::SetGameType(GameType gameType)
{
	m_gameType = gameType;
}

void Console::SetValues(FetchGameType values)
{
	m_values = values;
}

int Console::GetRow()
{
	return m_row;
}

int Console::GetColumn()
{
	return m_column;
}

int Console::GetBombsNumber()
{
	return m_bombsNumber;
}

Board Console::GetBoard()
{
	return m_board;
}

FetchGameType Console::GetValue()
{
	return m_values;
}

void Console::SetRow(const int& row)
{
	m_row = row;
}

void Console::SetColumn(const int& column)
{
	m_column = column;
}

void Console::SetBombsNumber(const int& bombsNumber)
{
	m_bombsNumber = bombsNumber;
}