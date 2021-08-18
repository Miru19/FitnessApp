#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Audio/Music.hpp>
#include"../LoggingDLL/Logger.h"
#include <iostream>
#include <vector>
#include <thread>
#include "Board.h"
#include "Run.h"

class GUI
{
public:
	using MatrixPosition = std::pair<int, int>;
	using DisplayPosition = std::pair<float, float>;

public:
	GUI();
	void AddImageNames();
	void SetWindowIcon();
	void RenderWindow();
	void RenderImages();
	void RenderCellImage(std::string, MatrixPosition, DisplayPosition);
	void AddCellPosition(int, int);
	void RenderText(std::string, DisplayPosition, int, bool);
	void GameInitialization();
	void RenderGameWindow();
	void RenderBackground();
	void RenderCells(int, int);
	void FindCell(MatrixPosition, bool);
	void SetCustomContent();
	void RenderCustomElements();
	int GetPressedButton(int, int);
	bool CheckIfCustomCorrect();
	void IncDecCustom();
	int SetCustomIndex();
	void StopThread();
	void RenderMusic(std::string, sf::Music&);

private:
	std::vector<std::pair<std::string, DisplayPosition>> m_imagesSource;

	std::vector<DisplayPosition>m_customTextPosition;
	std::vector<std::pair< std::string, DisplayPosition>> m_customElements;
	std::vector<std::pair<int, DisplayPosition>> m_inputCustom;
	int m_customIndex;

	sf::RenderWindow m_window;
	sf::Image m_icon;

	GameType m_gameType;
	FetchGameType m_values;

	std::vector<std::pair<DisplayPosition, MatrixPosition>> m_cellPosition;
	Board m_board;

	bool m_gameOver;
	bool m_gameWon;
	LoggerClass m_logger;
};
