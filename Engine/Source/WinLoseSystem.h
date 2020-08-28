#include "System.h"
#include <vector>
#include "Entity.h"
#include "Coordinator.h"
#include "Transform.h"
#include "RenderData.h"
#include "WinLoseMenu.h"
#include "CanvasText.h"

extern Coordinator coordinator;
#pragma once

class WinLoseSystem : public System
{
private:
	enum WINLOSE_STATE
	{
		S_WIN,
		S_LOSE,
		S_NONE
	};

	double timer;
	double escape_delay;

public:
	Entity GUI_Text;
	Entity GUI_Exit;
	Entity GUI_UnitsBuilt;
	Entity GUI_UnitsDestroyed;
	Entity GUI_UnitsLeft;
	Entity WinLoseCanvas;

	std::vector<Entity> WinLoseGUI_Entities;

	WINLOSE_STATE state;

	bool CollideWithCanvas(float x, float y, float xscale, float yscale);

	int NumOfUnitsBuilt;
	int NumOfUnitsDestroyed;
	int PlayerTotalUnit;

	int WinLose; // 0 = none, 1 = lose, 2 = win

	void Setup();
	void Init();
	void Update(float dt);
	void Render();

	void GetUnitsCreated(int create);
	void GetUnitsKilled(int killed);

	~WinLoseSystem();
};
