#include "Field.h"

Field::Field() : Field(0) { }

Field::Field(int number)
{
	height = 30;
	width = 70;
	start = { 1, 1 };

	fieldNumber = number;

	field = new FieldObjects * [height];

	for (int i = 0; i < height; i++)
	{
		field[i] = new FieldObjects[width];
	}

	switch (number)
	{
	case 0:
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
					field[i][j] = WALL;
				else
					field[i][j] = EMPTY;
			}
		}
		break;
	case 1:
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (i == 0 || i == height - 1 || j == 0 || j == width - 1 ||
					(i == height / 4 && j > width / 4 && j < width * 3 / 4) ||
					(i == height * 3 / 4 && j > width / 4 && j < width * 3 / 4) ||
					(j == width / 6 && i > height / 4 && i < height * 3 / 4) ||
					(j == width * 5 / 6 && i > height / 4 && i < height * 3 / 4))
					field[i][j] = WALL;
				else
					field[i][j] = EMPTY;
			}
		}
		break;
	default:
		break;
	}
}

int Field::GetHeight() const
{
	return height;
}

int Field::GetWidth() const
{
	return width;
}

void Field::Print() const
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = start;
	
	for (int i = 0; i < height; i++)
	{
		
		for (int j = 0; j < width; j++)
		{
			
			SetConsoleCursorPosition(h, c);
			if (field[i][j] == WALL)
			{

				SetConsoleTextAttribute(h, 255);
				cout << "*";
			}
			else
			{
				SetConsoleTextAttribute(h, 7);
				cout << " ";
			}
			c.X++;
		}
		c.Y++;
		c.X = start.X;
	}
	SetConsoleTextAttribute(h, 7);
}

FieldObjects& Field::operator()(int i, int j)
{
	i -= start.Y;
	j -= start.X;
	if (i >= 0 && i < height && j >= 0 && j < width)
		return field[i][j];
}

unsigned int Field::GetFieldNumber()
{
	return fieldNumber;
}
