#include "MenuGUISystem.h"
#include "Application.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

bool MenuGUISystem::CollideWithCanvas(float x, float y, float xscale, float yscale)
{
	//Thanks Guang Theng ;P
	float bottomleftx, bottomlefty, toprightx, toprighty;

	float offsetx = Application::GetWindowWidth() - Application::GetWindowHeight();
	float offsety = Application::GetWindowHeight() - Application::GetWindowWidth();

	if (Application::GetWindowWidth() > Application::GetWindowHeight())
		offsety = 0;
	else if (Application::GetWindowWidth() < Application::GetWindowHeight())
		offsetx = 0;

	float newx = ((x + 1) / 2) * (Application::GetWindowWidth() - offsetx);
	float newy = ((y + 1) / 2) * (Application::GetWindowHeight() + offsety);
	float newxscale = (xscale) * (Application::GetWindowWidth() - offsetx);
	float newyscale = (yscale) * (Application::GetWindowHeight() + offsety);

	bottomleftx = newx - newxscale * 0.5 + (offsetx * 0.5);
	bottomlefty = (Application::GetWindowHeight() - newy) - newyscale * 0.5 - (offsety * 0.5);
	toprightx = newx + newxscale * 0.5 + (offsetx * 0.5);
	toprighty = (Application::GetWindowHeight() - newy) + newyscale * 0.5 - (offsety * 0.5);


	double mousex, mousey;
	Application::GetCursorPos(&mousex, &mousey);
	if (mousex > bottomleftx&& mousex < toprightx && mousey > bottomlefty&& mousey < toprighty)
		return true;
	return false;
}

void MenuGUISystem::Setup()
{
	state = S_MAIN_MENU;
}

void MenuGUISystem::Init()
{
	GUI_Entities.push_back(GUI_Start);
	GUI_Entities.push_back(GUI_Exit);
	GUI_Entities.push_back(GUI_Options);
	GUI_Entities.push_back(GUI_VolumeUp);
	GUI_Entities.push_back(GUI_VolumeDown);
	GUI_Entities.push_back(GUI_VolumeMeter);
	GUI_Entities.push_back(GUI_BackToMainMenu);
}

void MenuGUISystem::Update(float dt)
{
	for (const auto& entity : GUI_Entities)
	{
		if (!coordinator.GetComponent<EntityState>(entity).active)
		{
			continue;
		}

		auto& transform = coordinator.GetComponent<Transform>(entity);
		auto& canvastext = coordinator.GetComponent<CanvasText>(entity);
		canvastext.size = 0.1f;

		if (CollideWithCanvas(transform.position.x, transform.position.y, transform.scale.x, transform.scale.y))
		{
			canvastext.size = 0.3f;
			auto& menugui = coordinator.GetComponent<MenuGUI>(entity);
			switch (menugui.menuGUIType)
			{
			case MenuGUI::START_BUTTON:
				if (Application::IsMousePressed(1))
				{

				}
				break;
			case MenuGUI::EXIT_BUTTON:
				if (Application::IsMousePressed(1))
				{
					Application::exitProgram = true;
				}
				break;
			case MenuGUI::OPTION_BUTTON:
				if (Application::IsMousePressed(1))
				{

				}
				break;
			case MenuGUI::AUDIO_INCREASE_BUTTON:
				if (Application::IsMousePressed(1))
				{

				}
				break;
			case MenuGUI::AUDIO_DECREASE_BUTTON:
				if (Application::IsMousePressed(1))
				{

				}
				break;
			case MenuGUI::BACK_BUTTON:
				break;
			default:
				canvastext.size = 0.1f;
				break;
			}
		}
	}
}

void MenuGUISystem::Render()
{
	if (state == S_MAIN_MENU)
	{
		GUI_Start;
		GUI_Exit;
		GUI_Options;
		GUI_VolumeUp;
		GUI_VolumeDown;
		GUI_BackToMainMenu;
		GUI_VolumeMeter;
	}
}
