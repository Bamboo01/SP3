#include "WinLoseSystem.h"
#include "Application.h"
#include "SoundController.h"

bool WinLoseSystem::CollideWithCanvas(float x, float y, float xscale, float yscale)
{
	float bottomleftx, bottomlefty, toprightx, toprighty;

	float offsetx = Application::GetWindowWidth() - Application::GetWindowHeight();
	float offsety = Application::GetWindowHeight() - Application::GetWindowWidth();

	if (Application::GetWindowWidth() > Application::GetWindowHeight())
		offsety = 0;
	else if (Application::GetWindowWidth() < Application::GetWindowHeight())
		offsetx = 0;

	float newx = ((x + 1.5) / 3) * (Application::GetWindowWidth() - offsetx);
	float newy = ((y + 1.5) / 3) * (Application::GetWindowHeight() + offsety);
	float newxscale = (xscale) * (Application::GetWindowWidth() - offsetx);
	float newyscale = (yscale) * (Application::GetWindowHeight() + offsety);

	bottomleftx = newx - newxscale * 0.5 + (offsetx * 0.5);
	bottomlefty = (Application::GetWindowHeight() - newy) - newyscale * 0.5 - (offsety * 0.5);
	toprightx = newx + newxscale * 0.5 + (offsetx * 0.5);
	toprighty = (Application::GetWindowHeight() - newy) + newyscale * 0.5 - (offsety * 0.5);


	double mousex, mousey;
	Application::GetCursorPos(&mousex, &mousey);
	if (mousex > bottomleftx && mousex < toprightx && mousey > bottomlefty && mousey < toprighty)
		return true;
	return false;
}

void WinLoseSystem::Setup()
{
	state = S_NONE;

	NumOfUnitsBuilt = 0;
	NumOfUnitsDestroyed = 0;
	WinLose = 0;
	PlayerTotalUnit = 0;
}

void WinLoseSystem::Init()
{
	WinLoseGUI_Entities.push_back(GUI_Text);
	WinLoseGUI_Entities.push_back(GUI_Exit);
	WinLoseGUI_Entities.push_back(GUI_UnitsBuilt);
	WinLoseGUI_Entities.push_back(GUI_UnitsDestroyed);
	WinLoseGUI_Entities.push_back(GUI_UnitsLeft);
}

void WinLoseSystem::Update(float dt)
{
	{
		auto& canvastext = coordinator.GetComponent<CanvasText>(GUI_UnitsBuilt);
		canvastext.Text = "Units Built: " + std::to_string(NumOfUnitsBuilt);
	}
	{
		auto& canvastext = coordinator.GetComponent<CanvasText>(GUI_UnitsDestroyed);
		canvastext.Text = "Death Count: " + std::to_string(NumOfUnitsDestroyed);
	}
	{
		auto& canvastext = coordinator.GetComponent<CanvasText>(GUI_UnitsLeft);
		canvastext.Text = "Alive Count: " + std::to_string(PlayerTotalUnit);
	}

	if (WinLose == 1)
		state = S_LOSE;
	else if (WinLose == 2)
		state = S_WIN;

	if (state == S_WIN)
	{
		auto& canvastext = coordinator.GetComponent<CanvasText>(GUI_Text);
		canvastext.Text = "SUCCESSFULLY HACKED";
	}
	else if (state == S_LOSE)
	{
		auto& canvastext = coordinator.GetComponent<CanvasText>(GUI_Text);
		canvastext.Text = "MALWARE DESTROYED";
	}


	for (const auto& entity : WinLoseGUI_Entities)
	{
		if (!coordinator.GetComponent<EntityState>(entity).active)
		{
			continue;
		}
		auto& transform = coordinator.GetComponent<Transform>(entity);
		auto& canvastext = coordinator.GetComponent<CanvasText>(entity);
		canvastext.size = 0.1f;

		if (CollideWithCanvas(transform.position.x, transform.position.y, canvastext.size, canvastext.size))
		{
			canvastext.size = 0.13f;
			auto& winlosegui = coordinator.GetComponent<WinLoseMenu>(entity);
			switch (winlosegui.WinLosemenuGUIType)
			{
			case WinLoseMenu::EXIT_BUTTON:
				if (Application::IsMousePressed(0))
				{
					Application::exitProgram = true;
					CSoundController::GetInstance()->PlaySoundByID(1000);
				}
				break;
			default:
				canvastext.size = 0.1f;
				break;
			}
		}
	}
}

void WinLoseSystem::Render()
{
	if (state == S_WIN || state == S_LOSE)
	{
		coordinator.GetComponent<EntityState>(GUI_Text).active = true;
		coordinator.GetComponent<EntityState>(GUI_Exit).active = true;
		coordinator.GetComponent<EntityState>(GUI_UnitsBuilt).active = true;
		coordinator.GetComponent<EntityState>(GUI_UnitsDestroyed).active = true;
		coordinator.GetComponent<EntityState>(GUI_UnitsLeft).active = true;
		coordinator.GetComponent<EntityState>(WinLoseCanvas).active = true;
	}
	else
	{
		coordinator.GetComponent<EntityState>(GUI_Text).active = false;
		coordinator.GetComponent<EntityState>(GUI_Exit).active = false;
		coordinator.GetComponent<EntityState>(GUI_UnitsBuilt).active = false;
		coordinator.GetComponent<EntityState>(GUI_UnitsDestroyed).active = false;
		coordinator.GetComponent<EntityState>(GUI_UnitsLeft).active = false;
		coordinator.GetComponent<EntityState>(WinLoseCanvas).active = false;
	}
}

void WinLoseSystem::GetUnitsCreated(int create)
{
	NumOfUnitsBuilt = create;
}

void WinLoseSystem::GetUnitsKilled(int killed)
{
	NumOfUnitsDestroyed = killed;
}

WinLoseSystem::~WinLoseSystem()
{
}
