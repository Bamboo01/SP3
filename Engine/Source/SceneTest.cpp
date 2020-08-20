#include "SceneTest.h"
#include "Application.h"

void SceneTest::Init()
{
	coordinator.Init();
	coordinator.RegisterComponent<Camera>();
	coordinator.RegisterComponent<Transform>();
	coordinator.RegisterComponent<RenderData>();
	coordinator.RegisterComponent<CanvasImage>();
	coordinator.RegisterComponent<Unit>();
	
	transformsystem = coordinator.RegisterSystem<TransformSystem>();
	camerasystem = coordinator.RegisterSystem<CameraSystem>();
	rendersystem = coordinator.RegisterSystem<RenderSystem>();
	canvasimagesystem = coordinator.RegisterSystem<CanvasImageSystem>();
	unitsystem = coordinator.RegisterSystem<UnitSystem>();

	transformsystem->Setup();
	camerasystem->Setup();
	rendersystem->Setup();
	canvasimagesystem->Setup();
	unitsystem->Setup();

	Entity maincamera = coordinator.CreateEntity();
	coordinator.AddComponent<Camera>(maincamera, Camera(
		glm::vec3(0, 0, -3.f),
		glm::vec3(0, 0, 0),
		1080, 1080, //Lower this if the FPS stinks
		45.f, 
		CAMERA_TYPE::CAMERA_MAIN,
		CAMERA_MODE::MODE_PERSPECTIVE
	));

	Entity axes = coordinator.CreateEntity();
	coordinator.AddComponent<RenderData>(axes, RenderData(renderer.getMesh(GEO_AXES), false));
	coordinator.AddComponent<Transform>(axes, Transform());

	Math::InitRNG();
	for (int i = 0; i < 400; i++)
	{
		int x = Math::RandIntMinMax(-20, 20);
		int y = Math::RandIntMinMax(-10, 5);
		int z = Math::RandIntMinMax(-20, 20);
		Entity cube = coordinator.CreateEntity();
		coordinator.AddComponent<RenderData>(cube, RenderData(renderer.getMesh(GEO_CUBE), false));
		coordinator.AddComponent<Transform>(cube, Transform());
		coordinator.GetComponent<Transform>(cube).rotation = glm::vec3(0.f, 180.f, 0.f);
		coordinator.GetComponent<Transform>(cube).position = glm::vec3(x, y, z);
		coordinator.GetComponent<Transform>(cube).type = TRANSFORM_TYPE::STATIC_TRANSFORM;
	}

	Entity cube = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(cube, Transform());
	coordinator.GetComponent<Transform>(cube).position = glm::vec3(0, 0, 0);
	coordinator.GetComponent<Transform>(cube).rotation = glm::vec3(0.f, 180.f, 0.f);
	coordinator.GetComponent<Transform>(cube).scale = glm::vec3(10, 10, 1);

	{
		// Test unit
		Entity unit;
		unit = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(unit, Transform());
		coordinator.GetComponent<Transform>(unit).position = glm::vec3(0, 0, 0);
		coordinator.GetComponent<Transform>(unit).rotation = glm::vec3(0.f, 180.f, 0.f);
		coordinator.GetComponent<Transform>(unit).scale = glm::vec3(10, 10, 1);
		coordinator.AddComponent<Unit>(unit, Unit("TestObject", 5, 100, 50, 30, 1.5f, Unit::NEXUS));
	}
	{
		// Minimap
		Entity UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.7, -0.7, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.3, 0.3, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//crate.tga", CanvasImage::NONCLICKABLE, CanvasImage::START2, CanvasImage::NONPOPUP, CanvasImage::START4, true));
	}
	{
		// Unit Info Box
		Entity UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(0.3, -0.75, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.7, 0.25, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//crate.tga", CanvasImage::NONCLICKABLE, CanvasImage::START2, CanvasImage::NONPOPUP, CanvasImage::START4, true));
	}
	{
		// Resource Box
		Entity UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(0, 0.9, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(1, 0.1, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//crate.tga", CanvasImage::NONCLICKABLE, CanvasImage::START2, CanvasImage::NONPOPUP, CanvasImage::START4, true));
	}
	for (int i = 0; i < 1; ++i)
	{
		// Nexus Clickable box
		Entity UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(0.5f, -0.9 + (i * 0.2), 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.15, 0.08, 1);
		if (i == 0)
			coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//grass.tga", CanvasImage::CLICKABLE, CanvasImage::NEXUSCREATEUNITBUTTON, CanvasImage::POPUP, CanvasImage::START4, false));
		//else if (i == 1)
		//	coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//grass.tga", CanvasImage::CLICKABLE, CanvasImage::NEXUSCREATEBUILDINGBUTTON, CanvasImage::POPUP, CanvasImage::START4, false));
	}

	/*Init all systems*/
	camerasystem->Init();
	rendersystem->Init();
	transformsystem->Init();
	canvasimagesystem->Init();
	unitsystem->Init();
	canvasimagesystem->SetUnitSystem(unitsystem);
}

void SceneTest::EarlyUpdate(double dt)
{
	transformsystem->EarlyUpdate(dt);
	camerasystem->EarlyUpdate(dt);
	rendersystem->EarlyUpdate(dt);
	canvasimagesystem->EarlyUpdate(dt);
}

void SceneTest::Update(double dt)
{
	transformsystem->Update(dt);
	camerasystem->Update(dt);
	rendersystem->Update(dt);
	canvasimagesystem->Update(dt);
}

void SceneTest::LateUpdate(double dt)
{
	transformsystem->LateUpdate(dt);
	camerasystem->LateUpdate(dt);
	rendersystem->LateUpdate(dt);
	canvasimagesystem->LateUpdate(dt);
}

void SceneTest::PreRender()
{
}

void SceneTest::Render()
{
	rendersystem->Render();
	camerasystem->Render();
	canvasimagesystem->Render();
}

void SceneTest::PostRender()
{
}

void SceneTest::Exit()
{
	coordinator.Exit();
}
