#pragma once
#include <cstdint>
#include <string>
#include <map>
enum class GameType : uint8_t {
	Easy = 0,
	Intermediate = 1,
	Advanced = 2,
	Custom = 3,
	None=4
};

GameType ConvertingToGameType(const std::string& other);
std::string ConvertGameTypeToString(const GameType& other);

