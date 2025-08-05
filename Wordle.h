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

extern int currentAttempt;

extern string roundRecord;
extern string gameRecord[5];

extern string defaultTextColorCode;
extern string textColorCode;
extern string errorColorCode;

extern string redColorCode;
extern string purpleColorCode;
extern string grayColorCode;
extern string yellowColorCode;
extern string greenColorCode;

void centreOutput();
void lineSeparator();
void displayTitle();
void displayInstructions();

void setWordFile(int);
void setRandomWordFromFile();

void gameStart();

void setWordToUpperCase(string&);
bool isLetterInWord(char);
bool isEnglishWord(string);

void takeInput(string&, int);
bool isMatch(string);
void displayWord(string, int);


void displayThanks();
void showRecord();
void GameWin();
void GameLost();
