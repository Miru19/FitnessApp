#pragma once
#include<iostream>
#include "GUI.h"
#include "Console.h"
#include "../LoggingDLL/Logger.h"
class Run
{
public:
	void UserInput();
	static void SetUserName(std::string input);
	static std::string GetUserName();
private:
	bool CheckIfNameAdded(std::string);
	void RunGUI();
	void RunConsole();
	void RenderText(sf::RenderWindow &, std::string, int, std::pair<float, float>);
	int GetPressedText(int, int);
	void SetWindowIcon(sf::RenderWindow&);
	static std::string userName;
	LoggerClass m_logger;
};
