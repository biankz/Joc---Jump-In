#pragma once

#define LIB_H
#define GAME_H

#include <iostream>
using namespace std;

struct position {
	int row, column;
};
struct foxPosition {
	position start, end;
	char orientation;
};

extern foxPosition Fox[5];

extern char board[5][5];

bool moveRabbit(int L1, int C1, int L2, int C2);
bool moveFox(int index, char direction, int positions);

void randomBoard();
bool gameWon();
void playGame();

void loadLevel(const char* filename);
void fox_level4();
void fox_level5();
void fox_level6();
void fox_level7();
void fox_level8();