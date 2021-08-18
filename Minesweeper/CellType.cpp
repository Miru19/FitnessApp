#include "CellType.h"
#include<map>

std::string ConvertCellTypeToString(CellType other)
{
	std::map<CellType, std::string> mapDecision = {
		{CellType::Bomb,"Bomb" },
		{CellType::Empty, "Empty" },
		{CellType::Number, "Number"},
		{CellType::None, "No value"}
	};
	return mapDecision[other];
}

CellType ConvertStringToCellType(const std::string& other)
{
	std::map<std::string, CellType> mapDecision = {
		{"Bomb", CellType::Bomb},
		{"Empty", CellType::Empty },
		{"Number", CellType::Number },
		{"No value", CellType::None}
	};
	return mapDecision[other];
}