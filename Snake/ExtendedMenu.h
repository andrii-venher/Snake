#pragma once
#include <vector>
#include <iostream>
#include <Windows.h>

#include "Constants.h"
#include "MouseTracker.h"

using namespace std;

struct MenuElement
{
	string title;
	COORD c;
	MENU_ELEMENT_TYPE type;
	bool isPressed;

	friend ostream& operator<<(ostream& cout, MenuElement el);
	bool operator==(MenuElement el);
};

struct MenuRow
{
	MenuElement name;
	vector<MenuElement> values;

	void Clear();
};

struct MatrixIndex
{
	int row;
	int col;
};

class ExtendedMenu
{
	MenuElement header;
	vector<MenuRow> table;
	MenuElement ending;
protected:
	void TossPressedElement(MatrixIndex index);
	MatrixIndex GetElementIndex(MenuElement el);
	void SetHeader(const MenuElement& el);
	void SetEnding(const MenuElement& el);
	void AddRow(const MenuRow& row);
	MenuElement ClickedElement();
public:	
	void Show();
};

