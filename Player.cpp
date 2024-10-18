#include "Player.h"
#include <string>
#include <string_view>
#include <cassert>

Player::Player(std::string_view name, char symbol) 
	: m_name{ name }, m_symbol{ symbol }
{
	assert(m_symbol != ' ' && "Invalid Player Symbol");
}
