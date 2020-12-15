#include "SceneCamera.h"

void SceneCamera::Init()
{
	coordinator.Init();
	coordinator.RegisterComponent<Camera>();
	coordinator.RegisterComponent<Transform>();
	coordinator.RegisterComponent<RenderData>();
	coordinator.RegisterComponent<EntityState>();

	transformsystem = coordinator.RegisterSystem<TransformSystem>();
	camerasystem = coordinator.RegisterSystem<CameraSystem>();
	rendersystem = coordinator.RegisterSystem<RenderSystem>();
	entitystatesystem = coordinator.RegisterSystem<EntityStateSystem>();

	transformsystem->Setup();
	camerasystem->Setup();
	rendersystem->Setup();
	entitystatesystem->Setup();

	Entity maincamera = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(maincamera, Transform());
	coordinator.AddComponent<EntityState>(maincamera, EntityState(true));
	coordinator.AddComponent<Camera>(maincamera, Camera(
		glm::vec3(0, 0, 0),
		glm::vec3(0, 0, 0),
		1080, 1080, //Lower this if the FPS stinks
		45.f,
		CAMERA_TYPE::CAMERA_MAIN,
		CAMERA_MODE::MODE_ORTHOGRAPHIC
	));

	//Entity maincamera = coordinator.CreateEntity();
	//coordinator.AddComponent<Camera>(maincamera, Camera(
	//	glm::vec3(0, 0, -3.f),
	//	glm::vec3(0, 0, 0),
	//	800, 800, //Lower this if the FPS stinks
	//	45.f,
	//	CAMERA_TYPE::CAMERA_MAIN,
	//	CAMERA_MODE::MODE_PERSPECTIVE
	//));
	coordinator.AddComponent<EntityState>(maincamera, EntityState());

	Entity axes = coordinator.CreateEntity();
	coordinator.AddComponent<RenderData>(axes, RenderData(renderer.getMesh(GEO_AXES), false));
	coordinator.AddComponent<Transform>(axes, Transform());
	coordinator.GetComponent<Transform>(axes).type = TRANSFORM_TYPE::STATIC_TRANSFORM;
	coordinator.AddComponent<EntityState>(axes, EntityState());

	Entity quad = coordinator.CreateEntity();
	coordinator.AddComponent<RenderData>(quad, RenderData(renderer.getMesh(GEO_GUIQUAD), false));
	coordinator.AddComponent<Transform>(quad, Transform());
	coordinator.GetComponent<Transform>(quad).scale = glm::vec3(100, 100, 100);
	coordinator.GetComponent<Transform>(quad).type = TRANSFORM_TYPE::STATIC_TRANSFORM;
	coordinator.AddComponent<EntityState>(quad, EntityState());

	transformsystem->Init();
	camerasystem->Init();
	rendersystem->Init();
	entitystatesystem->Init();
}

void SceneCamera::EarlyUpdate(double dt)
{
	transformsystem->EarlyUpdate(dt);
	camerasystem->EarlyUpdate(dt);
	rendersystem->EarlyUpdate(dt);
}

void SceneCamera::Update(double dt)
{
	entitystatesystem->Update(dt);
	transformsystem->Update(dt);
	camerasystem->Update(dt);
	rendersystem->Update(dt);
}

void SceneCamera::LateUpdate(double dt)
{
	transformsystem->LateUpdate(dt);
	camerasystem->LateUpdate(dt);
	rendersystem->LateUpdate(dt);
}

void SceneCamera::PreRender()
{
}

void SceneCamera::Render()
{
	rendersystem->Render();
	transformsystem->Render();
	camerasystem->Render();
}

void SceneCamera::PostRender()
{
}

void SceneCamera::Exit()
{
	coordinator.Exit();
}
