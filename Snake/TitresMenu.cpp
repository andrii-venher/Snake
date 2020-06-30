#include "TitresMenu.h"

TitresMenu::TitresMenu()
{
	SetHeader({ "TITRES", {5, 0}, MENU_ELEMENT_TYPE::LABEL, false });
	MenuRow row;
	row.name = { "Created by Andrey Venger", {0, 1}, MENU_ELEMENT_TYPE::LABEL, false };
	AddRow(row);
	SetEnding({ "BACK", {5, 3}, MENU_ELEMENT_TYPE::EXIT, false });
}

void TitresMenu::Interact()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	while (true)
	{
		MenuElement clickedEl = ClickedElement();
		if (clickedEl.type == MENU_ELEMENT_TYPE::EXIT)
			return;
	}
}
