#include "Connect4Board.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

// Default Constructor
Connect4Board::Connect4Board(const int width, const int height, const int winNumber)
	: m_width{ width }, m_height{ height }, m_winNumber{ winNumber }
{
	assert(m_winNumber >= 3 && "Too small win number");
	assert(m_width >= m_winNumber && "Too small board width");
	assert(m_height >= m_winNumber && "Too small board height");
};

// Helper function for print board
static void addPadding(const int number)
{
	for (int i{ 1 }; i <= number; ++i)
	{
		std::cout << ' ';
	}
}

// Converts a value to an std::size_t
std::size_t toUType(auto value)
{
	return static_cast<std::size_t>(value);
}

// Prints the board
void Connect4Board::print(const int padding) const
{
	// Prints the rows and collumns
	for (std::vector<char> row : m_board)
	{
		addPadding(padding);
		for (char symbol : row)
		{
			std::cout << "|" << symbol;
		}
		std::cout << "|\n";
	}

	// Adds the bottom of the board
	addPadding(padding);
	for (int i{ 1 }; i <= m_width; ++i)
	{
		std::cout << "^^";
	}
	std::cout << "^\n";

	// Prints a number below each row (does not support multi digit numbers)
	if (m_width <= 9)
	{
		addPadding(padding);
		for (int i{ 1 }; i <= m_width; ++i)
		{
			std::cout << ' ' << i;
		}
		std::cout << '\n';
	}
}

// Places a disk into the connect 4 board (returns false if failed)
bool Connect4Board::placeDisk(const int column, const char symbol)
{
	assert(column > 0 && column <= m_width && "placeDisk called with invalid column");
	
	// Checks if a space is empty, starting at the bottom
	for (std::size_t i{ toUType(m_height) }; i > 0; --i)
	{
		// Places a symbol and stops the function if a space is empty
		if (m_board[i - 1][toUType(column) - 1] == ' ')
		{
			m_board[i - 1][toUType(column) - 1] = symbol;
			return true;
		}
	}
	// Indicates that all spaces in a column were full
	return false;
}

// Checks to see if the most recently placed disk has caused a win
char Connect4Board::checkForWinner(const int mostRecentColumn) const
{
	// Get most recently placed disk
	std::size_t diskColumn{ toUType(mostRecentColumn - 1) };
	std::size_t diskRow{};
	char winSymbol{};

	for (std::size_t i{ 0 }; i < toUType(m_height); ++i)
	{
		if (m_board[i][diskColumn] != ' ')
		{
			diskRow = i;
			winSymbol = m_board[diskRow][diskColumn];
			break;
		}

		assert(i != toUType(m_height - 1) && "Check for winner called on an empty column");
	}

	// Checks for vertical wins
	{
		// Determines what column should be started on when calculating if a placed disk will resault in a win
		std::size_t startingColumn{ 0 };
		if (diskColumn > toUType(m_winNumber - 1))
			startingColumn = diskColumn - toUType(m_winNumber - 1);

		// Determines what column should be ended on when calculating if a placed disk will resault in a win
		std::size_t endingColumn{ std::min(diskColumn + toUType(m_winNumber - 1), toUType(m_width - 1)) };

		// Checks if their is 4 in a row
		int adjacentWinSymbols{ 0 };
		for (std::size_t i{ startingColumn }; i <= endingColumn; ++i)
		{
			if (m_board[diskRow][i] == winSymbol)
				++adjacentWinSymbols;
			else
				adjacentWinSymbols = 0;

			// Returns early if someone wins
			if (adjacentWinSymbols == m_winNumber)
				return winSymbol;
		}
	}

	// Check for left right diagonal wins
	{
		// Determines what row and column the start space should be
		std::size_t startingRow{ 0 };
		std::size_t startingColumn{ 0 };

		if (diskRow <= diskColumn)
		{
			if (diskRow > toUType(m_winNumber - 1))
				startingRow = diskRow - toUType(m_winNumber - 1);

			startingColumn = diskColumn - (diskRow - startingRow);
		}

		else
		{
			if (diskColumn > toUType(m_winNumber - 1))
				startingColumn = diskColumn - toUType(m_winNumber - 1);

			startingRow = diskRow - (diskColumn - startingColumn);
		}

		// Determines what row or column should be ended on
		std::size_t endingRow{ std::min(diskRow + toUType(m_winNumber - 1), toUType(m_height - 1)) };
		std::size_t endingColumn{ std::min(diskColumn + toUType(m_winNumber - 1), toUType(m_width - 1)) };

		// Checks if their is 4 in a row
		int adjacentWinSymbols{ 0 };

		for (std::size_t i{ startingRow }, j{ startingColumn }; i <= endingRow && j <= endingColumn; ++i, ++j)
		{
			if (m_board[i][j] == winSymbol)
				++adjacentWinSymbols;
			else
				adjacentWinSymbols = 0;

			// Returns early if someone wins
			if (adjacentWinSymbols == m_winNumber)
				return winSymbol;
		}
	}

	// Check for right left diagonal wins
	{
		// Determines what row and column the start space should be
		std::size_t startingRow{ 0 };
		std::size_t startingColumn{ 0 };

		if (diskRow <= toUType(m_width - 1) - diskColumn)
		{
			if (diskRow > toUType(m_winNumber - 1))
				startingRow = diskRow - (toUType(m_winNumber - 1));

			startingColumn = diskColumn + (diskRow - startingRow);
		}
		else
		{
			startingColumn = std::min(diskColumn + toUType(m_winNumber - 1), toUType(m_width - 1));

			startingRow = diskRow - (startingColumn - diskColumn);
		}

		// Determines what row or column should be ended on
		std::size_t endingRow{ std::min(diskRow + toUType(m_winNumber - 1), toUType(m_height - 1)) };
		std::size_t endingColumn{ 0 };

		if (diskColumn > toUType(m_winNumber - 1))
			endingColumn = diskColumn - toUType(m_winNumber - 1);

		// Checks if their is 4 in a row
		int adjacentWinSymbols{ 0 };

		// i and j are signed to prevent unsigned wrap around behavior
		for (int i{ static_cast<int>(startingRow) }, j{ static_cast<int>(startingColumn) };
			i <= static_cast<int>(endingRow) && j >= static_cast<int>(endingColumn); ++i, --j)
		{
			if (m_board[toUType(i)][toUType(j)] == winSymbol)
				++adjacentWinSymbols;
			else
				adjacentWinSymbols = 0;

			// Returns early if someone wins
			if (adjacentWinSymbols == m_winNumber)
				return winSymbol;
		}
	}

	// Check if there is a horizontal win
	if (toUType((m_height - 1) - (m_winNumber - 1)) >= diskRow)
	{
		int adjacentWinSymbols{ 0 };

		for (std::size_t i{ diskRow }; i <= diskRow + toUType(m_winNumber - 1); ++i)
		{
			if (m_board[i][diskColumn] == winSymbol)
				++adjacentWinSymbols;
			else
				adjacentWinSymbols = 0;

			// Returns early if someone wins
			if (adjacentWinSymbols == m_winNumber)
				return winSymbol;
		}
	}
	return ' ';
}
