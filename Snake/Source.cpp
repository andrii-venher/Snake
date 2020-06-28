#include <iostream>
#include <vector>

#include "Menu.h"
#include "Snake.h"
#include "GameProcess.h"
#include "UserInterface.h"

using namespace std;

int main()
{
	UserInterface UI;
	UI.Interact();

	Sleep(INFINITE);
}