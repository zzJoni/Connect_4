#include "playConnect4.h"
#include "isPlayingAgain.h"

int main()
{
	// Runs connect 4 games until the user specifies that they want to stop
	do
	{
		playConnect4();
	} while (isPlayingAgain());

	return(0);
}
