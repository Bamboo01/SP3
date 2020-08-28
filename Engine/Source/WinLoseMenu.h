#pragma once

struct WinLoseMenu
{
	enum WinLoseType
	{
		NO_BUTTON,

		EXIT_BUTTON,

		CANVAS,
	};

	WinLoseType WinLosemenuGUIType;

	WinLoseMenu(WinLoseType type)
	{
		WinLosemenuGUIType = type;
	}

	WinLoseMenu()
	{
		WinLosemenuGUIType = NO_BUTTON;
	}
};