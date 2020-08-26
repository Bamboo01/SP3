#include "SceneMenu.h"

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

	Entity GUI_Start = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_Start, Transform());
	coordinator.AddComponent<EntityState>(GUI_Start, EntityState());
	coordinator.AddComponent<CanvasText>(GUI_Start, CanvasText("Start", ALIGN_CENTER, glm::vec3(1.f), 0.01f));
	//coordinator.GetComponent<Transform>(GUI_Start).position.y = -0.15;
	coordinator.AddComponent<MenuGUI>(GUI_Start, MenuGUI(MenuGUI::START_BUTTON));

	//Entity GUI_Exit = coordinator.CreateEntity();
	//coordinator.AddComponent<Transform>(GUI_Exit, Transform());
	//coordinator.AddComponent<EntityState>(GUI_Exit, EntityState());
	//coordinator.AddComponent<CanvasText>(GUI_Exit, CanvasText("Exit"));
	//coordinator.GetComponent<Transform>(GUI_Exit).position.y = -0.25;
	//coordinator.AddComponent<MenuGUI>(GUI_Exit, MenuGUI(MenuGUI::EXIT_BUTTON));

	//Entity GUI_Options = coordinator.CreateEntity();
	//coordinator.AddComponent<Transform>(GUI_Options, Transform());
	//coordinator.AddComponent<EntityState>(GUI_Options, EntityState());
	//coordinator.AddComponent<CanvasText>(GUI_Options, CanvasText("Options"));
	//coordinator.GetComponent<Transform>(GUI_Options).position.y = -0.20;
	//coordinator.AddComponent<MenuGUI>(GUI_Options, MenuGUI(MenuGUI::OPTION_BUTTON));

	//Entity GUI_VolumeUp = coordinator.CreateEntity();
	//coordinator.AddComponent<Transform>(GUI_VolumeUp, Transform());
	//coordinator.AddComponent<EntityState>(GUI_VolumeUp, EntityState());
	//coordinator.AddComponent<CanvasText>(GUI_VolumeUp, CanvasText("VolumeUp"));
	//coordinator.AddComponent<MenuGUI>(GUI_VolumeUp, MenuGUI(MenuGUI::AUDIO_INCREASE_BUTTON));

	//Entity GUI_VolumeDown = coordinator.CreateEntity();
	//coordinator.AddComponent<Transform>(GUI_VolumeDown, Transform());
	//coordinator.AddComponent<EntityState>(GUI_VolumeDown, EntityState());
	//coordinator.AddComponent<CanvasText>(GUI_VolumeDown, CanvasText("VolumeDown"));
	//coordinator.AddComponent<MenuGUI>(GUI_VolumeDown, MenuGUI(MenuGUI::AUDIO_DECREASE_BUTTON));

	//Entity GUI_BackToMainMenu = coordinator.CreateEntity();
	//coordinator.AddComponent<Transform>(GUI_BackToMainMenu, Transform());
	//coordinator.AddComponent<EntityState>(GUI_BackToMainMenu, EntityState());
	//coordinator.AddComponent<CanvasText>(GUI_BackToMainMenu, CanvasText("BackToMainMenu"));
	//coordinator.AddComponent<MenuGUI>(GUI_BackToMainMenu, MenuGUI(MenuGUI::BACK_BUTTON));

	//Entity GUI_VolumeMeter = coordinator.CreateEntity();
	//coordinator.AddComponent<Transform>(GUI_VolumeMeter, Transform());
	//coordinator.AddComponent<EntityState>(GUI_VolumeMeter, EntityState());
	//coordinator.AddComponent<CanvasText>(GUI_VolumeMeter, CanvasText("VolumeMeter"));
	//coordinator.AddComponent<MenuGUI>(GUI_VolumeMeter, MenuGUI());


	menunexussystem->Init();
	menuunitsystem->Init();
	menucamerasystem->Init();
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
}
