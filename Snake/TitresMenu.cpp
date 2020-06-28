#include "TitresMenu.h"

TitresMenu::TitresMenu()
{
	Add({ "creator - Venger Andrey", {0,0}, false });
	Add({ "back", {0,1}, false });
}

void TitresMenu::Interact()
{
	while (true)
	{
		int index = ClickedElement();
		switch (index)
		{
		case 1:
			return;
		default:
			break;
		}
	}
}
