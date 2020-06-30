#include "SettingsMenu.h"

SnakeChars SettingsMenu::CharToSnakeChar(char ch)
{
	switch (ch)
	{
	case '*':
		return SnakeChars::STAR;
	case '&':
		return SnakeChars::AMPERSANT;
	case '#':
		return SnakeChars::HASHTAG;
	default:
		return SnakeChars::STAR;
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
	SetHeader({ "SETTINGS", {5, 0}, MENU_ELEMENT_TYPE::LABEL, false });
	SetEnding({ "BACK", {5, 5}, MENU_ELEMENT_TYPE::EXIT, false });

	MenuRow row;

	row.name = { "first", {0,1}, MENU_ELEMENT_TYPE::LABEL, false };
	row.values.push_back({ "first", {0,0}, MENU_ELEMENT_TYPE::BUTTON, false });
	row.values.push_back({ "second", {0,0}, MENU_ELEMENT_TYPE::BUTTON, false });
	for (int i = 0; i < row.values.size(); i++)
	{
		row.values[i].c.Y = row.name.c.Y;
		if (i == 0)
		{
			row.values[i].c.X = row.name.c.X + row.name.title.length() + 2;
		}
		else
		{
			row.values[i].c.X = row.values[i - 1].c.X + row.values[i - 1].title.length() + 2;
		}
		row.values[i].isPressed = settings->field->GetFieldNumber() == i;
	}
	AddRow(row);
	row.Clear();

	row.name = { "speed: ", {0,2}, MENU_ELEMENT_TYPE::LABEL, false };
	row.values.push_back({ "slow", {0,0}, MENU_ELEMENT_TYPE::BUTTON, false });
	row.values.push_back({ "medium", {0,0}, MENU_ELEMENT_TYPE::BUTTON, false });
	row.values.push_back({ "fast", {0,0}, MENU_ELEMENT_TYPE::BUTTON, false });
	for (int i = 0; i < row.values.size(); i++)
	{
		row.values[i].c.Y = row.name.c.Y;
		if (i == 0)
		{
			row.values[i].c.X = row.name.c.X + row.name.title.length() + 2;
		}
		else
		{
			row.values[i].c.X = row.values[i - 1].c.X + row.values[i - 1].title.length() + 2;
		}
	}
	switch (IntToSleepTime(settings->sleepTime))
	{
	case SleepTime::SLOW:
		row.values[0].isPressed = true;
		break;
	case SleepTime::MEDIUM:
		row.values[1].isPressed = true;
		break;
	case SleepTime::FAST:
		row.values[2].isPressed = true;
		break;
	default:
		row.values[0].isPressed = true;
		break;
	}
	AddRow(row);
	row.Clear();

	row.name = { "snake char: ", {0,3}, MENU_ELEMENT_TYPE::LABEL, false };
	row.values.push_back({ "*", {0,0}, MENU_ELEMENT_TYPE::BUTTON, false });
	row.values.push_back({ "&", {0,0}, MENU_ELEMENT_TYPE::BUTTON, false });
	row.values.push_back({ "#", {0,0}, MENU_ELEMENT_TYPE::BUTTON, false });
	for (int i = 0; i < row.values.size(); i++)
	{
		row.values[i].c.Y = row.name.c.Y;
		if (i == 0)
		{
			row.values[i].c.X = row.name.c.X + row.name.title.length() + 2;
		}
		else
		{
			row.values[i].c.X = row.values[i - 1].c.X + row.values[i - 1].title.length() + 2;
		}
	}
	switch (settings->snakeChar)
	{
	case SnakeChars::STAR:
		row.values[0].isPressed = true;
		break;
	case SnakeChars::AMPERSANT:
		row.values[1].isPressed = true;
		break;
	case SnakeChars::HASHTAG:
		row.values[2].isPressed = true;
		break;
	default:
		row.values[0].isPressed = true;
		break;
	}
	AddRow(row);
	row.Clear();
}

void SettingsMenu::Interact()
{
	while (true)
	{
		MenuElement clickedEl = ClickedElement();
		if (clickedEl.type == MENU_ELEMENT_TYPE::EXIT)
			return;
		MatrixIndex buttonIndex = GetElementIndex(clickedEl);
		switch (buttonIndex.row)
		{
		case 0:
		{
			switch (buttonIndex.col)
			{
			case 0:
			case 1:
				delete settings->field;
				settings->field = new Field(buttonIndex.col);
				break;
			default:
				break;
			}
			break;
		}
		case 1:
		{
			switch (buttonIndex.col)
			{
			case 0:
				settings->sleepTime = SleepTime::SLOW;
				break;
			case 1:
				settings->sleepTime = SleepTime::MEDIUM;
				break;
			case 2:
				settings->sleepTime = SleepTime::FAST;
				break;
			default:
				break;
			}
			break;
		}
		case 2:
		{
			switch (buttonIndex.col)
			{
			case 0:
				settings->snakeChar = SnakeChars::STAR;
				break;
			case 1:
				settings->snakeChar = SnakeChars::AMPERSANT;
				break;
			case 2:
				settings->snakeChar = SnakeChars::HASHTAG;
				break;
			default:
				break;
			}
			break;
		}	
		default:
			break;
		}
		if (buttonIndex.row != -1)
		{
			TossPressedElement(buttonIndex);
			Show();
		}
	}
}
