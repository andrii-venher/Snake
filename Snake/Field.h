#pragma once
#include <Windows.h>
#include <iostream>

#include "Constants.h"

using namespace std;

class Field
{
	FieldObjects** field;
	int height;
	int width;
	COORD start;
	unsigned int fieldNumber;
public:
	Field();
	Field(int number);
	int GetHeight() const;
	int GetWidth() const;
	void Print() const;
	FieldObjects& operator()(int i, int j);
	unsigned int GetFieldNumber();
};

