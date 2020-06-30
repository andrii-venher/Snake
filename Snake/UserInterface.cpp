#include "UserInterface.h"

void UserInterface::Init()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = false;
	cursorInfo.dwSize = 100;
	SetConsoleCursorInfo(h, &cursorInfo);

	system("title Snake");
	MoveWindow(GetConsoleWindow(), 0, 0, 0, 0, true);
	system("mode con cols=72 lines=33");
}

UserInterface::UserInterface()
{
	settings = new GameSettings;
	settings->sleepTime = 200;
	settings->snakeChar = SnakeChars::STAR;
	settings->field = new Field();

	SetHeader({ "SNAKE", { 5, 0 }, MENU_ELEMENT_TYPE::LABEL, false });
	SetEnding({ "EXIT", { 5, 5 }, MENU_ELEMENT_TYPE::EXIT, false });

	MenuRow row;

	row.values.push_back({ "new game", { 0, 1 }, MENU_ELEMENT_TYPE::BUTTON, false });
	AddRow(row);
	row.Clear();

	row.values.push_back({ "settings", { 0, 2 }, MENU_ELEMENT_TYPE::BUTTON, false });
	AddRow(row);
	row.Clear();

	row.values.push_back({ "about game", { 0, 3 }, MENU_ELEMENT_TYPE::BUTTON, false });
	AddRow(row);
	row.Clear();

	Init();

	Show();
}

void UserInterface::Interact()
{
	while (true)
	{
		MenuElement clickedEl = ClickedElement();
		if (clickedEl.type == MENU_ELEMENT_TYPE::EXIT)
			exit(0);
		MatrixIndex buttonIndex = GetElementIndex(clickedEl);
		switch (buttonIndex.row)
		{
		case 0:
			process = new GameProcess(settings);
			process->Show();
			process->Tick();
			delete process;
			Show();
			break;
		case 1:
			settingMenu = new SettingsMenu(settings);
			settingMenu->Show();
			settingMenu->Interact();
			delete settingMenu;
			Show();
			break;
		case 2:
			titres = new TitresMenu();
			titres->Show();
			titres->Interact();
			delete titres;
			Show();
			break;
		default:
			break;
		}
	}
}

