#include "FetchGameType.h"

void FetchGameType::CreateMap(std::map<std::string, int> customMap = {})
{
	std::map<std::string, int> easyMap = { std::make_pair("boardSize", 9), std::make_pair("bombNumber", 10) };
	std::map<std::string, int> intermediateMap = { std::make_pair("boardSize", 16), std::make_pair("bombNumber", 46) };
	std::map<std::string, int> advancedMap = { std::make_pair("boardSize", 24), std::make_pair("bombNumber", 99) };

	this->m_DecisionMap = {
	{GameType::Easy, easyMap},
	{GameType::Intermediate, intermediateMap},
	{GameType::Advanced, advancedMap},
	{GameType::Custom, customMap}
	};
}

FetchGameType::FetchGameType()
{
	CreateMap();
}

FetchGameType::FetchGameType(int boardRow, int boardColumn, int bombNumber)
{
	std::map<std::string, int> customMap = { std::make_pair("boardRow", boardRow), std::make_pair("boardColumn",boardColumn), std::make_pair("bombNumber",bombNumber) };

	CreateMap(customMap);
}

int FetchGameType::operator()(GameType gameType, std::string str)
{
	std::map<std::string, int> result = m_DecisionMap[gameType];
	return result[str];
}
