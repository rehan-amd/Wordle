#include "wordle.h"

using namespace std;

int main()
{
	try
	{
		gameStart();
	}
	catch (string e)
	{
		cout << e;
		return 0;
	}

	string guess;
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
