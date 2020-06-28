#pragma once
#include <Windows.h>
#include <string>
#include <vector>

#include "Menu.h"
#include "GameSettings.h"
#include "MouseTracker.h"
#include "Constants.h"

using namespace std;

struct MatrixIndex
{
	int i;
	int j;
};

class SettingsMenu
{
	GameSettings* settings;
	vector<vector<MenuElement> > table;
	
	void Add(const vector<MenuElement> row);
	MatrixIndex ClickedElement();
	void TossPressedElement(MatrixIndex index);
	SnakeChar CharToSnakeChar(char ch);
	SleepTime IntToSleepTime(int sleepTime);
public:
	SettingsMenu(GameSettings* settings);
	void Interact();
	void Show();
};

