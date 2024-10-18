#include "getInput.h"
#include "printDivider.h"
#include "isPlayingAgain.h"
#include <iostream>
#include <optional>

// Checks if the user wants to play again
bool isPlayingAgain()
{
	char userInput{};

	while (userInput != 'y' && userInput != 'n')
	{
		std::cout << "Do you want to play again? (enter y or n): ";
		userInput = getInput<char>().value_or(0);
	}
	printDivider();
	return (userInput == 'y') ? true : false;
}
