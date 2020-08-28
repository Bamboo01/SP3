#include "MenuGUISystem.h"
#include "Application.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "SoundController.h"
#include "SceneManager.h"

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
	CSoundController::GetInstance()->PlaySoundByID(999);
	GUI_Entities.push_back(GUI_Start);
	GUI_Entities.push_back(GUI_Exit);
	GUI_Entities.push_back(GUI_Options);
	GUI_Entities.push_back(GUI_VolumeUp);
	GUI_Entities.push_back(GUI_VolumeDown);
	GUI_Entities.push_back(GUI_VolumeMeter);
	GUI_Entities.push_back(GUI_BackToMainMenu);
	GUI_Entities.push_back(GUI_Instructionbutton);
	GUI_Entities.push_back(GUI_Credits);
}

void MenuGUISystem::Update(float dt)
{
	{
		auto& canvastext = coordinator.GetComponent<CanvasText>(GUI_VolumeMeter);
		canvastext.Text = "Volume: " + std::to_string(CSoundController::GetInstance()->GetMasterVolume());
	}

	for (const auto& entity : GUI_Entities)
	{
		if (!coordinator.GetComponent<EntityState>(entity).active)
		{
			continue;
		}

		auto& transform = coordinator.GetComponent<Transform>(entity);
		auto& canvastext = coordinator.GetComponent<CanvasText>(entity);
		auto& menugui = coordinator.GetComponent<MenuGUI>(entity);

		canvastext.size = 0.1f;
	
		if (CollideWithCanvas(transform.position.x, transform.position.y, canvastext.size, canvastext.size * 0.5f))
		{
			canvastext.size = 0.13f;
			switch (menugui.menuGUIType)
			{
			case MenuGUI::START_BUTTON:
				if (Application::IsMousePressed(0))
				{
					CSoundController::GetInstance()->PlaySoundByID(1000);
					SceneManager::getInstance()->ChangeScene(SCENE_COMBAT);
				}
				break;
			case MenuGUI::EXIT_BUTTON:
				if (Application::IsMousePressed(0))
				{
					CSoundController::GetInstance()->PlaySoundByID(1000);
					Application::exitProgram = true;
				}
				break;
			case MenuGUI::OPTION_BUTTON:
				if (Application::IsMousePressed(0))
				{
					CSoundController::GetInstance()->PlaySoundByID(1000);
					state = S_OPTIONS;
				}
				break;
			case MenuGUI::AUDIO_INCREASE_BUTTON:
				if (Application::IsMousePressed(0))
				{
					CSoundController::GetInstance()->MasterVolumeIncrease(dt);
				}
				break;
			case MenuGUI::AUDIO_DECREASE_BUTTON:
				if (Application::IsMousePressed(0))
				{
					CSoundController::GetInstance()->MasterVolumeDecrease(dt);
				}
				break;
			case MenuGUI::BACK_BUTTON:
				if (Application::IsMousePressed(0))
				{
					CSoundController::GetInstance()->PlaySoundByID(1000);
					state = S_MAIN_MENU;
				}
				break;
			case MenuGUI::INSTRUCTION_BUTTON:
				if (Application::IsMousePressed(0))
				{
					CSoundController::GetInstance()->PlaySoundByID(1000);
					state = S_INSTRUCTIONS;
				}
				break;
			case MenuGUI::CREDITS_BUTTON:
				if (Application::IsMousePressed(0))
				{
					SceneManager::getInstance()->ChangeScene(SCENE_CREDIT);
				}
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
		coordinator.GetComponent<EntityState>(GUI_Start).active = true;
		coordinator.GetComponent<EntityState>(GUI_Exit).active = true;
		coordinator.GetComponent<EntityState>(GUI_Options).active = true;
		coordinator.GetComponent<EntityState>(GUI_VolumeUp).active = false;
		coordinator.GetComponent<EntityState>(GUI_VolumeDown).active = false;;
		coordinator.GetComponent<EntityState>(GUI_BackToMainMenu).active = false;
		coordinator.GetComponent<EntityState>(GUI_VolumeMeter).active = false;

		coordinator.GetComponent<EntityState>(GUI_Instructionbutton).active = true;
		coordinator.GetComponent<EntityState>(GUI_Instructions).active = false;
		coordinator.GetComponent<EntityState>(GUI_Escape).active = false;
		coordinator.GetComponent<EntityState>(GUI_LeftMousePress).active = false;
		coordinator.GetComponent<EntityState>(GUI_RightMousePress).active = false;
		coordinator.GetComponent<EntityState>(GUI_ScrollWheel).active = false;

	}
	else if (state == S_OPTIONS)
	{
		coordinator.GetComponent<EntityState>(GUI_Start).active = false;
		coordinator.GetComponent<EntityState>(GUI_Exit).active = false;
		coordinator.GetComponent<EntityState>(GUI_Options).active = false;
		coordinator.GetComponent<EntityState>(GUI_VolumeUp).active = true;
		coordinator.GetComponent<EntityState>(GUI_VolumeDown).active = true;
		coordinator.GetComponent<EntityState>(GUI_BackToMainMenu).active = true;
		coordinator.GetComponent<EntityState>(GUI_VolumeMeter).active = true;

		coordinator.GetComponent<EntityState>(GUI_Instructionbutton).active = false;
		coordinator.GetComponent<EntityState>(GUI_Instructions).active = false;
		coordinator.GetComponent<EntityState>(GUI_Escape).active = false;
		coordinator.GetComponent<EntityState>(GUI_LeftMousePress).active = false;
		coordinator.GetComponent<EntityState>(GUI_RightMousePress).active = false;
		coordinator.GetComponent<EntityState>(GUI_ScrollWheel).active = false;
	}
	else if (state == S_INSTRUCTIONS)
	{
		coordinator.GetComponent<EntityState>(GUI_Start).active = false;
		coordinator.GetComponent<EntityState>(GUI_Exit).active = false;
		coordinator.GetComponent<EntityState>(GUI_Options).active = false;
		coordinator.GetComponent<EntityState>(GUI_VolumeUp).active = false;
		coordinator.GetComponent<EntityState>(GUI_VolumeDown).active = false;
		coordinator.GetComponent<EntityState>(GUI_BackToMainMenu).active = true;
		coordinator.GetComponent<EntityState>(GUI_VolumeMeter).active = false;

		coordinator.GetComponent<EntityState>(GUI_Instructionbutton).active = false;
		coordinator.GetComponent<EntityState>(GUI_Instructions).active = true;
		coordinator.GetComponent<EntityState>(GUI_Escape).active = true;
		coordinator.GetComponent<EntityState>(GUI_LeftMousePress).active = true;
		coordinator.GetComponent<EntityState>(GUI_RightMousePress).active = true;
		coordinator.GetComponent<EntityState>(GUI_ScrollWheel).active = true;
	}
}

MenuGUISystem::~MenuGUISystem()
{
}
