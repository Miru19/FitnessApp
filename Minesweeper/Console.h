#pragma once
#include "../LoggingDLL/Logger.h"
#include "Board.h"
#include <cstdio>
#include <ctime>

class Console
{
public:
	using Position = std::pair<int, int>;
public:
	Console();
	Console(const std::string&);
	void GameInitialization();
	int GetChoosenMode();
	void ChoosePosition();
	void PlayGame();
	void CustomValues();
	void PrintCells();
	void CustomInitialization();
	void CheckIfWin();
	Position GetPosition();
	int GetAction();
	bool CheckCustom();
	bool CheckRowNumber(int rowNumber);
	bool CheckColumnNumber(int columnNumber);
	
	void SetUserName(const std::string&);
	void SetGameType(GameType);
	void SetValues(FetchGameType);
	void SetRow(const int&);
	void SetColumn(const int&);
	void SetBombsNumber(const int&);
	std::string GetUserName();
	GameType GetGameType();
	int GetRow();
	int GetColumn();
	int GetBombsNumber();
	Board GetBoard();
	FetchGameType GetValue();

private:
	bool m_gameWon;
	bool m_gameOver;
	LoggerClass m_logger;
	Board m_board;
	GameType m_gameType;
	FetchGameType m_values;
	int m_row;
	int m_column;
	int m_bombsNumber;
	std::string m_userName;
	std::clock_t start;

};

