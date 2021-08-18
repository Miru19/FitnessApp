#pragma once
#include<cstdint>
#include<string>
enum class CellType : uint8_t
{
	Number,
	Empty,
	Bomb,
	None,

};
std::string ConvertCellTypeToString(CellType other);
CellType ConvertStringToCellType(const std::string& other);
