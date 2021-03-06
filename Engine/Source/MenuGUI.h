#pragma once

struct MenuGUI
{
	enum MENU_GUI_TYPES
	{
		NO_BUTTON,
		START_BUTTON,

		OPTION_BUTTON,
		AUDIO_INCREASE_BUTTON,
		AUDIO_DECREASE_BUTTON,
		BACK_BUTTON,

		INSTRUCTION_BUTTON,
		CREDITS_BUTTON,

		EXIT_BUTTON,
	};

	MENU_GUI_TYPES menuGUIType;

	MenuGUI(MENU_GUI_TYPES type)
	{
		menuGUIType = type;
	}

	MenuGUI()
	{
		menuGUIType = NO_BUTTON;
	}
};