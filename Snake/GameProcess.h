#pragma once
#include <string>
#include <conio.h>

#include "Field.h"
#include "Snake.h"
#include "GameSettings.h"
#include "Constants.h"

using namespace std;

struct GameInfo
{
	COORD place;
	unsigned int score;
	unsigned int rawTime;
};

class GameProcess
{
	Snake* snake;
	GameInfo* info;
	GameSettings settings;
public:
	GameProcess(const GameSettings* settings);
	void Show();
	void CheckRotation();
	bool CheckLose();
	void CheckGrow();
	void UpdateInfo();
	void SpawnEgg();
	void Tick();
	void Wait(unsigned int milliseconds);
};

