#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <random>
using namespace std;

extern const int WORD_SIZE;
extern const int FILE_SIZE;
extern string WORD;

extern string roundRecord;
extern string gameRecord[5];

void gameStart();

void setRandomWordFromFile();

void centreOutput();
void lineSeparator();
void displayTitle();
void displayInstructions();

bool isLetterInWord(char);
bool isEnglishWord(string);

void takeInput(string&, int);
bool isMatch(string);
void displayWord(string, int);


void displayThanks();
void showRecord();
void GameWin();
void GameLost();
