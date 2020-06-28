#pragma once

#include "Menu.h"
#include "GameProcess.h"
#include "SettingsMenu.h"
#include "GameSettings.h"
#include "TitresMenu.h"

class UserInterface : public Menu
{
	GameProcess* process;
	SettingsMenu* settingMenu;
	GameSettings* settings;
	TitresMenu* titres;

	void Init();
public:
	UserInterface();
	void Interact();
};

