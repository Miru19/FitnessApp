#pragma once
#include "FetchGameType.h"
#include <map>
#include<iostream>
#include "GameType.h"


struct FetchGameType
{
private:

	std::map<GameType, std::map<std::string, int>> m_DecisionMap;

	void CreateMap(std::map<std::string, int>);

public:
	FetchGameType();
	FetchGameType(int, int, int);
	int operator () (GameType, std::string);
	
};
