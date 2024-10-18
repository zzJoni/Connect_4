#pragma once
#include <string>
#include <string_view>

// Represents one of the players
class Player
{
public:
	Player(std::string_view name, char symbol);
	
	// Getters
	const std::string& getName() const { return m_name; }
	char getSymbol() const { return m_symbol; }


private:
	const std::string m_name{};
	const char m_symbol{};
};
