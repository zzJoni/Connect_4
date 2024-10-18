#include <iostream>
#include <optional>
#include <string>

// Skips over any input left in the input buffer
inline void ignoreLine()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Gets a value from the user and handles bad inputs (returns nullopt if failed)
template <typename T>
inline std::optional<T> getInput()
{
	T input{};
	std::cin >> input;

	// Ends program if end of file character is entered or the input stream irrevocably fails 
	if (std::cin.eof() || std::cin.bad())
	{
		exit(0);
	}

	// Handles failed input stream
	if (!std::cin)
	{
		std::cin.clear();
		ignoreLine();
		return std::nullopt;
	}

	ignoreLine();
	return input;
}

// Gets a string value from the user (returns nullopt if failed)
template <>
inline std::optional<std::string> getInput()
{
	std::string input{};
	std::getline(std::cin, input);

	// Ends program if end of file character is entered or the input stream irrevocably fails 
	if (std::cin.eof() || std::cin.bad())
	{
		exit(0);
	}

	// Handles bad input
	if (!std::cin)
	{
		std::cin.clear();
		return std::nullopt;
	}

	return input;
}
