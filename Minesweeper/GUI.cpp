#include "GUI.h"

int GUI::GetPressedButton(int mouseX, int mouseY)
{

	if (mouseX >= 80 && mouseX <= 210 && mouseY >= 100 && mouseY <= 155)
	{
		std::string str = Run::GetUserName() + " has choosen easy mode";
		m_logger.Log(str, LoggerClass::Level::INFO);
		m_gameType = GameType::Easy;

		return 1;
	}

	if (mouseX >= 280 && mouseX <= 400 && mouseY >= 100 && mouseY <= 155)
	{
		std::string str = Run::GetUserName() + " has choosen medium mode";
		m_logger.Log(str, LoggerClass::Level::INFO);
		m_gameType = GameType::Intermediate;

		return 2;
	}

	if (mouseX >= 80 && mouseX <= 210 && mouseY >= 200 && mouseY <= 255)
	{
		std::string str = Run::GetUserName() + " has choosen hard mode";
		m_logger.Log(str, LoggerClass::Level::INFO);
		m_gameType = GameType::Advanced;

		return 3;
	}

	if (mouseX >= 280 && mouseX <= 400 && mouseY >= 200 && mouseY <= 255)
	{
		std::string str = Run::GetUserName() + " has choosen custom mode";
		m_logger.Log(str, LoggerClass::Level::INFO);
		m_gameType = GameType::Custom;
		SetCustomContent();
		return 4;
	}

	return -1;
}

void GUI::RenderBackground()
{
	sf::Sprite background;
	sf::Texture backgroundImg;
	backgroundImg.loadFromFile("background.jpg");
	background.setTexture(backgroundImg);
	m_window.draw(background);
}

void GUI::RenderImages()
{
	for (auto imageSource : m_imagesSource)
	{
		sf::Sprite sprite;
		sf::Texture spriteImg;
		spriteImg.loadFromFile(imageSource.first);
		sprite.setTexture(spriteImg);

		sprite.setPosition(static_cast<float>(imageSource.second.first), static_cast<float>(imageSource.second.second));
		m_window.draw(sprite);
	}
}

void GUI::RenderCellImage(std::string imageSource, MatrixPosition matrixPos, DisplayPosition displayPos)
{
	auto& [indexRow, indexColumn] = matrixPos;
	auto& [coordX, coordY] = displayPos;

	sf::Sprite sprite;
	sf::Texture spriteImg;
	spriteImg.loadFromFile(imageSource);

	sprite.setTexture(spriteImg);
	sprite.setPosition(coordX, coordY);

	if (indexRow != -1) {
		AddCellPosition(indexRow, indexColumn);
	}

	m_window.draw(sprite);
}

void GUI::AddCellPosition(int indexRow, int indexColumn)
{
	MatrixPosition cell_position(indexColumn * Cell::GetHeight(), indexRow * Cell::GetHeight());
	MatrixPosition cell_index(indexRow, indexColumn);
	std::pair<MatrixPosition, MatrixPosition> vector_input(cell_position, cell_index);

	m_cellPosition.push_back(vector_input);
}

void GUI::RenderText(std::string textInput, DisplayPosition position, int textSize = 35, bool renderAnotherColor = false)
{
	sf::Font font;
	sf::Text text;
	sf::Color color(15, 72, 89);

	if (renderAnotherColor)
	{
		sf::Color choosenColor(255, 255, 255);
		color = choosenColor;
	}

	auto& [coordX, coordY] = position;
	text.setPosition(sf::Vector2f(coordX, coordY));
	text.setCharacterSize(textSize);
	text.setFillColor(color);

	if (!font.loadFromFile("sansation.ttf"))
	{
		std::cout << "Error loading font\n";
	}
	text.setFont(font);
	text.setString(textInput);

	m_window.draw(text);
}

void GUI::RenderCells(int boardHeight, int boardWidth)
{
	for (int indexRow = 0; indexRow < boardHeight; indexRow++)
	{
		for (int indexColumn = 0; indexColumn < boardWidth; indexColumn++)
		{
			auto cell = m_board.GetBoardCell(indexRow, indexColumn);

			MatrixPosition matrixPos(indexRow, indexColumn);
			float displayPosX = static_cast<float>(indexColumn * Cell::GetHeight());
			float displayPosY = static_cast<float>(indexRow * Cell::GetHeight() + 50);
			DisplayPosition displayPos(displayPosX, displayPosY);

			if (cell.isHidden()) {

				std::string imageSource = "cell.png";
				if (cell.IsFlag())
					imageSource = "flag.png";

				RenderCellImage(imageSource, matrixPos, displayPos);
			}
			else
			{
				auto cellType = cell.GetType();

				switch (cellType)
				{
				case CellType::Bomb:
				{
					RenderCellImage("bomb.png", matrixPos, displayPos);
					break;
				}
				case CellType::Number:
				{
					int number = m_board.GetBoardValue(indexRow, indexColumn);
					std::string image_name = std::to_string(number) + ".png";
					RenderCellImage(image_name, matrixPos, displayPos);
					break;

				}
				case CellType::Empty:
				{
					RenderCellImage("empty.png", matrixPos, displayPos);
					break;
				}
				}
			}
		}
	}
}

void GUI::FindCell(MatrixPosition position, bool leftButton)
{
	auto& [coordx, coordy] = position;
	for (auto cell : m_cellPosition)
	{
		auto& [displayX, displayY] = cell.first;
		auto& [matrixX, matrixY] = cell.second;

		if (displayX + 30 >= coordx && displayY + 30 + 50 >= coordy &&
			displayX <= coordx && displayY + 50 <= coordy)
		{
			if (leftButton)
			{
				std::string str = Run::GetUserName() + " pressed on row with number " + std::to_string((matrixY + 1)) + " and column with number " + std::to_string((matrixX + 1));
				m_logger.Log(str, LoggerClass::Level::INFO);
				m_gameOver = m_board.OpenNeighboursOnClick(matrixX, matrixY);
				if (m_gameOver)
				{
					std::string str = "Sorry, " + Run::GetUserName() + ", you lost!";
					m_logger.Log(str, LoggerClass::Level::INFO);
				}
			}
			else
			{
				if (m_board.GetNumberOfFlags() != 0 ||
					(m_board.GetNumberOfFlags() == 0 && m_board.GetBoardCell(matrixX, matrixY).IsFlag() == true))
				{
					m_board.GetBoardCell(matrixX, matrixY).SetCellFlag();
					m_board.SetNumberOfFlags(matrixX, matrixY);
				}

				std::string str = Run::GetUserName() + " has " + std::to_string(m_board.GetNumberOfFlags()) + " flags left";
				m_logger.Log(str, LoggerClass::Level::INFO);
			}
			break;
		}
	}
}

void GUI::SetCustomContent()
{
	m_customTextPosition.push_back(std::make_pair(170, 120));
	m_customTextPosition.push_back(std::make_pair(170, 180));
	m_customTextPosition.push_back(std::make_pair(170, 240));

	m_customElements.push_back(std::make_pair("Enter yout choices:", std::make_pair<int, int>(20, 50)));
	m_customElements.push_back(std::make_pair("Rows:", std::make_pair<int, int>(20, 120)));
	m_customElements.push_back(std::make_pair("Columns:", std::make_pair<int, int>(20, 180)));
	m_customElements.push_back(std::make_pair("Bombs:", std::make_pair<int, int>(20, 240)));

	m_inputCustom.push_back(std::make_pair(1, std::make_pair(205, 125)));
	m_inputCustom.push_back(std::make_pair(1, std::make_pair(205, 185)));
	m_inputCustom.push_back(std::make_pair(1, std::make_pair(205, 245)));
}

void GUI::RenderCustomElements()
{
	sf::Color color(136, 136, 136);
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(100, 50));
	const int textSize = 35;

	for (auto position : m_customTextPosition)
	{
		rectangle.setFillColor(color);
		rectangle.setOutlineColor(sf::Color::Black);
		rectangle.setOutlineThickness(2);
		rectangle.setPosition(position.first, position.second);
		m_window.draw(rectangle);
	}

	for (int index = 0; index < m_inputCustom.size(); index++)
	{
		bool renderAnotherColor = false;
		auto& [number, position] = m_inputCustom[index];
		std::string text = std::to_string(number);
		if (m_customIndex == index)
			renderAnotherColor = true;
		RenderText(text, position, textSize, renderAnotherColor);
	}

	for (auto element : m_customElements)
	{
		RenderText(element.first, element.second, 30);
	}

	const std::string rules = "Inc: Ctrl Up \nDecr: Ctrl Down \nChange: Up/Down \nStart: Right arrow ";
	RenderText(rules, std::make_pair(300, 130), 23);
}

bool GUI::CheckIfCustomCorrect()
{
	int rows = m_inputCustom[0].first;
	int columns = m_inputCustom[1].first;
	int bombs = m_inputCustom[2].first;

	if (rows * columns < bombs)
	{
		DisplayPosition position = std::make_pair(20, 300);
		std::string str = "The number of bombs is greater than board!";
		RenderText(str, position, 20);
		return false;
	}
	return true;
}

void GUI::IncDecCustom()
{
	StopThread();
	int newValue;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		newValue = m_inputCustom[m_customIndex].first + 1;
		if (newValue > 100)
			return;
		m_inputCustom[m_customIndex].first++;
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		newValue = m_inputCustom[m_customIndex].first - 1;
		if (newValue < 1)
			return;
		m_inputCustom[m_customIndex].first--;
		return;
	}
}

int GUI::SetCustomIndex()
{
	StopThread();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_customIndex--;
		if (m_customIndex < 0)
			m_customIndex = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_customIndex++;
		if (m_customIndex > 2)
			m_customIndex = 2;
	}
	return 1;
}

void GUI::StopThread()
{
	using namespace std::chrono_literals;
	auto start = std::chrono::high_resolution_clock::now();
	std::this_thread::sleep_for(5ms);

}

void GUI::RenderMusic(std::string musicName, sf::Music& music)
{
	if (!music.openFromFile(musicName))
		return;
	music.play();

}

void GUI::GameInitialization()
{
	Board board(m_gameType, m_values);
	m_board = board;

	m_board.MarkBombs();
	m_board.GenerateMatrixValues();
	m_board.GenerateMatrixCell();
	std::string str = "Good luck " + Run::GetUserName() + "! Game started!";
	m_logger.Log(str, LoggerClass::Level::INFO);
}

void GUI::RenderGameWindow()
{
	GameInitialization();

	int boardHeight = m_board.GetBoardSizeRow();
	int boardWidth = m_board.GetBoardSizeColumn();
	int timerValue = 0;

	this->m_window.create(sf::VideoMode(boardWidth * Cell::GetHeight(), boardHeight * Cell::GetHeight() + 50), "Play Game");
	SetWindowIcon();

	sf::Clock clock;

	sf::Time timer = clock.getElapsedTime();

	MatrixPosition matrixPos(-1, -1);
	float displayPosX = static_cast<float>(m_window.getSize().x / 2 - Cell::GetHeight());
	float displayPosY = 0.0F;
	DisplayPosition displayPos(displayPosX, displayPosY);

	float textPosX = static_cast<float>(m_window.getSize().x - 50);
	float textPosY = 10.0F;
	DisplayPosition textPos(textPosX, textPosY);

	bool isPlayed = false;
	sf::Music music;
	RenderMusic("music.ogg", music);

	while (m_window.isOpen())
	{

		sf::Event event;

		while (m_window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				m_window.close();
			if (!m_gameOver && !m_gameWon) {
				if (event.type == sf::Event::MouseButtonPressed)
				{
					bool leftButton = true;
					if (event.mouseButton.button == sf::Mouse::Right)
						leftButton = false;
					MatrixPosition position(event.mouseButton.x, event.mouseButton.y);
					FindCell(position, leftButton);
				}
			}
		}

		sf::Color color(176, 176, 176);
		m_window.clear(color);

		timer = clock.getElapsedTime();

		RenderCells(boardHeight, boardWidth);

		if (!m_gameWon)
		{
			m_gameWon = m_board.CheckIfWin();
			if (m_gameWon)
			{
				std::string str = "Congratulations " + Run::GetUserName() + ", you won! ";
				m_logger.Log(str, LoggerClass::Level::INFO);
			}
		}

		if (m_gameOver)
		{
			if (!isPlayed)
			{
				isPlayed = true;
				RenderMusic("lost.ogg", music);
			}
			RenderCellImage("Dead_Face.png", matrixPos, displayPos);
			RenderText(std::to_string(timerValue), textPos);
		}
		else
		{
			if (m_gameWon)
			{
				if (!isPlayed)
				{
					isPlayed = true;
					RenderMusic("applause.ogg", music);
				}
				RenderCellImage("Boss_Face.png", matrixPos, displayPos);
				RenderText(std::to_string(timerValue), textPos);
			}
			else
			{
				RenderCellImage("Neutral_Face.png", matrixPos, displayPos);
				timerValue = (int)timer.asSeconds();
				RenderText(std::to_string(timerValue), textPos);
				RenderText(std::to_string(m_board.GetNumberOfFlags()), std::make_pair(0, 10));

			}
		}

		m_window.display();
	}
}

void GUI::RenderWindow()
{
	int pressedButton = 0;
	std::string input;
	bool isCorrect = false;

	std::string str = "Hello " + Run::GetUserName() + "!";
	m_logger.Log(str, LoggerClass::Level::INFO);

	while (m_window.isOpen())
	{
		sf::Event event;

		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::TextEntered)
				if (event.text.unicode < 128)
				{
					input += event.text.unicode;
				}

			if (event.type == sf::Event::Closed)
				m_window.close();
			if (event.type == sf::Event::MouseButtonPressed && pressedButton != 4)
			{
				pressedButton = GetPressedButton(event.mouseButton.x, event.mouseButton.y);
				if (pressedButton != -1 && pressedButton != 4)
				{
					m_window.close();
					RenderGameWindow();
				}
			}
		}
		m_window.clear(sf::Color::White);
		RenderBackground();

		if (pressedButton < 4)
		{
			RenderImages();
		}
		else
		{
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
			{
				SetCustomIndex();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
			{
				IncDecCustom();
			}
			RenderCustomElements();
			isCorrect = CheckIfCustomCorrect();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				if (isCorrect)
				{
					FetchGameType values(m_inputCustom[0].first, m_inputCustom[1].first, m_inputCustom[2].first);
					m_values = values;
					RenderGameWindow();

				}
			}

		}

		m_window.display();
	}
}

GUI::GUI() :
	m_gameOver{ false }, m_gameWon{ false }, m_customIndex{ 0 }
{
	sf::RenderWindow window;
	this->m_window.create(sf::VideoMode(500, 400), "Minesweeper");
	AddImageNames();
	SetWindowIcon();
}

void GUI::AddImageNames()
{
	m_imagesSource.push_back(std::make_pair("easy.png", std::make_pair(80, 100)));
	m_imagesSource.push_back(std::make_pair("intermediate.png", std::make_pair(280, 100)));
	m_imagesSource.push_back(std::make_pair("hard.png", std::make_pair(80, 200)));
	m_imagesSource.push_back(std::make_pair("custom.png", std::make_pair(280, 200)));
}

void GUI::SetWindowIcon()
{
	m_icon.loadFromFile("icon.jpg");
	m_window.setIcon(m_icon.getSize().x, m_icon.getSize().y, m_icon.getPixelsPtr());
}
