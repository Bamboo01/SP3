#include "System.h"
#include <vector>
#include "Entity.h"
#include "Coordinator.h"
#include "Transform.h"
#include "ParticleSystemParameters.h"
#include "RenderData.h"
#include "MenuNexus.h"
#include "MenuGUI.h"
#include "CanvasText.h"

extern Coordinator coordinator;
#pragma once

class MenuGUISystem : public System
{
private:
	enum MENU_STATE
	{
		S_MAIN_MENU,
		S_OPTIONS
	};
public:
	Entity GUI_Start;
	Entity GUI_Exit;
	Entity GUI_Options;
	Entity GUI_VolumeUp;
	Entity GUI_VolumeDown;
	Entity GUI_BackToMainMenu;
	Entity GUI_VolumeMeter;
	
	std::vector<Entity> GUI_Entities;

	MENU_STATE state;

	bool CollideWithCanvas(float x, float y, float xscale, float yscale);

	void Setup();
	void Init();
	void Update(float dt);
	void Render();

	~MenuGUISystem();
};
