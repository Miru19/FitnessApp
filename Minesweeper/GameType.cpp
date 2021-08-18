#include "GameType.h"

GameType ConvertingToGameType(const std::string& other)
{
	std::map<std::string, GameType> mapDecision = {
		{"Easy", GameType::Easy},
		{"Intermediate", GameType::Intermediate},
		{"Advanced", GameType::Advanced},
		{"Custom", GameType::Custom},
		{"None", GameType::None}
	};

	return mapDecision[other];
}

std::string ConvertGameTypeToString(const GameType& other)
{
	std::map<GameType, std::string> mapDecision = {
		{GameType::Easy, "Easy"},
		{GameType::Intermediate, "Intermediate"},
		{GameType::Advanced, "Advanced"},
		{GameType::Custom, "Custom"},
		{GameType::None, "None"}
	};

	return mapDecision[other];
}
