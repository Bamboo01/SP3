#include "PauseMenuSystem.h"
#include "Application.h"
#include "SoundController.h"

bool PauseMenuSystem::CollideWithCanvas(float x, float y, float xscale, float yscale)
{
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
	if (mousex > bottomleftx && mousex < toprightx && mousey > bottomlefty && mousey < toprighty)
		return true;
	return false;
}

void PauseMenuSystem::Setup()
{
	state = S_NONE;
}

void PauseMenuSystem::Init()
{
	PauseGUI_Entities.push_back(GUI_Resume);
	PauseGUI_Entities.push_back(GUI_Exit);
	PauseGUI_Entities.push_back(GUI_Options);
	PauseGUI_Entities.push_back(GUI_VolumeUp);
	PauseGUI_Entities.push_back(GUI_VolumeDown);
	PauseGUI_Entities.push_back(GUI_BackToPauseMenu);
	PauseGUI_Entities.push_back(GUI_VolumeMeter);

	timer = 0;
	escape_delay = 0;
}

void PauseMenuSystem::Update(float dt)
{
	timer += dt;

	if (Application::IsKeyPressed(VK_ESCAPE) && escape_delay < timer)
	{
		if (state == S_PAUSE_MENU || state == S_OPTIONS)
			state = S_NONE;
		else if (state == S_NONE)
			state = S_PAUSE_MENU;
		

		escape_delay = timer + 0.3;
	}

	{
		auto& canvastext = coordinator.GetComponent<CanvasText>(GUI_VolumeMeter);
		canvastext.Text = "Volume: " + std::to_string(CSoundController::GetInstance()->GetMasterVolume());
	}

	for (const auto& entity : PauseGUI_Entities)
	{
		if (!coordinator.GetComponent<EntityState>(entity).active)
		{
			continue;
		}

		auto& transform = coordinator.GetComponent<Transform>(entity);
		auto& canvastext = coordinator.GetComponent<CanvasText>(entity);
		canvastext.size = 0.1f;

		if (CollideWithCanvas(transform.position.x, transform.position.y + (0.2 * canvastext.size), canvastext.size, canvastext.size))
		{

			canvastext.size = 0.13f;
			auto& pausegui = coordinator.GetComponent<PauseMenu>(entity);
			switch (pausegui.PausemenuGUIType)
			{
			case PauseMenu::RESUME_BUTTON:
				if (Application::IsMousePressed(0))
				{
					state = S_NONE;
				}
				break;
			case PauseMenu::EXIT_BUTTON:
				if (Application::IsMousePressed(0))
				{
					Application::exitProgram = true;
				}
				break;
			case PauseMenu::OPTION_BUTTON:
				if (Application::IsMousePressed(0))
				{
					state = S_OPTIONS;
				}
				break;
			case PauseMenu::AUDIO_INCREASE_BUTTON:
				if (Application::IsMousePressed(0))
				{
					CSoundController::GetInstance()->MasterVolumeIncrease(dt);
				}
				break;
			case PauseMenu::AUDIO_DECREASE_BUTTON:
				if (Application::IsMousePressed(0))
				{
					CSoundController::GetInstance()->MasterVolumeDecrease(dt);
				}
				break;
			case PauseMenu::BACK_BUTTON:
				if (Application::IsMousePressed(0))
				{
					state = S_PAUSE_MENU;
				}
				break;
			default:
				canvastext.size = 0.1f;
				break;
			}
		}
	}
}

void PauseMenuSystem::Render()
{
	if (state == S_PAUSE_MENU)
	{
		coordinator.GetComponent<EntityState>(GUI_Resume).active = true;
		coordinator.GetComponent<EntityState>(GUI_Exit).active = true;
		coordinator.GetComponent<EntityState>(GUI_Options).active = true;
		coordinator.GetComponent<EntityState>(GUI_VolumeUp).active = false;
		coordinator.GetComponent<EntityState>(GUI_VolumeDown).active = false;;
		coordinator.GetComponent<EntityState>(GUI_BackToPauseMenu).active = false;
		coordinator.GetComponent<EntityState>(GUI_VolumeMeter).active = false;
		coordinator.GetComponent<EntityState>(PauseCanvas).active = true;
	}
	else if (state == S_OPTIONS)
	{
		coordinator.GetComponent<EntityState>(GUI_Resume).active = false;
		coordinator.GetComponent<EntityState>(GUI_Exit).active = false;
		coordinator.GetComponent<EntityState>(GUI_Options).active = false;
		coordinator.GetComponent<EntityState>(GUI_VolumeUp).active = true;
		coordinator.GetComponent<EntityState>(GUI_VolumeDown).active = true;
		coordinator.GetComponent<EntityState>(GUI_BackToPauseMenu).active = true;
		coordinator.GetComponent<EntityState>(GUI_VolumeMeter).active = true;
		coordinator.GetComponent<EntityState>(PauseCanvas).active = true;
	}
	else if (state == S_NONE)
	{
		coordinator.GetComponent<EntityState>(GUI_Resume).active = false;
		coordinator.GetComponent<EntityState>(GUI_Exit).active = false;
		coordinator.GetComponent<EntityState>(GUI_Options).active = false;
		coordinator.GetComponent<EntityState>(GUI_VolumeUp).active = false;
		coordinator.GetComponent<EntityState>(GUI_VolumeDown).active = false;
		coordinator.GetComponent<EntityState>(GUI_BackToPauseMenu).active = false;
		coordinator.GetComponent<EntityState>(GUI_VolumeMeter).active = false;
		coordinator.GetComponent<EntityState>(PauseCanvas).active = false;
	}
}

PauseMenuSystem::~PauseMenuSystem()
{
}
