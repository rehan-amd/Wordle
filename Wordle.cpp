#include "wordle.h"

const int WORD_SIZE = 5;
string WORD;

string roundRecord;
string gameRecord[5];

void gameStart()
{
	setRandomWordFromFile();

	displayTitle();

	displayInstructions();
	system("cls");
}

void setRandomWordFromFile()
{
	ifstream myFile("Words.txt");

	if (!myFile.is_open())
	{
		cerr << "Error opening file.\n";
		return;
	}

	random_device rd;
	mt19937 gen(rd());

	uniform_int_distribution<> dist(1, 16152);

	int choosenLine = dist(gen);

	string line;
	int currentLine = 1;

	while (getline(myFile, line))
	{
		if (currentLine == choosenLine)
		{
			WORD = line;
			break;
		}

		currentLine++;
	}

	while (!WORD.empty() && isspace(WORD.front()))
		WORD.erase(WORD.begin());

	while (!WORD.empty() && isspace(WORD.back()))
		WORD.pop_back();

	myFile.close();
}

void centreOutput()
{
	cout << "\t\t\t";
}

void displayTitle()
{
	centreOutput();
	cout << "Wordle Knock-Off";

	cout << "\n\n\n\n\n";
}

void displayInstructions()
{
	cout << "-You have to guess a " << WORD_SIZE << " lettered Word." << endl;
	cout << "-You have 5 attempts." << endl;
	cout << "-There's a color-code to help you with your guess:" << endl
		<< "\t" << "GRAY <> Incorrect letter" << endl
		<< "\t" << "YELLOW <> Correct letter, but Incorrect Position" << endl
		<< "\t" << "GREEN <> Correct letter and Position" << endl;

	cout << "-Let the Games Begin!!!" << endl << endl << endl;

	system("pause");
}

bool isLetterInWord(char letter)
{
	for (int i = 0; i < WORD_SIZE; i++)
	{
		if (toupper(letter) == toupper(WORD[i]))
			return true;
	}

	return false;
}

bool isEnglishWord(string input)
{
	ifstream myFile("Words.txt");
	string line, word;
	int currentLine = 1;

	while (getline(myFile, line))
	{
		word = line;

		while (!word.empty() && isspace(word.front()))
			word.erase(word.begin());

		while (!word.empty() && isspace(word.back()))
			word.pop_back();

		if (input == word)
			return true;

		if (currentLine++ == 16152)
			break;
	}

	myFile.close();

	return false;
}


void takeInput(string& variable, int attempt)
{
	displayTitle();

	int i;
	for (i = 0; i < 5 - attempt; i++)
	{
		centreOutput();
		cout << gameRecord[i] << endl;
	}

	for (; i < 2; i++)
		cout << endl;

	cout << "\n" << "\t\t\t\t\t\t\t" << "Attempt No. " << 6 - attempt << endl;

Input:
	string input;
	cout << "Enter a Word:\t";
	cin >> input;

	if (input.size() != 5)
	{
		cout << "Error! Enter a 5 letter Word - Try Again" << endl << endl;
		goto Input;
	}

	for (char character : input)
	{
		if (!isalpha(character))
		{
			cout << "Error! Your Word contains a Non-Alphabet Character - Try Again" << endl << endl;
			goto Input;
		}
	}


	if (!isEnglishWord(input))
	{
		cout << "Error! Your Word isn't an English Word - Try Again\n\n";
		goto Input;
	}

	variable = input;
}

bool isMatch(string guess)
{
	for (int i = 0; i < WORD_SIZE; i++)
	{
		if (toupper(guess[i]) != toupper(WORD[i]))
			return false;
	}

	return true;
}

void displayLetter(char letter, int color)
{
	letter = toupper(letter);

	string code;

	if (color == 0)
	{
		code = "\033[90m" + string(1, letter) + " \033[0m";
	}
	else if (color == 1)
	{
		code = "\033[33m" + string(1, letter) + " \033[0m";
	}
	else if (color == 2)
	{
		code = "\033[32m" + string(1, letter) + " \033[0m";
	}

	cout << code;
	roundRecord.append(code);
}

void displayWord(string input, int attempt)
{
	roundRecord.clear();

	int colorCode[WORD_SIZE] = { 0 }; // 0 - gray, 1 - yellow, 2 - green
	bool usedInWord[WORD_SIZE] = { false };
	bool usedInInput[WORD_SIZE] = { false };

	// Step 1: Mark GREEN
	for (int i = 0; i < WORD_SIZE; i++)
	{
		if (toupper(input[i]) == toupper(WORD[i]))
		{
			colorCode[i] = 2; // Green
			usedInWord[i] = true;
			usedInInput[i] = true;
		}
	}

	// Step 2: Mark YELLOW
	for (int i = 0; i < WORD_SIZE; i++)
	{
		if (usedInInput[i]) continue;

		for (int j = 0; j < WORD_SIZE; j++)
		{
			if (!usedInWord[j] && toupper(input[i]) == toupper(WORD[j]))
			{
				colorCode[i] = 1; // Yellow
				usedInWord[j] = true;
				break;
			}
		}
	}

	// Display the word with correct colors
	cout << endl;
	centreOutput();
	for (int i = 0; i < WORD_SIZE; i++)
	{
		displayLetter(input[i], colorCode[i]);
	}

	cout << endl << endl << endl << endl;
	gameRecord[5 - attempt] = roundRecord;

	//---------------
	/*
	roundRecord.clear();

	int colorCode = 0;
	//case 0 - Gray
	//case 1 - Yellow
	//case 2 - Green

	cout << endl; centreOutput();
	for (int i = 0; i < WORD_SIZE; i++)
	{
		if (toupper(input[i]) == toupper(WORD[i]))
			colorCode = 2;
		else if (isLetterInWord(input[i]))
			colorCode = 1;
		else
			colorCode = 0;

		displayLetter(input[i], colorCode);
	}

	cout << endl << endl << endl << endl;
	gameRecord[5 - attempt] = roundRecord;
	*/
}



void displayThanks()
{
	cout << "Thank You For Playing. Hope You Had Fun." << endl;
}

void showRecord()
{
	displayTitle();

	cout << "Game Score:-" << endl << endl;
	for (int i = 0; i < 5; i++)
	{
		centreOutput();
		cout << gameRecord[i] << endl;
	}

	cout << endl << endl;
}

void GameWin()
{
	showRecord();

	cout << endl << endl;
	cout << "You Won!" << endl;
	displayThanks();
}

void GameLost()
{
	showRecord();

	cout << endl << endl;
	cout << "You Lost! You couldn't guesss the Word(\033[32m " << WORD << "\033[0m ) in 5 attempts." << endl;
	displayThanks();
}
