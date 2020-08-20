#include "SceneTest.h"
#include "Application.h"

void SceneTest::Init()
{
	coordinator.Init();
	coordinator.RegisterComponent<Camera>();
	coordinator.RegisterComponent<Transform>();
	coordinator.RegisterComponent<RenderData>();
	coordinator.RegisterComponent<Unit>();
	coordinator.RegisterComponent<CameraController>();
	coordinator.RegisterComponent<GridControllerSytem>();
	
	transformsystem = coordinator.RegisterSystem<TransformSystem>();
	camerasystem = coordinator.RegisterSystem<CameraSystem>();
	rendersystem = coordinator.RegisterSystem<RenderSystem>();
	cameracontrollersystem = coordinator.RegisterSystem<CameraControllerSystem>();
	gridcontrollersystem = coordinator.RegisterSystem<GridControllerSytem>();


	transformsystem->Setup();
	camerasystem->Setup();
	rendersystem->Setup();
	gridcontrollersystem->SetUp();

	cameracontrollersystem->Setup();

	Entity testunit = coordinator.CreateEntity();
	coordinator.AddComponent<Unit>(testunit, Unit("Test", 0, 0, 0, 0, 0, Unit::WALL, 500));
	coordinator.AddComponent<RenderData>(testunit, RenderData(renderer.getMesh(GEO_GRID), false));
	coordinator.AddComponent<Transform>(testunit, Transform());
	coordinator.GetComponent<Transform>(testunit).position = glm::vec3(10, 2, 10);
	coordinator.GetComponent<Transform>(testunit).scale = glm::vec3(30, 30, 30);
	coordinator.GetComponent<Transform>(testunit).type = TRANSFORM_TYPE::STATIC_TRANSFORM;
	Entity testunit2 = coordinator.CreateEntity();
	coordinator.AddComponent<Unit>(testunit2, Unit("Test2", 0, 0, 0, 0, 0, Unit::WALL, 500));
	coordinator.AddComponent<RenderData>(testunit2, RenderData(renderer.getMesh(GEO_GRID), false));
	coordinator.AddComponent<Transform>(testunit2, Transform());
	coordinator.GetComponent<Transform>(testunit2).position = glm::vec3(60, 2, 150);
	coordinator.GetComponent<Transform>(testunit2).scale = glm::vec3(30, 30, 30);
	coordinator.GetComponent<Transform>(testunit2).type = TRANSFORM_TYPE::STATIC_TRANSFORM;

	Entity maincamera = coordinator.CreateEntity();
	coordinator.AddComponent<Camera>(maincamera, Camera(
		glm::vec3(0, 50, -3.f),
		glm::vec3(90, 0, 0),
		800, 800,
		90.f, 
		CAMERA_TYPE::CAMERA_MAIN,
		CAMERA_MODE::MODE_PERSPECTIVE
	));
	coordinator.AddComponent<CameraController>(maincamera, CameraController());

	Entity axes = coordinator.CreateEntity();
	coordinator.AddComponent<RenderData>(axes, RenderData(renderer.getMesh(GEO_AXES), false));
	coordinator.AddComponent<Transform>(axes, Transform());
	Math::InitRNG();


	/*Init all systes*/

	//for (int i = 0; i < 400; i++)
	//{
	//	int x = Math::RandIntMinMax(-10, 10);
	//	int y = Math::RandIntMinMax(-10, 10);
	//	int z = Math::RandIntMinMax(-10, 10);

		Entity cube = coordinator.CreateEntity();
		coordinator.AddComponent<RenderData>(cube, RenderData(renderer.getMesh(GEO_CUBE), false));
		coordinator.AddComponent<Transform>(cube, Transform());
		coordinator.GetComponent<Transform>(cube).rotation = glm::vec3(0.f, 180.f, 0.f);
		coordinator.GetComponent<Transform>(cube).position = glm::vec3(0, 0, 0);
		coordinator.GetComponent<Transform>(cube).scale = glm::vec3(500, 1, 500);
		coordinator.GetComponent<Transform>(cube).type = TRANSFORM_TYPE::STATIC_TRANSFORM;
	//}
	camerasystem->Init();
	rendersystem->Init();
	transformsystem->Init();
}

void SceneTest::EarlyUpdate(double dt)
{

}

void SceneTest::Update(double dt)
{
	transformsystem->Update(dt);
	camerasystem->Update(dt);
	cameracontrollersystem->Update(dt);
	rendersystem->Update(dt);
	gridcontrollersystem->Update(dt);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void SceneTest::LateUpdate(double dt)
{
}

void SceneTest::PreRender()
{
}

void SceneTest::Render()
{
	rendersystem->Render();
	camerasystem->Render();
}

void SceneTest::PostRender()
{
}

void SceneTest::Exit()
{
	coordinator.Exit();
}
