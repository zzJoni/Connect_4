#include "Connect4Board.h"
#include "Player.h"
#include "getInput.h"
#include "Random.h"
#include "playConnect4.h"
#include "printDivider.h"
#include <iostream>
#include <string>
#include <utility>
#include <optional>

// Gets a player's name
static std::string getName(int playerNumber)
{
	std::string name{};
	
	while (name == "")
	{
		std::cout << "Enter the name of player " << playerNumber << ": ";
		name = getInput<std::string>().value_or("");
	}

	return name;
}

// Runs the turn taking process and returns the winner
static const Player* runTurnTaking(Connect4Board& board, const Player& player1, const Player& player2)
{
	for (int i{ 1 }; i <= board.maxTurns(); ++i)
	{
		// Determines who's turn it is
		const Player& currentPlayer{ ((i % 2 == 0)? player2 : player1) };

		if (i == 1)
			std::cout << currentPlayer.getName() << " goes first!\n";
		else
			std::cout << currentPlayer.getName() << "'s turn\n";
		
		std::cout << "Symbol: " << currentPlayer.getSymbol() << '\n';

		std::cout << '\n';
		board.print();
		std::cout << '\n';

		// Tracks which column the player placed a disk in
		int mostRecentColumn{};

		// Lets the player place a disk
		{
			bool diskPlaced{ false };

			while (!diskPlaced)
			{
				int columnNumber{};
				while (columnNumber < 1 || columnNumber > board.getWidth())
				{
					std::cout << "Enter the column that you want to place a disk in: ";
					columnNumber = getInput<int>().value_or(0);
				}

				diskPlaced = board.placeDisk(columnNumber, currentPlayer.getSymbol());

				if (diskPlaced)
					mostRecentColumn = columnNumber;
				else
					std::cout << "That column is full\n";
			}
		}

		std::cout << '\n';
		printDivider();

		// Starts checking for winners once enough disks are placed for someone to win
		char winningSymbol{};
		
		if (i >= (board.getWinNumber() * 2) - 1)
			winningSymbol = board.checkForWinner(mostRecentColumn);

		if (winningSymbol == player1.getSymbol())
			return &player1;
		
		if (winningSymbol == player2.getSymbol())
			return &player2;
	}

	return nullptr;
}

// Runs a game of Connect4
void playConnect4(int width, int height, int winNumber)
{
	std::cout << "\nWelcome to Connect 4 Online! In order to play, you will need 2 people!\n\n";
	
	// Creates the board
	Connect4Board board{ width, height, winNumber };
	
	// Creates players and randomizes who goes first
	std::string name1{ getName(1) };
	std::string name2{ getName(2) };

	if (Random::generate(0, 1))
	{
		std::swap(name1, name2);
	}

	const Player player1{ name1, 'X' };
	const Player player2{ name2, 'O' };

	std::cout << '\n';
	printDivider();

	// Runs the turns of the game and records who won
	const Player* winner{ runTurnTaking(board, player1, player2) };

	if (winner == nullptr)
	{
		std::cout << "\nDraw!!!\n\n";
		board.print();
	}
	else
	{
		std::cout << '\n' << winner->getName() << " wins!!!\n\n";
		board.print();
	}

	
	std::cout << '\n';
	printDivider();
}
