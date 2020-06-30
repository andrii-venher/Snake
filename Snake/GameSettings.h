#pragma once
#include "Field.h"
#include "Constants.h"

struct GameSettings
{
	Field* field;
	unsigned int sleepTime;
	SnakeChars snakeChar;
};
