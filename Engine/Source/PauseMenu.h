#pragma once

struct PauseMenu
{
	enum PauseType
	{
		NO_BUTTON,
		RESUME_BUTTON,

		OPTION_BUTTON,
		AUDIO_INCREASE_BUTTON,
		AUDIO_DECREASE_BUTTON,
		BACK_BUTTON,

		EXIT_BUTTON,

		CANVAS,
	};

	PauseType PausemenuGUIType;

	PauseMenu(PauseType type)
	{
		PausemenuGUIType = type;
	}

	PauseMenu()
	{
		PausemenuGUIType = NO_BUTTON;
	}
};