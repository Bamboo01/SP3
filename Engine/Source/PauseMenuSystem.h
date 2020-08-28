#include "System.h"
#include <vector>
#include "Entity.h"
#include "Coordinator.h"
#include "Transform.h"
#include "RenderData.h"
#include "PauseMenu.h"
#include "CanvasText.h"

extern Coordinator coordinator;
#pragma once

class PauseMenuSystem : public System
{
private:
	enum PAUSE_STATE
	{
		S_PAUSE_MENU,
		S_OPTIONS,
		S_NONE
	};

	double timer;
	double escape_delay;

public:
	Entity GUI_Resume;
	Entity GUI_Exit;
	Entity GUI_Options;
	Entity GUI_VolumeUp;
	Entity GUI_VolumeDown;
	Entity GUI_BackToPauseMenu;
	Entity GUI_VolumeMeter;

	Entity PauseCanvas;

	std::vector<Entity> PauseGUI_Entities;

	PAUSE_STATE state;

	bool CollideWithCanvas(float x, float y, float xscale, float yscale);

	void Setup();
	void Init();
	void Update(float dt);
	void Render();

	~PauseMenuSystem();
};
