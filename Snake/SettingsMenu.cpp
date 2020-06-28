#include "SettingsMenu.h"

void SettingsMenu::Show()
{
	system("cls");
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < table.size(); i++)
	{
		for (int j = 0; j < table[i].size(); j++)
		{
			SetConsoleCursorPosition(h, table[i][j].c);
			if (table[i][j].isPressed)
			{
				SetConsoleTextAttribute(h, 10);
			}
			else
			{
				SetConsoleTextAttribute(h, 7);
			}
			cout << table[i][j].title;
		}
	}
	SetConsoleTextAttribute(h, 7);
}

void SettingsMenu::Add(const vector<MenuElement> row)
{
	table.push_back(row);
}

MatrixIndex SettingsMenu::ClickedElement()
{
	COORD click = click_coordinate();
	MatrixIndex index = { -1, -1 };
	for (int i = 0; i < table.size(); i++)
	{
		for (int j = 0; j < table[i].size(); j++)
		{
			if (click.Y == table[i][j].c.Y && click.X >= table[i][j].c.X && click.X <= table[i][j].c.X + table[i][j].title.length())
			{
				index = { i, j };
				return index;
			}
		}
	}
	return index;
}

void SettingsMenu::TossPressedElement(MatrixIndex index)
{
	for (int k = 0; k < table[index.i].size(); k++)
	{
		if (table[index.i][k].isPressed)
			table[index.i][k].isPressed = false;
	}
	table[index.i][index.j].isPressed = true;
}

SnakeChar SettingsMenu::CharToSnakeChar(char ch)
{
	switch (ch)
	{
	case '*':
		return SnakeChar::STAR;
	case '&':
		return SnakeChar::AMPERSANT;
	case '#':
		return SnakeChar::HASHTAG;
	default:
		return SnakeChar::STAR;
	}
}

SleepTime SettingsMenu::IntToSleepTime(int sleepTime)
{
	switch (sleepTime)
	{
	case 100:
		return SleepTime::FAST;
	case 150:
		return SleepTime::MEDIUM;
	case 200:
		return SleepTime::SLOW;
	default:
		return SleepTime::SLOW;
	}
}

SettingsMenu::SettingsMenu(GameSettings* settings)
{
	this->settings = settings;
	vector<MenuElement> temp;

	temp.push_back({ "field: ", {0,0}, false });
	temp.push_back({ "first", {0,0}, false });
	temp.push_back({ "second", {0,0}, false });
	for (int i = 1; i < 3; i++)
	{
		temp[i].c.Y = temp[i - 1].c.Y;
		temp[i].c.X = temp[i - 1].c.X + temp[i - 1].title.length() + 2;
		temp[i].isPressed = settings->field->GetFieldNumber() == i - 1;
	}
	Add(temp);
	temp.erase(temp.begin(), temp.end());

	temp.push_back({ "speed: ", {0,1}, false });
	temp.push_back({ "slow", {0,0}, false });
	temp.push_back({ "medium", {0,0}, false });
	temp.push_back({ "fast", {0,0}, false });
	for (int i = 1; i < 4; i++)
	{
		temp[i].c.Y = temp[i - 1].c.Y;
		temp[i].c.X = temp[i - 1].c.X + temp[i - 1].title.length() + 2;
	}
	switch (IntToSleepTime(settings->sleepTime))
	{
	case SleepTime::SLOW:
		temp[1].isPressed = true;
		break;
	case SleepTime::MEDIUM:
		temp[2].isPressed = true;
		break;
	case SleepTime::FAST:
		temp[3].isPressed = true;
		break;
	default:
		temp[0].isPressed = true;
		break;
	}
	Add(temp);
	temp.erase(temp.begin(), temp.end());

	temp.push_back({ "snake char: ", {0,2}, false });
	temp.push_back({ "*", {0,0}, false });
	temp.push_back({ "&", {0,0}, false });
	temp.push_back({ "#", {0,0}, false });
	for (int i = 1; i < 4; i++)
	{
		temp[i].c.Y = temp[i - 1].c.Y;
		temp[i].c.X = temp[i - 1].c.X + temp[i - 1].title.length() + 2;
	}
	switch (CharToSnakeChar(settings->snakeChar))
	{
	case SnakeChar::STAR:
		temp[1].isPressed = true;
		break;
	case SnakeChar::AMPERSANT:
		temp[2].isPressed = true;
		break;
	case SnakeChar::HASHTAG:
		temp[3].isPressed = true;
		break;
	default:
		temp[0].isPressed = true;
		break;
	}
	Add(temp);
	temp.erase(temp.begin(), temp.end());

	temp.push_back({ "back", {0, 3}, false });
	Add(temp);
}

void SettingsMenu::Interact()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	while (true)
	{
		MatrixIndex index = ClickedElement();
		switch (index.i)
		{
		case 0:
		{
			switch (index.j)
			{
			case 1:
			case 2:
				delete settings->field;
				settings->field = new Field(index.j - 1);
				break;
			default:
				break;
			}
			break;
		}
		case 1:
		{
			switch (index.j)
			{
			case 1:
				settings->sleepTime = SleepTime::SLOW;
				break;
			case 2:
				settings->sleepTime = SleepTime::MEDIUM;
				break;
			case 3:
				settings->sleepTime = SleepTime::FAST;
				break;
			default:
				break;
			}
			break;
		}
		case 2:
		{
			switch (index.j)
			{
			case 1:
				settings->snakeChar = SnakeChar::STAR;
				break;
			case 2:
				settings->snakeChar = SnakeChar::AMPERSANT;
				break;
			case 3:
				settings->snakeChar = SnakeChar::HASHTAG;
				break;
			default:
				break;
			}
			break;
		}	
		case 3:
			return;
		default:
			break;
		}
		if (index.i != -1)
		{
			TossPressedElement(index);
			Show();
		}
	}
}
