#include "Run.h"

void Run::UserInput()
{
	sf::RenderWindow window(sf::VideoMode(400, 250), "UserOption");
	SetWindowIcon(window);
	int pressedButton;
	std::string input;
	bool nameAdded = true;

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::TextEntered)
				if (event.text.unicode >= 65 && event.text.unicode <= 128)
				{
					input += event.text.unicode;
					Run::SetUserName(input);
				}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
			{
				if (input.size())
				{
					input.pop_back();
					Run::SetUserName(input);
				}
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				pressedButton = GetPressedText(event.mouseButton.x, event.mouseButton.y);
				if (pressedButton == 0)
				{
					if (CheckIfNameAdded(input))
					{
						window.close();
						RunGUI();
					}
					else
					{
						nameAdded = false;
					}
				}
				else if (pressedButton == 1)
				{
					if (CheckIfNameAdded(input))
					{
						window.close();
						RunConsole();
					}
					else
					{
						nameAdded = false;
					}
				}
			}
		}
		window.clear(sf::Color::Black);
		RenderText(window, "GUI", 35, std::make_pair(90.0f, 80.0f));
		RenderText(window, "Console", 35, std::make_pair(200.0f, 80.0f));
		RenderText(window, "Enter your name:", 25, std::make_pair(40.0f, 20.0f));
		RenderText(window, input, 25, std::make_pair(250.0f, 20.0f));
		if (!nameAdded)
		{
			RenderText(window, "Please add a name!", 25, std::make_pair(100.0f, 150.0f));
		}
		window.display();
	}
}

void Run::RunGUI()
{
	GUI gui;
	gui.RenderWindow();
}

void Run::RunConsole()
{
	Console console(GetUserName());
	console.PlayGame();
}

void Run::RenderText(sf::RenderWindow& window, std::string inputText, int size, std::pair<float, float> position)
{
	sf::Font font;
	sf::Text text;
	sf::Color color(102, 186, 212);

	text.setPosition(sf::Vector2f(position.first, position.second));
	text.setCharacterSize(size);
	text.setFillColor(color);

	if (!font.loadFromFile("sansation.ttf"))
	{
		m_logger.Log("Error loading font", LoggerClass::Level::ERROR);
	}

	text.setFont(font);
	text.setString(inputText);
	window.draw(text);
}

int Run::GetPressedText(int mouseCoordX, int mouseCoordY)
{
	if (mouseCoordX >= 90 && mouseCoordX <= 150 && mouseCoordY >= 80 && mouseCoordY <= 120)
		return 0;

	if (mouseCoordX >= 200 && mouseCoordX <= 350 && mouseCoordY >= 80 && mouseCoordY <= 120)
		return 1;

	return -1;
}

void Run::SetWindowIcon(sf::RenderWindow& window)
{
	sf::Image icon;
	icon.loadFromFile("Boss_Face.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

bool Run::CheckIfNameAdded(std::string input)
{
	if (input.size() == 0)
		return false;
	return true;
}

std::string Run::userName;
void Run::SetUserName(std::string input)
{
	Run::userName = input;
}

std::string Run::GetUserName()
{
	return Run::userName;
}
