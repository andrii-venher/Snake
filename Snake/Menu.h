#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>

#include "MouseTracker.h"

using namespace std;

struct MenuElement
{
	string title;
	COORD c;
	bool isPressed;
};

class Menu
{
protected:
	vector<MenuElement> elements;
	
	void Add(const MenuElement& el);
	int ClickedElement();
public:
	void Show() const;
};

