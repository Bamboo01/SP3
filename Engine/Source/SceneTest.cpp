#include "SceneTest.h"
#include "Application.h"

void SceneTest::Init()
{
	coordinator.Init();
	coordinator.RegisterComponent<Camera>();
	coordinator.RegisterComponent<Transform>();
	coordinator.RegisterComponent<RenderData>();
	coordinator.RegisterComponent<CanvasImage>();
	coordinator.RegisterComponent<CanvasText>();
	coordinator.RegisterComponent<Unit>();
	coordinator.RegisterComponent<CameraController>();
	//coordinator.RegisterComponent<GridControllerSytem>();
	coordinator.RegisterComponent<EntityState>();
	
	transformsystem = coordinator.RegisterSystem<TransformSystem>();
	camerasystem = coordinator.RegisterSystem<CameraSystem>();
	rendersystem = coordinator.RegisterSystem<RenderSystem>();
	canvasimagesystem = coordinator.RegisterSystem<CanvasImageSystem>();
	canvastextsystem = coordinator.RegisterSystem<CanvasTextSystem>();
	cameracontrollersystem = coordinator.RegisterSystem<CameraControllerSystem>();
	entitystatesystem = coordinator.RegisterSystem<EntityStateSystem>();
	//gridcontrollersystem = coordinator.RegisterSystem<GridControllerSytem>();


	transformsystem->Setup();
	camerasystem->Setup();
	rendersystem->Setup();
	canvasimagesystem->Setup();
	canvastextsystem->Setup();
	entitystatesystem->Setup();
	//gridcontrollersystem->SetUp();
	cameracontrollersystem->Setup();

	Entity maincamera = coordinator.CreateEntity();
	coordinator.AddComponent<Camera>(maincamera, Camera(
		glm::vec3(0, 50, -3.f),
		glm::vec3(90, 0, 0),
		1080, 1080, //Lower this if the FPS stinks
		45.f,
		CAMERA_TYPE::CAMERA_MAIN,
		CAMERA_MODE::MODE_PERSPECTIVE
	));
	coordinator.AddComponent<CameraController>(maincamera, CameraController());
	coordinator.AddComponent<EntityState>(maincamera, EntityState());
	

	//Entity testunit = coordinator.CreateEntity();
	//coordinator.AddComponent<Unit>(testunit, Unit("Test", 0, 0, 0, 0, 0, Unit::WALL, 500));
	//coordinator.AddComponent<RenderData>(testunit, RenderData(renderer.getMesh(GEO_GRID), false));
	//coordinator.AddComponent<Transform>(testunit, Transform());
	//coordinator.GetComponent<Transform>(testunit).position = glm::vec3(10, 2, 10);
	//coordinator.GetComponent<Transform>(testunit).scale = glm::vec3(30, 30, 30);
	//coordinator.GetComponent<Transform>(testunit).type = TRANSFORM_TYPE::STATIC_TRANSFORM;
	//coordinator.AddComponent<EntityState>(testunit, EntityState());

	//Entity testunit2 = coordinator.CreateEntity();
	//coordinator.AddComponent<Unit>(testunit2, Unit("Test2", 0, 0, 0, 0, 0, Unit::WALL, 500));
	//coordinator.AddComponent<RenderData>(testunit2, RenderData(renderer.getMesh(GEO_GRID), false));
	//coordinator.AddComponent<Transform>(testunit2, Transform());
	//coordinator.GetComponent<Transform>(testunit2).position = glm::vec3(60, 2, 150);
	//coordinator.GetComponent<Transform>(testunit2).scale = glm::vec3(30, 30, 30);
	//coordinator.GetComponent<Transform>(testunit2).type = TRANSFORM_TYPE::STATIC_TRANSFORM;
	//coordinator.AddComponent<EntityState>(testunit2, EntityState());

	/*Entity maincamera = coordinator.CreateEntity();
	coordinator.AddComponent<Camera>(maincamera, Camera(
		glm::vec3(0, 50, -3.f),
		glm::vec3(90, 0, 0),
		800, 800,
		90.f, 
		CAMERA_TYPE::CAMERA_MAIN,
		CAMERA_MODE::MODE_PERSPECTIVE
	));*/
	

	Entity axes = coordinator.CreateEntity();
	coordinator.AddComponent<RenderData>(axes, RenderData(renderer.getMesh(GEO_AXES), false));
	coordinator.AddComponent<Transform>(axes, Transform());
	coordinator.GetComponent<Transform>(axes).type = TRANSFORM_TYPE::DYNAMIC_TRANSFORM;
	coordinator.AddComponent<EntityState>(axes, EntityState(false));

	Math::InitRNG();
	//for (int i = 0; i < 400; i++)
	//{
	//	int x = Math::RandIntMinMax(-20, 20);
	//	int y = Math::RandIntMinMax(-10, 5);
	//	int z = Math::RandIntMinMax(-20, 20);
	//	Entity cube = coordinator.CreateEntity();
	//	coordinator.AddComponent<RenderData>(cube, RenderData(renderer.getMesh(GEO_CUBE), false));
	//	coordinator.AddComponent<Transform>(cube, Transform());
	//	coordinator.GetComponent<Transform>(cube).rotation = glm::vec3(0.f, 180.f, 0.f);
	//	coordinator.GetComponent<Transform>(cube).position = glm::vec3(0, 0, 0);
	//	coordinator.GetComponent<Transform>(cube).scale = glm::vec3(500, 1, 500);
	//	coordinator.GetComponent<Transform>(cube).type = TRANSFORM_TYPE::STATIC_TRANSFORM;
	//}

	//Entity cube = coordinator.CreateEntity();
	//coordinator.AddComponent<Transform>(cube, Transform());
	//coordinator.GetComponent<Transform>(cube).position = glm::vec3(0, 0, 0);
	//coordinator.GetComponent<Transform>(cube).rotation  = glm::vec3(0.f, 180.f, 0.f);
	//coordinator.GetComponent<Transform>(cube).scale = glm::vec3(10, 10, 1);
	//coordinator.AddComponent<EntityState>(testunit, EntityState());

	//Entity UI = coordinator.CreateEntity();
	//coordinator.AddComponent<Transform>(UI, Transform());
	//coordinator.GetComponent<Transform>(UI).position = glm::vec3(0, 0, 0);
	//coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.5, 0.5, 1);
	//coordinator.AddComponent<CanvasImage>(UI, CanvasImage());
	//coordinator.GetComponent<Camera>(maincamera).assignTargetTexture(&coordinator.GetComponent<CanvasImage>(UI).TextureID);
	//coordinator.AddComponent<EntityState>(UI, EntityState());

	//Entity UIText = coordinator.CreateEntity();
	//coordinator.AddComponent<Transform>(UIText, Transform());
	//coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.1, 0.1, 1);
	//coordinator.AddComponent<CanvasText>(UIText, CanvasText("12345", ALIGN_CENTER)); 
	//coordinator.AddComponent<EntityState>(UIText, EntityState());

	/*Init all systems*/
	camerasystem->Init();
	rendersystem->Init();
	transformsystem->Init();
	canvasimagesystem->Init();
	canvastextsystem->Init();
	entitystatesystem->Init();
}

void SceneTest::EarlyUpdate(double dt)
{
	transformsystem->EarlyUpdate(dt);
	camerasystem->EarlyUpdate(dt);
	rendersystem->EarlyUpdate(dt);
	canvasimagesystem->EarlyUpdate(dt);
	canvastextsystem->EarlyUpdate(dt);
	entitystatesystem->EarlyUpdate(dt);
}

void SceneTest::Update(double dt)
{
	transformsystem->Update(dt);
	camerasystem->Update(dt);
	cameracontrollersystem->Update(dt);
	rendersystem->Update(dt);
	canvasimagesystem->Update(dt);
	canvastextsystem->Update(dt);
	entitystatesystem->Update(dt);
	//gridcontrollersystem->Update(dt);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void SceneTest::LateUpdate(double dt)
{
	transformsystem->LateUpdate(dt);
	camerasystem->LateUpdate(dt);
	rendersystem->LateUpdate(dt);
	canvasimagesystem->LateUpdate(dt);
	canvastextsystem->LateUpdate(dt);
}

void SceneTest::PreRender()
{
}

void SceneTest::Render()
{
	rendersystem->Render();
	camerasystem->Render();
	canvasimagesystem->Render();
	canvastextsystem->Render();
}

void SceneTest::PostRender()
{
}

void SceneTest::Exit()
{
	coordinator.Exit();
}
