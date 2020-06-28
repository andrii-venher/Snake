#include "Menu.h"

void Menu::Show() const
{
	system("cls");
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < elements.size(); i++)
	{
		SetConsoleCursorPosition(h, elements[i].c);
		cout << elements[i].title;
	}
}

void Menu::Add(const MenuElement& el)
{
	elements.push_back(el);
}

int Menu::ClickedElement()
{
	COORD click = click_coordinate();
	for (int i = 0; i < elements.size(); i++)
	{
		if (click.Y == elements[i].c.Y && click.X >= elements[i].c.X && click.X <= elements[i].c.X + elements[i].title.length())
		{
			return i;
		}
	}
	return -1;
}
