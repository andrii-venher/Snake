#pragma once
#include <Windows.h>
#include <vector>
#include <iostream>

#include "Constants.h"

using namespace std;

enum DIRECTIONS {UP, RIGHT, DOWN, LEFT, NONE};

class Snake
{
	vector<COORD> body;
	DIRECTIONS dir;
	SnakeChars snakeChar;
public:
	Snake(COORD head, SnakeChars snakeChar);
	void Paint();
	void Move();
	bool CheckCrash();
	COORD& Head();
	COORD& Tail();
	void SetDir(DIRECTIONS d);
	DIRECTIONS GetDir() const;
	void Grow();
};

