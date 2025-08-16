#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <random>
using namespace std;

extern string FILE_NAME;
extern int WORD_SIZE;
extern int FILE_SIZE;
extern string WORD;

extern const int TOTAL_ATTEMPTS;
extern int currentAttempt;

extern string roundRecord;
extern string gameRecord[5];

extern string defaultTextColorCode;
extern string textColorCode;
extern string errorColorCode;

extern string redColorCode;
extern string yellowColorCode;
extern string greenColorCode;
extern string purpleColorCode;
extern string grayColorCode;
extern string blackColorCode;

void GAME();

void centreOutput();
void lineSeparator();
void displayTitle();
void displayInstructions();

void setWordFile(int);
void setRandomWordFromFile();

void gameStart();
void gameRun();

void setWordToUpperCase(string&);
bool isLetterInWord(char);
bool isEnglishWord(string);

void takeInput(string&, int);
bool isMatch(string);
void displayWord(string, int);


void showRecord();
void playAgain(string&);
void gameWin();
void gameLost();
void displayThanks();
