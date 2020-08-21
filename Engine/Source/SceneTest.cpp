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
	coordinator.RegisterComponent<RayCasting>();
	coordinator.RegisterComponent<Collider>();
	
	transformsystem = coordinator.RegisterSystem<TransformSystem>();
	camerasystem = coordinator.RegisterSystem<CameraSystem>();
	rendersystem = coordinator.RegisterSystem<RenderSystem>();
	canvasimagesystem = coordinator.RegisterSystem<CanvasImageSystem>();
	raycastingsystem = coordinator.RegisterSystem<RayCastingSystem>();
	collidersystem = coordinator.RegisterSystem<ColliderSystem>();
	unitsystem = coordinator.RegisterSystem<UnitSystem>();

	transformsystem->Setup();
	camerasystem->Setup();
	rendersystem->Setup();
	canvasimagesystem->Setup();
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
	//for (int i = 0; i < 400; i++)
	//{
	//	int x = Math::RandIntMinMax(-20, 20);
	//	int y = Math::RandIntMinMax(-10, 5);
	//	int z = Math::RandIntMinMax(-20, 20);
	//	Entity cube = coordinator.CreateEntity();
	//	coordinator.AddComponent<RenderData>(cube, RenderData(renderer.getMesh(GEO_CUBE), false));
	//	coordinator.AddComponent<Transform>(cube, Transform());
	//	coordinator.GetComponent<Transform>(cube).rotation = glm::vec3(0.f, 180.f, 0.f);
	//	coordinator.GetComponent<Transform>(cube).position = glm::vec3(x, y, z);
	//	coordinator.GetComponent<Transform>(cube).type = TRANSFORM_TYPE::STATIC_TRANSFORM;
	//}

	Entity cube = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(cube, Transform());
	coordinator.GetComponent<Transform>(cube).position = glm::vec3(0, 0, 0);
	coordinator.GetComponent<Transform>(cube).rotation = glm::vec3(0.f, 180.f, 0.f);
	coordinator.GetComponent<Transform>(cube).scale = glm::vec3(10, 10, 1);

	for (int i = 0; i < 1000; i++)
	{
		Entity myObject3;
		myObject3 = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(myObject3, Transform());
		coordinator.AddComponent<RenderData>(myObject3, RenderData());
		coordinator.AddComponent<Collider>(myObject3, Collider());
		coordinator.AddComponent<Unit>(myObject3, Unit());
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
	{
		// Generator Clickable box
		Entity UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(0.7f, -0.85, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.15, 0.08, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//grass.tga", CanvasImage::CLICKABLE, CanvasImage::GENERATORBUTTON, CanvasImage::POPUP, CanvasImage::START4, false));
	}
	{
		// Lab Clickable Box
		Entity UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(0.7f, -0.85, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.15, 0.08, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//grass.tga", CanvasImage::CLICKABLE, CanvasImage::LABBUTTON, CanvasImage::POPUP, CanvasImage::START4, false));
	}
	{
		// Lab PopUp unit box
		Entity UI;
		UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.5, 0.2, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.5, 0.6, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//crate.tga", CanvasImage::NONCLICKABLE, CanvasImage::START2, CanvasImage::POPUP, CanvasImage::LABUI, false));
	}
	for (int i = 0; i < 3; ++i)
	{
		// Lab Unit Pic
		Entity UI;
		UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.75 + (i * 0.25), 0.5, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.11, 0.11, 1);
		if (i == 0)
			coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//grass.tga", CanvasImage::CLICKABLE, CanvasImage::LABNORMALUNIT, CanvasImage::POPUP, CanvasImage::START4, false));
		else if (i == 1)
			coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//grass.tga", CanvasImage::CLICKABLE, CanvasImage::LABRANGEUNIT, CanvasImage::POPUP, CanvasImage::START4, false));
		else if (i == 2)
			coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//grass.tga", CanvasImage::CLICKABLE, CanvasImage::LABTANKUNIT, CanvasImage::POPUP, CanvasImage::START4, false));
	}
	for (int i = 0; i < 2; ++i)
	{
		// Nexus Clickable box
		Entity UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(0.7f, -0.85 + (i * 0.2), 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.15, 0.08, 1);
		if (i == 0)
			coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//grass.tga", CanvasImage::CLICKABLE, CanvasImage::NEXUSCREATEUNITBUTTON, CanvasImage::POPUP, CanvasImage::START4, false));
		else if (i == 1)
			coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//grass.tga", CanvasImage::CLICKABLE, CanvasImage::NEXUSCREATEBUILDINGBUTTON, CanvasImage::POPUP, CanvasImage::START4, false));
	}
	{
		// Nexus PopUp unit box
		Entity UI;
		UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.5, 0.2, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.5, 0.6, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//crate.tga", CanvasImage::NONCLICKABLE, CanvasImage::START2, CanvasImage::POPUP, CanvasImage::NEXUSUNITUI, false));
	}
	for (int i = 0; i < 3; ++i)
	{
		// Nexus Unit Pic
		Entity UI;
		UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.75 + (i * 0.25), 0.5, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.11, 0.11, 1);
		if (i == 0)
			coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//grass.tga", CanvasImage::CLICKABLE, CanvasImage::NEXUSNORMALUNIT, CanvasImage::POPUP, CanvasImage::START4, false));
		else if (i == 1)
			coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//grass.tga", CanvasImage::CLICKABLE, CanvasImage::NEXUSRANGEUNIT, CanvasImage::POPUP, CanvasImage::START4, false));
		else if (i == 2)
			coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//grass.tga", CanvasImage::CLICKABLE, CanvasImage::NEXUSTANKUNIT, CanvasImage::POPUP, CanvasImage::START4, false));
	}
	{
		// Nexus PopUp building box
		Entity UI;
		UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.5, 0.2, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.5, 0.6, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//crate.tga", CanvasImage::NONCLICKABLE, CanvasImage::START2, CanvasImage::POPUP, CanvasImage::NEXUSBUILDINGUI, false));
	}
	for (int i = 0; i < 2; ++i)
	{
		// Nexus Building Pic
		Entity UI;
		UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.75 + (i * 0.25), 0.5, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.11, 0.11, 1);
		if (i == 0)
			coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//grass.tga", CanvasImage::CLICKABLE, CanvasImage::NEXUSBUILDING, CanvasImage::POPUP, CanvasImage::START4, false));
		else if (i == 1)
			coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//grass.tga", CanvasImage::CLICKABLE, CanvasImage::NEXUSWALL, CanvasImage::POPUP, CanvasImage::START4, false));
	}

	/*Init all systems*/
	camerasystem->Init();
	rendersystem->Init();
	transformsystem->Init();
	canvasimagesystem->Init();
	unitsystem->Init();
	raycastingsystem->Init();
	collidersystem->Init();
	
	canvasimagesystem->SetUnitSystem(unitsystem);
	collidersystem->SetRayCastSystem(raycastingsystem);
}

void SceneTest::EarlyUpdate(double dt)
{
	transformsystem->EarlyUpdate(dt);
	camerasystem->EarlyUpdate(dt);
	rendersystem->EarlyUpdate(dt);
	canvasimagesystem->EarlyUpdate(dt);
	raycastingsystem->EarlyUpdate(dt);
	collidersystem->EarlyUpdate(dt);
	unitsystem->EarlyUpdate(dt);
}

void SceneTest::Update(double dt)
{
	transformsystem->Update(dt);
	camerasystem->Update(dt);
	rendersystem->Update(dt);
	canvasimagesystem->Update(dt);
	raycastingsystem->Update(dt);
	collidersystem->Update(dt);
	unitsystem->Update(dt);
}

void SceneTest::LateUpdate(double dt)
{
	transformsystem->LateUpdate(dt);
	camerasystem->LateUpdate(dt);
	rendersystem->LateUpdate(dt);
	canvasimagesystem->LateUpdate(dt);
	raycastingsystem->LateUpdate(dt);
	collidersystem->LateUpdate(dt);
	unitsystem->LateUpdate(dt);
}

void SceneTest::PreRender()
{
	// ImGui PreRender
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	// ImGui PreRender
}

void SceneTest::Render()
{
	rendersystem->Render();
	camerasystem->Render();
	canvasimagesystem->Render();
	UpdateImGui();
}

void SceneTest::PostRender()
{
	//ImGui PostRender (Make sure this is called before swapBuffers
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	//ImGui PostRender
}

void SceneTest::Exit()
{
	coordinator.Exit();
}

void SceneTest::UpdateImGui()
{
	UpdateImGuiUnitSpawn();
	UpdateImGuiEntityList();

	ImGui::Begin("Main");
	ImGui::Button("Hello!");
	ImGui::End();

}

void SceneTest::UpdateImGuiUnitSpawn()
{
	static float f = 0.0f;
	static const char* unittypes[]{ "NORMAL","TANK","RANGE","TOWER","WALL","NEXUS","GENERATOR","LAB","PROJECTILE" };
	static const char* unitfaction[]{ "PLAYER","ENEMY" };
	static int counter = 0;
	static int selectedItem = 0;
	static int selectedItem2 = 0;
	static float translation[] = { 0.f, 0.f, 0.f };
	static float rotation[] = { 0.f, 0.f, 0.f };
	static float scale[] = { 1.f, 1.f, 1.f };
	static int levelOfUnit = 1;
	static int numOfUnit = 0;

	ImGui::Begin("Debug");                          // Create a window called "Hello, world!" and append into it.

	ImGui::Combo("UnitType", &selectedItem, unittypes, IM_ARRAYSIZE(unittypes));
	ImGui::Combo("UnitFaction", &selectedItem2, unitfaction, IM_ARRAYSIZE(unitfaction));

	ImGui::SliderInt("UnitLevel", &levelOfUnit, 1, 50);
	ImGui::SliderInt("Number Of Units", &numOfUnit, 0, 100);

	if (ImGui::CollapsingHeader("Transformation"))
	{
		ImGui::SliderFloat("Translation X", &translation[0], -2000.0f, 2000.0f);
		ImGui::SliderFloat("Translation Y", &translation[1], -2000.0f, 2000.0f);
		ImGui::SliderFloat("Translation Z", &translation[2], -2000.0f, 2000.0f);

		ImGui::SliderFloat("Rotation X", &rotation[0], 0.f, 360.0f);
		ImGui::SliderFloat("Rotation Y", &rotation[1], 0.f, 360.0f);
		ImGui::SliderFloat("Rotation Z", &rotation[2], 0.f, 360.0f);

		ImGui::SliderFloat("Scale X", &scale[0], 0.f, 500.0f);
		ImGui::SliderFloat("Scale Y", &scale[1], 0.f, 500.0f);
		ImGui::SliderFloat("Scale Z", &scale[2], 0.f, 500.0f);
	}

	if (ImGui::Button("Spawn Unit"))             // Display some text (you can use a format strings too)
	{
		for (int i = 0; i < numOfUnit; i++)
		{
			unitsystem->CreateUnit((Unit::UnitType)(selectedItem + 1), (Unit::UnitFaction)(selectedItem2 + 1), levelOfUnit, Transform(glm::vec3(translation[0], translation[1], translation[2]), glm::vec3(scale[0], scale[1], scale[2]), glm::vec3(rotation[0], rotation[1], rotation[2]), TRANSFORM_TYPE::DYNAMIC_TRANSFORM));
		}
	}

	ImGui::SameLine();
	if (ImGui::Button("Spawn Unit (Random Pos)"))
	{
		for (int i = 0; i < numOfUnit; i++)
		{
			translation[0] = Math::RandFloatMinMax(-2000, 2000);
			translation[2] = Math::RandFloatMinMax(-2000, 2000);
			unitsystem->CreateUnit((Unit::UnitType)(selectedItem + 1), (Unit::UnitFaction)(selectedItem2 + 1), levelOfUnit, Transform(glm::vec3(translation[0], translation[1], translation[2]), glm::vec3(scale[0], scale[1], scale[2]), glm::vec3(rotation[0], rotation[1], rotation[2]), TRANSFORM_TYPE::DYNAMIC_TRANSFORM));
		}
	}

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

void SceneTest::UpdateImGuiEntityList()
{
	ImGui::Begin("EntityList");
	if (activeEntityList.empty())
		ImGui::Text("No active entities");
	else
	{
		static int selection = 0;
		ImGui::SliderInt(("activeEntities: " + std::to_string(activeEntityList.size())).c_str(), &selection, 0, activeEntityList.size() - 1);

		testHandler = activeEntityList[selection];
		auto& transform = coordinator.GetComponent<Transform>(testHandler);
		auto& collider = coordinator.GetComponent<Collider>(testHandler);
		auto& unit = coordinator.GetComponent<Unit>(testHandler);
		static const char* unittypes2[]{ "NORMAL","TANK","RANGE","TOWER","WALL","NEXUS","GENERATOR","LAB","PROJECTILE" };
		static const char* unitfaction2[]{ "PLAYER","ENEMY" };

		if (ImGui::CollapsingHeader("Unit Data"))
		{
			ImGui::Text("EntityID: %d", testHandler);
			ImGui::Text("UnitName: %s", unit.name.c_str());
			ImGui::Text("UnitType: %s", unittypes2[unit.unitType - 1]);
			ImGui::Text("UnitFaction: %s", unitfaction2[unit.unitFaction - 1]);
			ImGui::Text("Level: %d", unit.level);
			ImGui::SliderFloat("Health", &unit.health, 0.f, 1000.f);
			ImGui::SliderFloat("Damage", &unit.damage, 0.f, 2000.f);
			ImGui::SliderFloat("Defense", &unit.defense, 0.f, 2000.f);
			ImGui::SliderFloat("Attack Range", &unit.attackRange, -50.f, 50.f);
			ImGui::SliderFloat("Attack Speed", &unit.attackSpeed, -50.f, 50.f);

			if (ImGui::CollapsingHeader(("Targeted EntityID: " + std::to_string(unit.target)).c_str()))
			{
				if (unit.target != UINT_MAX)
				{
					auto& targetTransform = coordinator.GetComponent<Transform>(unit.target);
					auto& targetUnit = coordinator.GetComponent<Unit>(unit.target);
					ImGui::Text("[Target] EntityID: %d", targetUnit.target);
					ImGui::Text("[Target] UnitName: %s", targetUnit.name.c_str());
					ImGui::Text("[Target] UnitType: %d", targetUnit.unitType);
					ImGui::Text("[Target] Level: %d", targetUnit.level);
					ImGui::SliderFloat("[Target] Health", &targetUnit.health, 0.f, 1000.f);
					ImGui::SliderFloat("[Target] Damage", &targetUnit.damage, 0.f, 2000.f);
					ImGui::SliderFloat("[Target] Defense", &targetUnit.defense, 0.f, 2000.f);
					ImGui::SliderFloat("[Target] Attack Range", &targetUnit.attackRange, -50.f, 50.f);
					ImGui::SliderFloat("[Target] Attack Speed", &targetUnit.attackSpeed, -50.f, 50.f);
				}
			}
		}

		if (ImGui::CollapsingHeader("Transformation"))
		{
			ImGui::SliderFloat("Translation X", &transform.position.x, -2000.0f, 2000.0f);
			ImGui::SliderFloat("Translation Y", &transform.position.y, -2000.0f, 2000.0f);
			ImGui::SliderFloat("Translation Z", &transform.position.z, -2000.0f, 2000.0f);

			ImGui::SliderFloat("Rotation X", &transform.rotation.x, -2000.f, 2000.0f);
			ImGui::SliderFloat("Rotation Y", &transform.rotation.y, -2000.f, 2000.0f);
			ImGui::SliderFloat("Rotation Z", &transform.rotation.z, -2000.f, 2000.0f);

			ImGui::SliderFloat("Scale X", &transform.scale.x, -2000.f, 2000.0f);
			ImGui::SliderFloat("Scale Y", &transform.scale.y, -2000.f, 2000.0f);
			ImGui::SliderFloat("Scale Z", &transform.scale.z, -2000.f, 2000.0f);
		}

		if (ImGui::CollapsingHeader("Collider"))
		{
			ImGui::SliderFloat("Mass", &collider.mass, -1.f, 2000.0f);
			ImGui::SliderFloat("Collider Scale X", &collider.scale.x, -2000.0f, 2000.0f);
			ImGui::SliderFloat("Collider Scale Y", &collider.scale.y, -2000.0f, 2000.0f);
			ImGui::SliderFloat("Collider Scale Z", &collider.scale.z, -2000.0f, 2000.0f);
		}

		//if (ImGui::CollapsingHeader("Mesh"))
		//{
		//	ImGui::Text("MeshName: %s", render->name.c_str());
		//	ImGui::Text("DrawMode: %s", std::to_string(mesh->mode).c_str());
		//	ImGui::Text("TextureID: %u", std::to_string(mesh->mode).c_str());
		//}

		if (ImGui::Button("Set to inactive"))
		{
			unit.active = false;

			if (selection == activeEntityList.size() - 1 && selection != 0)
			{
				selection -= 1;
			}
		}

		ImGui::SameLine();

		if (ImGui::Button("Set all to inactive"))
		{
			for (int i = 0; i < activeEntityList.size(); i++)
			{
				auto& testunit = coordinator.GetComponent<Unit>(activeEntityList[i]);
				testunit.active = false;
				selection = 0;
			}
		}

	}

	ImGui::End();
}
