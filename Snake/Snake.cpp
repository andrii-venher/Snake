#include "Snake.h"

Snake::Snake(COORD head, SnakeChars snakeChar)
{
	body.push_back(head);
	body.push_back({ head.X - 1, head.Y });
	dir = NONE;
	this->snakeChar = snakeChar;
}

void Snake::Paint()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < body.size(); i++)
	{
		if (body[i].X == Head().X && body[i].Y == Head().Y)
			SetConsoleTextAttribute(h, (int)Colors::RED);
		else
			SetConsoleTextAttribute(h, (int)Colors::WHITE);
		SetConsoleCursorPosition(h, body[i]);
		cout << (char)snakeChar;
	}
	SetConsoleTextAttribute(h, 7);
}

void Snake::Move()
{
	if (dir == NONE)
		return;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(h, Tail());
	SetConsoleTextAttribute(h, (int)Colors::WHITE);
	cout << " ";

	for (int i = body.size() - 1; i > 0; i--)
	{
		body[i] = body[i - 1];
	}

	switch (dir)
	{
	case UP:
		Head().Y--;
		break;
	case RIGHT:
		Head().X++;
		break;
	case DOWN:
		Head().Y++;
		break;
	case LEFT:
		Head().X--;
		break;
	default:
		break;
	}

	SetConsoleCursorPosition(h, Head());
	SetConsoleTextAttribute(h, (int)Colors::RED);
	cout << (char)snakeChar;
	SetConsoleCursorPosition(h, body[1]);
	SetConsoleTextAttribute(h, (int)Colors::WHITE);
	cout << (char)snakeChar;
}

bool Snake::CheckCrash()
{
	for (int i = 1; i < body.size(); i++)
	{
		if (Head().X == body[i].X && Head().Y == body[i].Y)
		{
			return true;
		}
	}
	return false;
}

COORD& Snake::Head()
{
	return body.front();
}

COORD& Snake::Tail()
{
	return body.back();
}

void Snake::SetDir(DIRECTIONS d)
{
	dir = d;
}

DIRECTIONS Snake::GetDir() const
{
	return dir;
}

void Snake::Grow()
{
	body.push_back(Tail());
}
