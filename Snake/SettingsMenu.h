#pragma once

#include "ExtendedMenu.h"
#include "GameSettings.h"

using namespace std;

class SettingsMenu : public ExtendedMenu
{
	GameSettings* settings;
	
	SnakeChars CharToSnakeChar(char ch);
	SleepTime IntToSleepTime(int sleepTime);
public:
	SettingsMenu(GameSettings* settings);
	void Interact();
};

