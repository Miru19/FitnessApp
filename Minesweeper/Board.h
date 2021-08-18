#pragma once
#include "Cell.h"
#include <vector>
#include <utility>
#include "FetchGameType.h"


class Board
{

public:
	Board();
	Board(GameType, FetchGameType);
	Board(const Board&);
	Board(Board&&)noexcept;
	~Board();
	Board& operator = (const Board&);
	Board& operator = (Board&&)noexcept;

	void SetFirstMove(bool value);
	void SetNumberOfFlags(int, int);

	Cell& GetBoardCell(int,int);
	int GetBoardValue(int, int);
	int GetBoardSizeRow() const;
	int GetBoardSizeColumn() const;
	int GetNumberOfBombs() const;
	const std::vector<std::vector<int>>& GetMatrixValue() const;
	GameType GetType()const;
	int GetNumberOfFlags() const;

	void InitializeMatrix();
	std::pair<int, int> GenerateBombs();
	void MarkBombs();
	void GenerateMatrixValues();
	void GenerateMatrixCell();

	void ReplaceMineOnFirstMove(int, int);
	bool OpenNeighboursOnClick(int, int);
	bool CheckIfWin();
	void ShowMines();

	bool operator==(const Board&);
	friend std::ostream& operator<<(std::ostream&, const Board&);

private:
	void GenerateNeighboursValues();
	bool IsValid(int, int, int);
	bool IsNumber(int, int);

private:
	std::vector<std::vector<Cell>>m_boardCell;
	std::vector<std::vector<int>>m_boardValue;
	GameType m_gameType;
	int m_boardSizeRow;
	int m_boardSizeColumn;
	int m_numberOfBombs;
	std::vector< std::pair<int, int>> m_neighbours;
	bool m_firstMove = true;
	int m_numberOfFlags;
};

