#include "wordle.h"

using namespace std;

int main()
{
	gameStart();

	string guess = "\0";
	int attempts = 5;
	while (attempts != 0)
	{
		takeInput(guess, attempts);

		displayWord(guess, attempts);

		system("pause");
		system("cls");

		if (isMatch(guess))
		{
			GameWin();
			return 0;
		}

		attempts--;
	}

	GameLost();

	return 0;
}
