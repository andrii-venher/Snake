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
	settings->snakeChar = SnakeChar::STAR;
	settings->field = new Field();

	Add({ "new game", { 0, 0 }, false });
	Add({ "settings", { 0, 1 }, false });
	Add({ "about game", { 0, 2 }, false });
	Add({ "exit", { 0, 3 }, false });

	Init();

	Show();
}

void UserInterface::Interact()
{
	while (true)
	{
		int index = ClickedElement();
		switch (index)
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
		case 3:
			exit(0);
		default:
			break;
		}
	}
}

