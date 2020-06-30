#include "GameProcess.h"

GameProcess::GameProcess(const GameSettings* settings)
{
	this->settings = *settings;
	snake = new Snake({ (short)settings->field->GetWidth() / 2, (short)settings->field->GetHeight() / 2 }, settings->snakeChar);
	info = new GameInfo;
	info->place = { 0, (short)settings->field->GetHeight() + 1 };
	info->score = 0;
	info->rawTime = 0;
}

void GameProcess::Show()
{
	system("cls");
	settings.field->Print();
	snake->Paint();
	SpawnEgg();
}

void GameProcess::CheckRotation()
{
	int key;
	if (_kbhit()) {
		key = _getch();
		if (key == (int)Keys::ARROW) {
			key = _getch();
		}
	}
	else
	{
		key = NULL;
	}
	switch (key)
	{
	case (int)Keys::UPPERARROW:
		if(snake->GetDir() != DOWN)
			snake->SetDir(UP);
		break;
	case (int)Keys::RIGHTARROW:
		if (snake->GetDir() != LEFT)
			snake->SetDir(RIGHT);
		break;
	case (int)Keys::DOWNARROW:
		if (snake->GetDir() != UP)
			snake->SetDir(DOWN);
		break;
	case (int)Keys::LEFTARROW:
		if (snake->GetDir() != RIGHT)
			snake->SetDir(LEFT);
		break;
	case NULL:
		break;
	default:
		break;
	}
}

bool GameProcess::CheckLose()
{
	if (snake->CheckCrash() || (*settings.field)(snake->Head().Y, snake->Head().X) == FieldObjects::WALL)
	{
		MessageBoxA(0, "YOU LOST!", "GAMEOVER", MB_OK);
		return true;
	}

	return false;
}

void GameProcess::CheckGrow()
{
	if ((*settings.field)(snake->Head().Y, snake->Head().X) == FieldObjects::EGG)
	{
		snake->Grow();
		info->score++;
		(*settings.field)(snake->Head().Y, snake->Head().X) = FieldObjects::EMPTY;
		SpawnEgg();
	}
}

void GameProcess::UpdateInfo()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, info->place);
	cout << "score: " << info->score << endl;
	cout << "time: " << info->rawTime / 1000;
}

void GameProcess::SpawnEgg()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int radius = 3;

	while (true)
	{
		short x = rand() % (settings.field->GetWidth() - 1) + 1;
		short y = rand() % (settings.field->GetHeight() - 1) + 1;
		
		if ((*settings.field)(y, x) != FieldObjects::WALL &&
			pow(x - snake->Head().X, 2) + pow(y - snake->Head().Y, 2) > radius &&
			pow(x - snake->Tail().X, 2) + pow(y - snake->Tail().Y, 2) > radius)
		{
			(*settings.field)(y, x) = FieldObjects::EGG;
			SetConsoleCursorPosition(h, { x, y });
			cout << "$";
			break;
		}
	}
}

void GameProcess::Tick()
{
	while (!CheckLose())
	{
		CheckRotation();
		snake->Move();
		CheckGrow();
		UpdateInfo();
		Wait(settings.sleepTime);
	}
}

void GameProcess::Wait(unsigned int milliseconds)
{
	if(snake->GetDir() != NONE)
		info->rawTime += settings.sleepTime;
	Sleep(settings.sleepTime);
}
