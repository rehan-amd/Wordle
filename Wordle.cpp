#include "wordle.h"

string FILE_NAME = "Words.txt";
int WORD_SIZE = 5;
int FILE_SIZE = 16152;
string WORD = "RHN AMD";

int currentAttempt;

string roundRecord;
string gameRecord[5];

string defaultColorCode = "\033[0m";
string textColorCode = "\033[93m"; //Bright Yellow
string errorColorCode = "\033[91m"; //Light Red

string redColorCode = "\033[38;5;1m";
string purpleColorCode = "\033[38;5;89m";
string grayColorCode = "\033[38;5;59m";
string yellowColorCode = "\033[33m";
string greenColorCode = "\033[38;5;46m";


void centreOutput()
{
	cout << "\t\t\t";
}

void lineSeparator()
{
	centreOutput();

	for (int i = 0; i < WORD_SIZE * 2; i++)
		cout << "--";
		
	cout << "-" << endl;
}

void displayTitle()
{
	centreOutput();
	cout << textColorCode << "   Wordle Knock-Off" << defaultColorCode;

	cout << "\n\n\n\n\n";
}

void displayInstructions()
{
	cout << textColorCode << "-You have to guess a Random Word." << endl;
	cout << "-You have 5 attempts." << endl;
	cout << "-There's a color-code to help you with your guess:" << endl
		<< "\t" << grayColorCode << "GRAY <> Incorrect letter" << endl
		<< "\t" << yellowColorCode << "YELLOW <> Correct letter, but Incorrect Position" << endl
		<< "\t" << greenColorCode << "GREEN <> Correct letter and Position" << endl;

	cout << textColorCode << "-Let the Games Begin!!!" << defaultColorCode << endl << endl << endl;
}

void setWordFile(int difficulty)
{
	if (difficulty == 1)
	{
		FILE_NAME = "SIX_LETTERED_WORDS.txt";
		WORD_SIZE = 6;
	}
	else if (difficulty == 2)
	{
		FILE_NAME = "FIVE_LETTERED_WORDS.txt";
		WORD_SIZE = 5;
	}
	else if (difficulty == 3)
	{
		FILE_NAME = "FOUR_LETTERED_WORDS.txt";
		WORD_SIZE = 4;
	}
	else if (difficulty == 4)
	{
		FILE_NAME = "THREE_LETTERED_WORDS.txt";
		WORD_SIZE = 3;
	}

	ifstream myFile(FILE_NAME);
	
	if (!myFile.is_open())
	{
		throw "Error";
		return;
	}

	string size;
	getline(myFile, size);
	
	FILE_SIZE = stoi(size);
}

void setRandomWordFromFile()
{
	ifstream myFile(FILE_NAME);

	if (!myFile.is_open())
	{
		throw "Error";
		return;
	}

	random_device rd;
	mt19937 gen(rd());

	uniform_int_distribution<> dist(2, FILE_SIZE);

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

	setWordToUpperCase(WORD);

	myFile.close();
}

void gameStart()
{
	displayTitle();
	displayInstructions();

	Input:
	string input;
	int difficulty;
	cout << textColorCode << "Enter Difficulty:-" << endl
		<< "\t" << greenColorCode << "1 - Easy( 6 Letter Words )" << endl
		<< "\t" << yellowColorCode << "2 - Medium( 5 Letter Words )" << endl
		<< "\t" << redColorCode << "3 - Hard( 4 Letter Words )" << endl
		<< "\t" << purpleColorCode << "4 - Extra Hard( 3 Letter Words )" << endl
		<< textColorCode << ">>> " << defaultColorCode;
	cin >> input;
	
	try
	{
		difficulty = stoi(input);
	}
	catch (...)
	{
		cout << errorColorCode << "Error!Input is not a Number - Try Again" << defaultColorCode << endl << endl;
		goto Input;
	}

	if (difficulty < 1 || difficulty > 4)
	{
		cout << errorColorCode << "Error! Your Input is Outside the Range - Try Again" << defaultColorCode << endl << endl;

		goto Input;
	}


	try
	{
		setWordFile(difficulty);
		setRandomWordFromFile();
	}
	catch (...)
	{
		throw errorColorCode + "Error! Can't Access Word File - Try Again Later.\n\n" + defaultColorCode;
		return;
	}

	cout << textColorCode << "" << endl << endl;
	system("pause");
	system("cls");
}

void setWordToUpperCase(string& word)
{
	for (int i = 0; i < WORD_SIZE; i++)
		word[i] = toupper(word[i]);
}

bool isLetterInWord(char letter)
{
	for (int i = 0; i < WORD_SIZE; i++)
	{
		if (letter == WORD[i])
			return true;
	}

	return false;
}

bool isEnglishWord(string input)
{
	ifstream myFile(FILE_NAME);
	string line, word;
	int currentLine = 1;

	while (getline(myFile, line))
	{
		word = line;

		while (!word.empty() && isspace(word.front()))
			word.erase(word.begin());

		while (!word.empty() && isspace(word.back()))
			word.pop_back();

		setWordToUpperCase(word);

		if (input == word)
			return true;

		if (currentLine++ == FILE_SIZE)
			break;
	}

	myFile.close();

	return false;
}


void takeInput(string& variable, int attempt)
{
	currentAttempt = 6 - attempt;

	displayTitle();
	if (currentAttempt != 1)	lineSeparator();

	int i;
	for (i = 0; i < currentAttempt - 1; i++)
	{
		centreOutput();
		cout << gameRecord[i] << endl;
		lineSeparator();
	}

	for (; i < 2; i++)
		cout << endl;

	cout << "\n" << "\t\t\t\t\t\t\t" << textColorCode << "Attempt No. " << currentAttempt << endl;

Input:
	string input;
	cout << textColorCode << "Enter a Word:\t" << defaultColorCode;
	cin >> input;

	if (input.size() != WORD_SIZE)
	{
		cout << errorColorCode << "Error! Input isn't " << WORD_SIZE << " letters - Try Again" << defaultColorCode << endl << endl;
		goto Input;
	}

	for (int i = 0; i < WORD_SIZE; i++)
	{
		if (!isalpha(input[i]))
		{
			cout << errorColorCode << "Error! Your Word contains a Non-Alphabet Character - Try Again" << defaultColorCode << endl << endl;
			goto Input;
		}
	}

	setWordToUpperCase(input);
	
	if (!isEnglishWord(input))
	{
		cout << errorColorCode << "Error! \"" << input << "\" isn't an English Word - Try Again" << defaultColorCode << endl << endl;
		goto Input;
	}

	variable = input;
}

bool isMatch(string guess)
{
	for (int i = 0; i < WORD_SIZE; i++)
		if (guess[i] != WORD[i])
			return false;

	return true;
}

void displayLetter(char letter, int color)
{
	string code;

	if (color == 0)	//Gray
	{
		code = "| " + grayColorCode + string(1, letter) + " " + defaultColorCode;
	}
	else if (color == 1)	//Yellow
	{
		code = "| " + yellowColorCode + string(1, letter) + " " + defaultColorCode;
	}
	else if (color == 2)	//Green
	{
		code = "| " + greenColorCode + string(1, letter) + " " + defaultColorCode;
	}

	cout << code;
	roundRecord.append(code);
}

void displayWord(string input, int attempt)
{
	currentAttempt = 6 - attempt;

	roundRecord.clear();

	int* colorCode = new int[WORD_SIZE] {0};
	bool* usedInWord = new bool[WORD_SIZE] {0};
	bool* usedInInput = new bool[WORD_SIZE] {0};

	// Step 1: Mark GREEN
	for (int i = 0; i < WORD_SIZE; i++)
	{
		if (input[i] == WORD[i])
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
			if (!usedInWord[j] && input[i] == WORD[j])
			{
				colorCode[i] = 1; // Yellow
				usedInWord[j] = true;
				break;
			}
		}
	}

	// Display the word with correct colors
	cout << endl;
	lineSeparator();
	centreOutput();
	for (int i = 0; i < WORD_SIZE; i++)
	{
		displayLetter(input[i], colorCode[i]);
	}

	cout << "|" << endl;
	roundRecord.append("|");

	lineSeparator();

	cout << textColorCode << "" << endl << endl << endl << endl;
	gameRecord[currentAttempt - 1] = roundRecord;

	delete[] colorCode;
	delete[] usedInWord;
	delete[] usedInInput;
}


void showRecord()
{
	displayTitle();

	cout << textColorCode << "Game Score:-" << defaultColorCode << endl << endl;
	lineSeparator();
	for (int i = 0; i < currentAttempt; i++)
	{
		centreOutput();
		cout << gameRecord[i] << endl;
		lineSeparator();
	}

	cout << textColorCode << "" << endl << endl;
}

void displayThanks()
{
	cout << "Thank You For Playing. Hope You Had Fun." << defaultColorCode << endl << endl;
	cout << "------------------------------------------------------------------------------------";
}

void GameWin()
{
	showRecord();

	cout << endl << endl;
	cout << "You Won! You guessed the Word( " << greenColorCode << WORD << textColorCode << " ) in " << currentAttempt << " attempt(s)." << endl;
	displayThanks();
}

void GameLost()
{
	showRecord();

	cout << endl << endl;
	cout << "You Lost! You couldn't guess the Word( " << greenColorCode << WORD << textColorCode << " ) in 5 attempts." << endl;
	displayThanks();
}
