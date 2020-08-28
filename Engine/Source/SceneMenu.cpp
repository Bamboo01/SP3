#include "SceneMenu.h"
#include "SoundController.h"

void SceneMenu::Init()
{
	coordinator.Init();
	coordinator.RegisterComponent<Camera>();
	coordinator.RegisterComponent<Transform>();
	coordinator.RegisterComponent<RenderData>();
	coordinator.RegisterComponent<CanvasImage>();
	coordinator.RegisterComponent<CanvasText>();
	coordinator.RegisterComponent<CameraController>();
	coordinator.RegisterComponent<EntityState>();
	coordinator.RegisterComponent<MenuNexus>();
	coordinator.RegisterComponent<MenuUnit>();
	coordinator.RegisterComponent<ParticleSystemParameters>();
	coordinator.RegisterComponent<MenuGUI>();

	transformsystem = coordinator.RegisterSystem<TransformSystem>();
	camerasystem = coordinator.RegisterSystem<CameraSystem>();
	rendersystem = coordinator.RegisterSystem<RenderSystem>();
	canvasimagesystem = coordinator.RegisterSystem<CanvasImageSystem>();
	canvastextsystem = coordinator.RegisterSystem<CanvasTextSystem>();
	entitystatesystem = coordinator.RegisterSystem<EntityStateSystem>();
	particlesystem = coordinator.RegisterSystem<ParticleSystem>();

	menunexussystem = coordinator.RegisterSystem<MenuNexusSystem>();
	menuunitsystem = coordinator.RegisterSystem<MenuUnitSystem>();
	menucamerasystem = coordinator.RegisterSystem<MenuCameraSystem>();
	menuguisystem = coordinator.RegisterSystem<MenuGUISystem>();


	transformsystem->Setup();
	camerasystem->Setup();
	rendersystem->Setup();
	canvasimagesystem->Setup();
	canvastextsystem->Setup();
	entitystatesystem->Setup();
	menunexussystem->Setup();
	menuunitsystem->Setup();
	menucamerasystem->Setup();
	particlesystem->Setup();
	menuguisystem->Setup();

	Entity menuCamera = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(menuCamera, Transform());
	coordinator.AddComponent<EntityState>(menuCamera, EntityState(true));
	coordinator.AddComponent<Camera>(menuCamera, Camera(
		glm::vec3(0, 10, -30),
		glm::vec3(60, 0, 0),
		1080, 1080, //Lower this if the FPS stinks
		45.f,
		CAMERA_TYPE::CAMERA_MAIN,
		CAMERA_MODE::MODE_PERSPECTIVE
	));

	Entity menuNexus = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(menuNexus, Transform(
		glm::vec3(0.f), glm::vec3(1.f), glm::vec3(0.f), TRANSFORM_TYPE::DYNAMIC_TRANSFORM
	));
	coordinator.AddComponent<EntityState>(menuNexus, EntityState(true));
	coordinator.AddComponent<MenuNexus>(menuNexus, MenuNexus());
	coordinator.AddComponent<RenderData>(menuNexus, RenderData(renderer.getMesh(GEO_MENU_NEXUS), false));
	coordinator.AddComponent<ParticleSystemParameters>(menuNexus,
		ParticleSystemParameters(
			renderer.getMesh(GEO_CODEPARTICLE), 5, 5, 1,
			glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
			glm::vec3(-5, 15, -5), glm::vec3(5, 15, 5),
			glm::vec3(1.f, 1.f, 1.f), glm::vec3(1.f, 1.f, 1.f),
			glm::vec3(0.f), glm::vec3(0.f),
			glm::vec3(0.f), glm::vec3(0.f))
		);

	Entity Title = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(Title, Transform());
	coordinator.AddComponent<EntityState>(Title, EntityState());
	coordinator.AddComponent<CanvasText>(Title, CanvasText("HOLOWAR", ALIGN_CENTER, glm::vec3(1.f), 0.4f));
	coordinator.GetComponent<Transform>(Title).position = glm::vec3(0.06, 0.8, 0);
	coordinator.AddComponent<MenuGUI>(Title, MenuGUI(MenuGUI::START_BUTTON));

	Entity GUI_Start = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_Start, Transform());
	coordinator.AddComponent<EntityState>(GUI_Start, EntityState());
	coordinator.AddComponent<CanvasText>(GUI_Start, CanvasText("Start", ALIGN_CENTER));
	coordinator.GetComponent<Transform>(GUI_Start).position.y = -0.35;
	coordinator.AddComponent<MenuGUI>(GUI_Start, MenuGUI(MenuGUI::START_BUTTON));

	Entity GUI_Options = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_Options, Transform());
	coordinator.AddComponent<EntityState>(GUI_Options, EntityState());
	coordinator.AddComponent<CanvasText>(GUI_Options, CanvasText("Options", ALIGN_CENTER));
	coordinator.GetComponent<Transform>(GUI_Options).position.y = -0.50;
	coordinator.AddComponent<MenuGUI>(GUI_Options, MenuGUI(MenuGUI::OPTION_BUTTON));

	Entity GUI_Exit = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_Exit, Transform());
	coordinator.AddComponent<EntityState>(GUI_Exit, EntityState());
	coordinator.AddComponent<CanvasText>(GUI_Exit, CanvasText("Exit", ALIGN_CENTER));
	coordinator.GetComponent<Transform>(GUI_Exit).position.y = -0.80;
	coordinator.AddComponent<MenuGUI>(GUI_Exit, MenuGUI(MenuGUI::EXIT_BUTTON));

	Entity GUI_Credits = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_Credits, Transform());
	coordinator.AddComponent<EntityState>(GUI_Credits, EntityState());
	coordinator.AddComponent<CanvasText>(GUI_Credits, CanvasText("Credits", ALIGN_CENTER));
	coordinator.GetComponent<Transform>(GUI_Credits).position.y = -1.2f;
	coordinator.AddComponent<MenuGUI>(GUI_Credits, MenuGUI(MenuGUI::CREDITS_BUTTON));

	Entity GUI_VolumeUp = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_VolumeUp, Transform());
	coordinator.AddComponent<EntityState>(GUI_VolumeUp, EntityState());
	coordinator.AddComponent<CanvasText>(GUI_VolumeUp, CanvasText("VolumeUp", ALIGN_CENTER));
	coordinator.GetComponent<Transform>(GUI_VolumeUp).position.y = -0.35;
	coordinator.AddComponent<MenuGUI>(GUI_VolumeUp, MenuGUI(MenuGUI::AUDIO_INCREASE_BUTTON));

	Entity GUI_VolumeDown = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_VolumeDown, Transform());
	coordinator.AddComponent<EntityState>(GUI_VolumeDown, EntityState());
	coordinator.AddComponent<CanvasText>(GUI_VolumeDown, CanvasText("VolumeDown", ALIGN_CENTER));
	coordinator.GetComponent<Transform>(GUI_VolumeDown).position.y = -0.50;
	coordinator.AddComponent<MenuGUI>(GUI_VolumeDown, MenuGUI(MenuGUI::AUDIO_DECREASE_BUTTON));

	Entity GUI_BackToMainMenu = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_BackToMainMenu, Transform());
	coordinator.AddComponent<EntityState>(GUI_BackToMainMenu, EntityState());
	coordinator.AddComponent<CanvasText>(GUI_BackToMainMenu, CanvasText("Back"));
	coordinator.GetComponent<Transform>(GUI_BackToMainMenu).position.y = -1.05;
	coordinator.AddComponent<MenuGUI>(GUI_BackToMainMenu, MenuGUI(MenuGUI::BACK_BUTTON));

	Entity GUI_VolumeMeter = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_VolumeMeter, Transform());
	coordinator.AddComponent<EntityState>(GUI_VolumeMeter, EntityState());
	coordinator.AddComponent<CanvasText>(GUI_VolumeMeter, CanvasText("Volume: ", ALIGN_CENTER));
	coordinator.GetComponent<Transform>(GUI_VolumeMeter).position.y = -0.65;
	coordinator.AddComponent<MenuGUI>(GUI_VolumeMeter, MenuGUI());

	Entity GUI_Instructionbutton = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_Instructionbutton, Transform());
	coordinator.AddComponent<EntityState>(GUI_Instructionbutton, EntityState());
	coordinator.AddComponent<CanvasText>(GUI_Instructionbutton, CanvasText("Instruction", ALIGN_CENTER));
	coordinator.GetComponent<Transform>(GUI_Instructionbutton).position.y = -0.65;
	coordinator.AddComponent<MenuGUI>(GUI_Instructionbutton, MenuGUI(MenuGUI::INSTRUCTION_BUTTON));

	Entity GUI_Instructions = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_Instructions, Transform());
	coordinator.AddComponent<EntityState>(GUI_Instructions, EntityState());
	coordinator.AddComponent<CanvasText>(GUI_Instructions, CanvasText("INSTRUCTIONS", ALIGN_CENTER));
	coordinator.GetComponent<Transform>(GUI_Instructions).position.y = 0.30;
	coordinator.AddComponent<MenuGUI>(GUI_Instructions, MenuGUI());

	Entity GUI_Escape = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_Escape, Transform());
	coordinator.AddComponent<EntityState>(GUI_Escape, EntityState());
	coordinator.AddComponent<CanvasText>(GUI_Escape, CanvasText("ESCAPE Key -> Menu Screen", ALIGN_CENTER));
	coordinator.GetComponent<Transform>(GUI_Escape).position.y = 0.15;
	coordinator.AddComponent<MenuGUI>(GUI_Escape, MenuGUI());

	Entity GUI_LeftMousePress = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_LeftMousePress, Transform());
	coordinator.AddComponent<EntityState>(GUI_LeftMousePress, EntityState());
	coordinator.AddComponent<CanvasText>(GUI_LeftMousePress, CanvasText("Left Click: Select units by dragging & Interact with UI ", ALIGN_CENTER));
	coordinator.GetComponent<Transform>(GUI_LeftMousePress).position.y = 0.0;
	coordinator.AddComponent<MenuGUI>(GUI_LeftMousePress, MenuGUI());

	Entity GUI_RightMousePress = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_RightMousePress, Transform());
	coordinator.AddComponent<EntityState>(GUI_RightMousePress, EntityState());
	coordinator.AddComponent<CanvasText>(GUI_RightMousePress, CanvasText("Right Click: Move Selected Units", ALIGN_CENTER));
	coordinator.GetComponent<Transform>(GUI_RightMousePress).position.y = -0.15;
	coordinator.AddComponent<MenuGUI>(GUI_RightMousePress, MenuGUI());

	Entity GUI_ScrollWheel = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_ScrollWheel, Transform());
	coordinator.AddComponent<EntityState>(GUI_ScrollWheel, EntityState());
	coordinator.AddComponent<CanvasText>(GUI_ScrollWheel, CanvasText("Scroll Wheel: Rotate/Zoom Camera", ALIGN_CENTER));
	coordinator.GetComponent<Transform>(GUI_ScrollWheel).position.y = -0.30;
	coordinator.AddComponent<MenuGUI>(GUI_ScrollWheel, MenuGUI());


	menuguisystem->GUI_BackToMainMenu = GUI_BackToMainMenu;
	menuguisystem->GUI_Exit = GUI_Exit;
	menuguisystem->GUI_Options = GUI_Options;
	menuguisystem->GUI_Start = GUI_Start;
	menuguisystem->GUI_VolumeDown = GUI_VolumeDown;
	menuguisystem->GUI_VolumeUp = GUI_VolumeUp;
	menuguisystem->GUI_VolumeMeter = GUI_VolumeMeter;
	menuguisystem->GUI_Credits = GUI_Credits;

	menuguisystem->GUI_Instructionbutton = GUI_Instructionbutton;
	menuguisystem->GUI_Instructions = GUI_Instructions;
	menuguisystem->GUI_Escape = GUI_Escape;
	menuguisystem->GUI_LeftMousePress = GUI_LeftMousePress;
	menuguisystem->GUI_RightMousePress = GUI_RightMousePress;
	menuguisystem->GUI_ScrollWheel = GUI_ScrollWheel;

	menunexussystem->Init();
	menuunitsystem->Init();
	menucamerasystem->Init();
	menuguisystem->Init();
	particlesystem->Init();

	camerasystem->Init();
	rendersystem->Init();
	transformsystem->Init();
	canvasimagesystem->Init();
	canvastextsystem->Init();
	entitystatesystem->Init();
}

void SceneMenu::EarlyUpdate(double dt)
{
	camerasystem->EarlyUpdate(dt);
	rendersystem->EarlyUpdate(dt);
	transformsystem->EarlyUpdate(dt);
	canvasimagesystem->EarlyUpdate(dt);
	canvastextsystem->EarlyUpdate(dt);
	entitystatesystem->EarlyUpdate(dt);
}

void SceneMenu::Update(double dt)
{
	menunexussystem->Update(dt);
	menuunitsystem->Update(dt);
	menucamerasystem->Update(dt);
	particlesystem->Update(dt);
	menuguisystem->Update(dt);

	camerasystem->Update(dt);
	rendersystem->Update(dt);
	transformsystem->Update(dt);
	canvasimagesystem->Update(dt);
	canvastextsystem->Update(dt);
	entitystatesystem->Update(dt);
}

void SceneMenu::LateUpdate(double dt)
{
	camerasystem->LateUpdate(dt);
	rendersystem->LateUpdate(dt);
	transformsystem->LateUpdate(dt);
	canvasimagesystem->LateUpdate(dt);
	canvastextsystem->LateUpdate(dt);
	entitystatesystem->LateUpdate(dt);
}

void SceneMenu::PreRender()
{

}

void SceneMenu::Render()
{
	menuguisystem->Render();
	particlesystem->Render();
	rendersystem->Render();
	entitystatesystem->Render();
	transformsystem->Render();
	camerasystem->Render();
	canvasimagesystem->Render();
	canvastextsystem->Render();
}

void SceneMenu::PostRender()
{

}

void SceneMenu::Exit()
{
	CSoundController::GetInstance()->StopAllSounds();
}
