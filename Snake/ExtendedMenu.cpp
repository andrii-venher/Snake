#include "ExtendedMenu.h"

void ExtendedMenu::Show()
{
	system("cls");
	cout << header;
	for (int i = 0; i < table.size(); i++)
	{
		cout << table[i].name;
		for (int j = 0; j < table[i].values.size(); j++)
		{
			cout << table[i].values[j];
		}
	}
	cout << ending;
}

MenuElement ExtendedMenu::ClickedElement()
{
	MenuElement noneIsPressed = { "NULL", {-1, -1}, MENU_ELEMENT_TYPE::LABEL, false };
	COORD click = click_coordinate();
	if (click.Y == header.c.Y && click.X >= header.c.X && click.X <= header.c.X + header.title.length())
	{
		return header;
	}
	if (click.Y == ending.c.Y && click.X >= ending.c.X && click.X <= ending.c.X + ending.title.length())
	{
		return ending;
	}
	for (int i = 0; i < table.size(); i++)
	{
		if (click.Y == table[i].name.c.Y && click.X >= table[i].name.c.X && click.X <= table[i].name.c.X + table[i].name.title.length())
		{
			return table[i].name;
		}
		for (int j = 0; j < table[i].values.size(); j++)
		{
			if (click.Y == table[i].values[j].c.Y && click.X >= table[i].values[j].c.X && click.X <= table[i].values[j].c.X + table[i].values[j].title.length())
			{
				return table[i].values[j];
			}
		}
	}
	return noneIsPressed;
}

void ExtendedMenu::TossPressedElement(MatrixIndex index)
{
	for (int k = 0; k < table[index.row].values.size(); k++)
	{
		if (table[index.row].values[k].isPressed)
			table[index.row].values[k].isPressed = false;
	}
	table[index.row].values[index.col].isPressed = true;
}

MatrixIndex ExtendedMenu::GetElementIndex(MenuElement el)
{
	if (el.type == MENU_ELEMENT_TYPE::BUTTON)
	{
		for (int i = 0; i < table.size(); i++)
		{
			for (int j = 0; j < table[i].values.size(); j++)
			{
				if (el == table[i].values[j])
					return MatrixIndex({ i, j });
			}
		}
	}
	return MatrixIndex({ -1,-1 });
}

void ExtendedMenu::SetHeader(const MenuElement& el)
{
	header = el;
}

void ExtendedMenu::SetEnding(const MenuElement& el)
{
	ending = el;
}

void ExtendedMenu::AddRow(const MenuRow& row)
{
	table.push_back(row);
}

void MenuRow::Clear()
{
	name = { "", {0, 0}, MENU_ELEMENT_TYPE::LABEL, false };
	values.clear();
}

ostream& operator<<(ostream& cout, MenuElement el)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, el.c);
	if (el.isPressed)
		SetConsoleTextAttribute(h, (int)Colors::GREEN);
	else
		SetConsoleTextAttribute(h, (int)Colors::WHITE);
	cout << el.title;
	SetConsoleTextAttribute(h, (int)Colors::WHITE);
	return cout;
}

bool MenuElement::operator==(MenuElement el)
{
	return this->c.X == el.c.X && this->c.Y == el.c.Y && this->isPressed == el.isPressed &&
		this->title == el.title && this->type == el.type;
}