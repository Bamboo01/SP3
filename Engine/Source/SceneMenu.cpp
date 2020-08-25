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


	transformsystem->Setup();
	camerasystem->Setup();
	rendersystem->Setup();
	canvasimagesystem->Setup();
	canvastextsystem->Setup();
	entitystatesystem->Setup();

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
			renderer.getMesh(GEO_CODEPARTICLE), 5, 50, 1,
			glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
			glm::vec3(-1, 15, -1), glm::vec3(1, 15, 1),
			glm::vec3(10.f, 10.f, 1.f), glm::vec3(10.f, 10.f, 1.f),
			glm::vec3(0.f), glm::vec3(0.f),
			glm::vec3(0.f), glm::vec3(0.f))
		);

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
