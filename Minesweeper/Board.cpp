#include "Board.h"
#include <random>
#include <map>
#include <variant>

void Board::GenerateNeighboursValues()
{
	for (int indexRow = -1; indexRow <= 1; indexRow++)
		for (int indexColumn = -1; indexColumn <= 1; indexColumn++)
			m_neighbours.push_back(std::make_pair(indexRow, indexColumn));
}

bool Board::IsValid(int indexRow, int indexColumn, int indexN)
{
	if (indexRow + m_neighbours[indexN].first >= 0 && indexRow + m_neighbours[indexN].first < m_boardSizeRow &&
		indexColumn + m_neighbours[indexN].second >= 0 && indexColumn + m_neighbours[indexN].second < m_boardSizeColumn)
		return true;
	return false;
}

void Board::ShowMines()
{
	for (int indexRow = 0; indexRow < m_boardSizeRow; indexRow++)
	{
		for (int indexColumn = 0; indexColumn < m_boardSizeColumn; indexColumn++)
		{
			if (m_boardCell[indexRow][indexColumn].GetType() == CellType::Bomb)
			{
				m_boardCell[indexRow][indexColumn].SetCellHide();
			}
		}
	}
}

void Board::SetFirstMove(bool value)
{
	this->m_firstMove = value;
}

bool Board::IsNumber(int indexR, int indexC)
{
	return m_boardCell[indexR][indexC].GetType() == CellType::Number;
}

Board::Board()
	:m_boardSizeColumn{ 0 }, m_boardSizeRow{ 0 }, m_gameType{ GameType::None }, m_numberOfBombs{ 0 }, m_numberOfFlags{ 0 }
{
}

Board::Board(GameType type, FetchGameType values)
{
	this->m_gameType = type;
	m_numberOfBombs = values(m_gameType, "bombNumber");
	m_numberOfFlags = m_numberOfBombs;

	if (m_gameType != GameType::Custom)
	{
		m_boardSizeRow = values(m_gameType, "boardSize");
		m_boardSizeColumn = m_boardSizeRow;
	}
	else {
		m_boardSizeRow = values(m_gameType, "boardRow");
		m_boardSizeColumn = values(m_gameType, "boardColumn");
	}

	auto intializeMatrix = [this]()
	{
		this->m_boardValue = std::vector<std::vector<int>>(m_boardSizeRow, std::vector<int>(m_boardSizeColumn));
		this->m_boardCell = std::vector<std::vector<Cell>>(m_boardSizeRow, std::vector<Cell>(m_boardSizeColumn));
	};

	intializeMatrix();
	GenerateNeighboursValues();
}

Board::Board(const Board& other)
{
	*this = other;
}

Board::Board(Board&& other)noexcept
{
	*this = std::move(other);
}

Board& Board::operator=(const Board& other)
{
	if (this != &other)
	{
		m_boardCell = other.m_boardCell;
		m_boardValue = other.m_boardValue;
		m_boardSizeRow = other.m_boardSizeRow;
		m_boardSizeColumn = other.m_boardSizeColumn;
		m_gameType = other.m_gameType;
		m_numberOfBombs = other.m_numberOfBombs;
		m_neighbours = other.m_neighbours;
		m_numberOfFlags = other.m_numberOfFlags;
	}

	return *this;
}

Board& Board::operator=(Board&& other)noexcept
{
	if (this != &other)
	{
		m_boardCell = other.m_boardCell;
		m_boardValue = other.m_boardValue;
		m_boardSizeRow = other.m_boardSizeRow;
		m_boardSizeColumn = other.m_boardSizeColumn;
		m_gameType = other.m_gameType;
		m_numberOfBombs = other.m_numberOfBombs;
		m_neighbours = other.m_neighbours;
		m_numberOfFlags = other.m_numberOfFlags;

		new(&other)Board();
	}

	return *this;
}

Cell& Board::GetBoardCell(int indexRow, int indexColumn)
{
	return m_boardCell[indexRow][indexColumn];
}

int Board::GetBoardValue(int indexRow, int indexColumn)
{
	return m_boardValue[indexRow][indexColumn];
}

Board::~Board()
{
}

void Board::ReplaceMineOnFirstMove(int indexR, int indexC)
{
	bool find = false;
	for (int indexRow = 0; indexRow < m_boardSizeRow && !find; indexRow++)
	{
		for (int indexColumn = 0; indexColumn < m_boardSizeColumn && !find; indexColumn++)
		{
			if (m_boardValue[indexRow][indexColumn] != 9)
			{
				m_boardValue[indexRow][indexColumn] = 9;
				m_boardValue[indexR][indexC] = 0;
				find = true;

			}
		}
	}

	GenerateMatrixValues();
	GenerateMatrixCell();
}

bool Board::OpenNeighboursOnClick(int indexR, int indexC)
{
	if (m_firstMove)
	{
		this->SetFirstMove(false);
		if (m_boardCell[indexR][indexC].GetType() == CellType::Bomb)
		{
			ReplaceMineOnFirstMove(indexR, indexC);
		}
	}

	if (!m_boardCell[indexR][indexC].isHidden() || m_boardCell[indexR][indexC].IsFlag())
		return false;

	m_boardCell[indexR][indexC].SetCellHide();

	if (m_boardCell[indexR][indexC].GetType() == CellType::Bomb)
	{
		ShowMines();
		return true;
	}

	if (m_boardCell[indexR][indexC].GetType() == CellType::Number)
	{
		return false;
	}

	for (int indexN = 0; indexN < m_neighbours.size(); indexN++)
	{
		if (IsValid(indexR, indexC, indexN))
		{
			OpenNeighboursOnClick(indexR + m_neighbours[indexN].first, indexC + m_neighbours[indexN].second);
		}
	}

	return false;
}

void Board::InitializeMatrix()
{
	for (int indexRow = 0; indexRow < m_boardSizeRow; indexRow++)
	{
		for (int indexColumn = 0; indexColumn < m_boardSizeColumn; indexColumn++)
			m_boardValue[indexRow][indexColumn] = 0;

	}
}

bool Board::operator==(const Board& other)
{
	if (this->m_boardValue == other.m_boardValue && this->m_boardSizeRow == other.m_boardSizeRow
		&& this->m_boardSizeColumn == other.m_boardSizeColumn && this->m_gameType == other.m_gameType
		&& this->m_numberOfBombs == other.m_numberOfBombs && this->m_neighbours == other.m_neighbours)
		return true;
	return false;
}

int Board::GetBoardSizeRow() const
{
	return m_boardSizeRow;
}

int Board::GetBoardSizeColumn() const
{
	return m_boardSizeColumn;
}

int Board::GetNumberOfBombs() const
{
	return m_numberOfBombs;
}

GameType Board::GetType() const
{
	return this->m_gameType;
}

void Board::GenerateMatrixCell()
{
	for (int indexRow = 0; indexRow < m_boardValue.size(); indexRow++)
		for (int indexColumn = 0; indexColumn < m_boardValue[indexRow].size(); indexColumn++)
		{
			switch (m_boardValue[indexRow][indexColumn])
			{
			case 0:
				m_boardCell[indexRow][indexColumn].SetCellType(CellType::Empty);
				break;
			case 9:
				m_boardCell[indexRow][indexColumn].SetCellType(CellType::Bomb);
				break;
			default:
				m_boardCell[indexRow][indexColumn].SetCellType(CellType::Number);
				break;
			}
		}
}

std::pair<int, int> Board::GenerateBombs()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> lineIndex(0, m_boardSizeRow - 1);
	std::uniform_int_distribution<int> columnIndex(0, m_boardSizeColumn - 1);
	std::pair<int, int> bombCoordinates = std::make_pair(lineIndex(mt), columnIndex(mt));

	return bombCoordinates;
}

void Board::MarkBombs()
{
	for (int index = 0; index < m_numberOfBombs; index++)
	{
		std::pair<int, int> coordinates = GenerateBombs();
		if (m_boardValue[coordinates.first][coordinates.second] == 9)
		{
			index--;
		}
		else
		{
			m_boardValue[coordinates.first][coordinates.second] = 9;
		}
	}
}

void Board::GenerateMatrixValues()
{
	for (int indexRow = 0; indexRow < m_boardSizeRow; indexRow++)
		for (int indexColumn = 0; indexColumn < m_boardSizeColumn; indexColumn++)
		{
			if (m_boardValue[indexRow][indexColumn] != 9)
			{
				int nrBombs = 0;
				for (int indexN = 0; indexN < m_neighbours.size(); indexN++)
				{
					if (IsValid(indexRow, indexColumn, indexN))
					{
						int indexAuxR = indexRow + m_neighbours[indexN].first;
						int indexAuxC = indexColumn + m_neighbours[indexN].second;
						if (m_boardValue[indexAuxR][indexAuxC] == 9)
						{
							nrBombs++;
						}
					}
				}
				m_boardValue[indexRow][indexColumn] = nrBombs;
			}
		}
}

void Board::SetNumberOfFlags(int indexRow, int indexColumn)
{
	if (m_boardCell[indexRow][indexColumn].IsFlag())
		m_numberOfFlags--;
	else
		if (m_boardCell[indexRow][indexColumn].isHidden())
			m_numberOfFlags++;
}

int Board::GetNumberOfFlags() const
{
	return m_numberOfFlags;
}

const std::vector<std::vector<int>>& Board::GetMatrixValue() const
{
	return this->m_boardValue;
}

std::ostream& operator<<(std::ostream& write, const Board& other)
{
	write << "Board size: " << other.m_boardSizeRow << std::endl;
	write << "Number of bombs: " << other.m_numberOfBombs << std::endl;
	write << "Game type: " << ConvertGameTypeToString(other.m_gameType) << std::endl;
	return write;
}

bool Board::CheckIfWin()
{
	if (m_numberOfFlags != 0)
		return false;
	
	for (int indexRow = 0; indexRow < m_boardCell.size(); indexRow++)
		for (int indexCol = 0; indexCol < m_boardCell[indexRow].size(); indexCol++)
			if (m_boardCell[indexRow][indexCol].GetType() != CellType::Bomb && m_boardCell[indexRow][indexCol].isHidden() == true)
				return false;

	return true;
}
