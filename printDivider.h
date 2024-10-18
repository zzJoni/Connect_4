#pragma once
#include <iostream>

// Prints x lines to use as a divider
inline void printDivider(const int x = 1)
{
	for (int i{ 1 }; i <= x; ++i)
	{
		std::cout << "_______________________________________________________________________________________\n";
	}
	std::cout << '\n';
}