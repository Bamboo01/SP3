#include "SceneTest.h"
#include "Application.h"

void SceneTest::Init()
{
	coordinator.Init();
	coordinator.RegisterComponent<Camera>();
	coordinator.RegisterComponent<Transform>();
	coordinator.RegisterComponent<RenderData>();
	coordinator.RegisterComponent<CanvasImage>();
	coordinator.RegisterComponent<CanvasImageUpdate>();
	coordinator.RegisterComponent<Unit>();
	coordinator.RegisterComponent<RayCasting>();
	coordinator.RegisterComponent<Collider>();
	
	transformsystem = coordinator.RegisterSystem<TransformSystem>();
	camerasystem = coordinator.RegisterSystem<CameraSystem>();
	rendersystem = coordinator.RegisterSystem<RenderSystem>();
	canvasimagesystem = coordinator.RegisterSystem<CanvasImageSystem>();
	canvasimageupdatesystem = coordinator.RegisterSystem<CanvasImageUpdateSystem>();
	unitsystem = coordinator.RegisterSystem<UnitSystem>();
	raycastingsystem = coordinator.RegisterSystem<RayCastingSystem>();
	collidersystem = coordinator.RegisterSystem<ColliderSystem>();

	transformsystem->Setup();
	camerasystem->Setup();
	rendersystem->Setup();
	canvasimagesystem->Setup();
	canvasimageupdatesystem->Setup();
	unitsystem->Setup();
	raycastingsystem->Setup();
	collidersystem->Setup();

	Entity maincamera = coordinator.CreateEntity();
	coordinator.AddComponent<Camera>(maincamera, Camera(
		glm::vec3(0, 0, -3.f),
		glm::vec3(0, 0, 0),
		1080, 1080, //Lower this if the FPS stinks
		45.f, 
		CAMERA_TYPE::CAMERA_MAIN,
		CAMERA_MODE::MODE_PERSPECTIVE
	));
	coordinator.AddComponent<RayCasting>(maincamera, RayCasting());
	coordinator.AddComponent<Transform>(maincamera, Transform());

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
		coordinator.AddComponent<Unit>(unit, Unit("TestObject", 5, 100, 50, 30, 1.5f, Unit::LAB));
	}
	for (int i = 0; i < 5; ++i)
	{
		// Collider
		Entity collider = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(collider, Transform());
		coordinator.GetComponent<Transform>(collider).position = glm::vec3(10 + (i * 20), 0, 0);
		coordinator.GetComponent<Transform>(collider).rotation = glm::vec3(0.f, 0.f, 0.f);
		coordinator.GetComponent<Transform>(collider).scale = glm::vec3(10, 10, 10);
		coordinator.AddComponent<RenderData>(collider, RenderData(renderer.getMesh(GEO_CUBE), false));
		coordinator.AddComponent<Collider>(collider, Collider(glm::vec3(10, 10, 10), 1));
		coordinator.AddComponent<Unit>(collider, Unit("TestObject", 5, 100, 50, 30, 1.5f, Unit::LAB));
	}
	{
		// Minimap
		Entity UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.7, -0.7, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.3, 0.3, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//crate.tga"));
		coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::NONCLICKABLE, CanvasImageUpdate::START2, CanvasImageUpdate::NONPOPUP, CanvasImageUpdate::START4, true));
	}
	{
		// Unit Info Box
		Entity UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(0.3, -0.75, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.7, 0.25, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//crate.tga"));
		coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::NONCLICKABLE, CanvasImageUpdate::START2, CanvasImageUpdate::NONPOPUP, CanvasImageUpdate::START4, true));
	}
	{
		// Resource Box
		Entity UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(0, 0.9, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(1, 0.1, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//crate.tga"));
		coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::NONCLICKABLE, CanvasImageUpdate::START2, CanvasImageUpdate::NONPOPUP, CanvasImageUpdate::START4, true));
	}
	{
		// Generator Clickable box
		Entity UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(0.7f, -0.85, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.15, 0.08, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//grass.tga"));
		coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::GENERATORBUTTON, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4, false));
	}
	{
		// Lab Clickable Box
		Entity UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(0.7f, -0.85, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.15, 0.08, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//grass.tga"));
		coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::LABBUTTON, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4, false));
	}
	{
		// Lab PopUp unit box
		Entity UI;
		UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.5, 0.2, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.5, 0.6, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//crate.tga"));
		coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::NONCLICKABLE, CanvasImageUpdate::START2, CanvasImageUpdate::POPUP, CanvasImageUpdate::LABUI, false));
	}
	for (int i = 0; i < 3; ++i)
	{
		// Lab Unit Pic
		Entity UI;
		UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.75 + (i * 0.25), 0.5, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.11, 0.11, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//grass.tga"));
		if (i == 0)
			coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::LABNORMALUNIT, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4, false));
		else if (i == 1)
			coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::LABRANGEUNIT, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4, false));
		else if (i == 2)
			coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::LABTANKUNIT, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4, false));
	}
	for (int i = 0; i < 2; ++i)
	{
		// Nexus Clickable box
		Entity UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(0.7f, -0.85 + (i * 0.2), 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.15, 0.08, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//grass.tga"));
		if (i == 0)
			coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::NEXUSCREATEUNITBUTTON, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4, false));
		else if (i == 1)
			coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::NEXUSCREATEBUILDINGBUTTON, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4, false));
	}
	{
		// Nexus PopUp unit box
		Entity UI;
		UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.5, 0.2, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.5, 0.6, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//crate.tga"));
		coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::NONCLICKABLE, CanvasImageUpdate::START2, CanvasImageUpdate::POPUP, CanvasImageUpdate::NEXUSUNITUI, false));
	}
	for (int i = 0; i < 3; ++i)
	{
		// Nexus Unit Pic
		Entity UI;
		UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.75 + (i * 0.25), 0.5, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.11, 0.11, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//grass.tga"));
		if (i == 0)
			coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::NEXUSNORMALUNIT, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4, false));
		else if (i == 1)
			coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::NEXUSRANGEUNIT, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4, false));
		else if (i == 2)
			coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::NEXUSTANKUNIT, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4, false));
	}
	{
		// Nexus PopUp building box
		Entity UI;
		UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.5, 0.2, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.5, 0.6, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//crate.tga"));
		coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::NONCLICKABLE, CanvasImageUpdate::START2, CanvasImageUpdate::POPUP, CanvasImageUpdate::NEXUSBUILDINGUI, false));
	}
	for (int i = 0; i < 2; ++i)
	{
		// Nexus Building Pic
		Entity UI;
		UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.75 + (i * 0.25), 0.5, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.11, 0.11, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//grass.tga"));
		if (i == 0)
			coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::NEXUSBUILDING, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4, false));
		else if (i == 1)
			coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::NEXUSWALL, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4, false));
	}

	/*Init all systems*/
	camerasystem->Init();
	rendersystem->Init();
	transformsystem->Init();
	canvasimagesystem->Init();
	canvasimagesystem->Init();
	unitsystem->Init();
	raycastingsystem->Init();
	collidersystem->Init();
	
	canvasimageupdatesystem->SetUnitSystem(unitsystem);
	collidersystem->SetRayCastSystem(raycastingsystem);
}

void SceneTest::EarlyUpdate(double dt)
{
	transformsystem->EarlyUpdate(dt);
	camerasystem->EarlyUpdate(dt);
	rendersystem->EarlyUpdate(dt);
	canvasimagesystem->EarlyUpdate(dt);
	canvasimageupdatesystem->EarlyUpdate(dt);
	raycastingsystem->EarlyUpdate(dt);
	collidersystem->EarlyUpdate(dt);
}

void SceneTest::Update(double dt)
{
	transformsystem->Update(dt);
	camerasystem->Update(dt);
	rendersystem->Update(dt);
	canvasimagesystem->Update(dt);
	canvasimageupdatesystem->Update(dt);
	raycastingsystem->Update(dt);
	collidersystem->Update(dt);
}

void SceneTest::LateUpdate(double dt)
{
	transformsystem->LateUpdate(dt);
	camerasystem->LateUpdate(dt);
	rendersystem->LateUpdate(dt);
	canvasimagesystem->LateUpdate(dt);
	canvasimageupdatesystem->LateUpdate(dt);
	raycastingsystem->LateUpdate(dt);
	collidersystem->LateUpdate(dt);
}

void SceneTest::PreRender()
{
}

void SceneTest::Render()
{
	rendersystem->Render();
	camerasystem->Render();
	canvasimagesystem->Render();
	canvasimageupdatesystem->Render();
}

void SceneTest::PostRender()
{
}

void SceneTest::Exit()
{
	coordinator.Exit();
}
