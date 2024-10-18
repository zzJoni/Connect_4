#pragma once
#include <vector>
#include <iostream>

class Connect4Board 
{
public:
	explicit Connect4Board(const int width = 7, const int height = 6, const int winNumber = 4);

	// Prints the board (padding specifies the offset from left)
	void print(const int padding = 0) const;

	// Places a disk into the connect 4 board (returns false if failed)
	bool placeDisk(const int column, const char symbol);

	// Get functions
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	int getWinNumber() const { return m_winNumber; }
	int maxTurns() const { return (m_width * m_height); }

	// Checks to see if the most recently placed disk has caused a win (returns the char of that disk)
	char checkForWinner(const int mostRecentColumn) const;

private:	
	using Board = std::vector<std::vector<char>>;

	// Dimensions of the board
	const int m_width{ 7 };
	const int m_height{ 6 };
	
	// Number of disks that you need to connect to win
	const int m_winNumber{ 4 };
	
	// Default initializes an empty board based on above sizes
	Board m_board{ 
		static_cast<std::size_t>(m_height),
		std::vector<char>(static_cast<std::size_t>(m_width), ' ')};
};
