#include "SceneCombat.h"
#include "Application.h"

void SceneCombat::Init()
{
	coordinator.Init();

	// Registering Component to coordinator
	coordinator.RegisterComponent<Camera>();
	coordinator.RegisterComponent<Transform>();
	coordinator.RegisterComponent<RenderData>();
	coordinator.RegisterComponent<CanvasImage>();
	coordinator.RegisterComponent<CanvasText>();
	coordinator.RegisterComponent<Unit>();
	coordinator.RegisterComponent<CameraController>();
	//coordinator.RegisterComponent<GridControllerSytem>();
	coordinator.RegisterComponent<EntityState>();
	coordinator.RegisterComponent<TerrainData>();
	coordinator.RegisterComponent<CanvasImageUpdate>();
	coordinator.RegisterComponent<RayCasting>();
	coordinator.RegisterComponent<Collider>();
	coordinator.RegisterComponent<GUIText>();
	coordinator.RegisterComponent<QuadTree>();
	coordinator.RegisterComponent<ObjectPoolSystem>();
	coordinator.RegisterComponent<ParticleSystemParameters>();
	coordinator.RegisterComponent<Controller>();
	coordinator.RegisterComponent<Pool>();
	coordinator.RegisterComponent<AIController>();
	coordinator.RegisterComponent<PauseMenu>();
	coordinator.RegisterComponent<WinLoseMenu>();

	// Registering System to coordinator
	transformsystem = coordinator.RegisterSystem<TransformSystem>();
	camerasystem = coordinator.RegisterSystem<CameraSystem>();
	rendersystem = coordinator.RegisterSystem<RenderSystem>();
	canvasimagesystem = coordinator.RegisterSystem<CanvasImageSystem>();
	canvastextsystem = coordinator.RegisterSystem<CanvasTextSystem>();
	cameracontrollersystem = coordinator.RegisterSystem<CameraControllerSystem>();
	entitystatesystem = coordinator.RegisterSystem<EntityStateSystem>();
	terrainsystem = coordinator.RegisterSystem<TerrainSystem>();
	objectpoolsystem = coordinator.RegisterSystem<ObjectPoolSystem>();
	gridcontrollersystem = coordinator.RegisterSystem<GridControllerSystem>();
	canvasimageupdatesystem = coordinator.RegisterSystem<CanvasImageUpdateSystem>();
	raycastingsystem = coordinator.RegisterSystem<RayCastingSystem>();
	collidersystem = coordinator.RegisterSystem<ColliderSystem>();
	unitsystem = coordinator.RegisterSystem<UnitSystem>();
	guitextsystem = coordinator.RegisterSystem<GUITextSystem>();
	particlesystem = coordinator.RegisterSystem<ParticleSystem>();
	controllersystem = coordinator.RegisterSystem<ControllerSystem>();
	quadtreesystem = coordinator.RegisterSystem<QuadTreeSystem>();
	aicontrollersystem = coordinator.RegisterSystem<AIControllerSystem>();
	pausemenusystem = coordinator.RegisterSystem<PauseMenuSystem>();
	winlosesystem = coordinator.RegisterSystem<WinLoseSystem>();

	transformsystem->Setup();
	camerasystem->Setup();
	rendersystem->Setup();
	canvasimagesystem->Setup();
	canvastextsystem->Setup();
	entitystatesystem->Setup();
	//gridcontrollersystem->SetUp();
	cameracontrollersystem->Setup();
	terrainsystem->Setup();
	canvasimageupdatesystem->Setup();
	unitsystem->Setup();
	raycastingsystem->Setup();
	collidersystem->Setup();
	guitextsystem->Setup();
	particlesystem->Setup();
	objectpoolsystem->Setup();
	controllersystem->Setup();
	quadtreesystem->Setup();
	aicontrollersystem->Setup();
	pausemenusystem->Setup();
	winlosesystem->Setup();

	InitMainCamera();
	InitTerrain();
	InitGUIText();
	InitPoolPrefab();
	InitCanvasGUI();
	InitMiniMap();
	InitController();
	InitPauseMenu();
	InitWinLose();

	// Initialising of all System
	camerasystem->Init();
	rendersystem->Init();
	transformsystem->Init();
	canvasimagesystem->Init();
	canvastextsystem->Init();
	entitystatesystem->Init();
	terrainsystem->Init();
	collidersystem->Init();
	raycastingsystem->Init(&collidersystem->m_Entities, &controllersystem->m_Entities, cameraHandler);
	controllersystem->Init(&collidersystem->m_Entities);
	canvasimageupdatesystem->Init(&controllersystem->m_Entities);
	guitextsystem->Init(&controllersystem->m_Entities);
	pausemenusystem->Init();
	winlosesystem->Init();
	
	raycastingsystem->SetTerrainEntities(terrainsystem->m_Entities);
	raycastingsystem->SetQuadTreeSystem(quadtreesystem);
	raycastingsystem->SetUnitSystem(unitsystem);
	raycastingsystem->SetColliderSystem(collidersystem);
	canvasimageupdatesystem->SetUnitSystem(unitsystem);
	particlesystem->Init();
	objectpoolsystem->Init();
	quadtreesystem->Init();
	aicontrollersystem->Init();
	unitsystem->Init(terrainsystem->m_Entities, aicontrollersystem->m_Entities, cameraHandler);

	collidersystem->SetUnitSystem(unitsystem);
	collidersystem->SetQuadTreeSystem(quadtreesystem);
	unitsystem->SetObjectPoolSystem(objectpoolsystem);
	unitsystem->SetQuadTreeSystem(quadtreesystem);
	aicontrollersystem->SetUnitSystem(unitsystem);
	InitUnit();

	gridcontrollersystem->Init();
	gridcontrollersystem->getUnitEntity(&unitsystem->m_Entities);

	cSoundController = CSoundController::GetInstance();
	cSoundController->PlaySoundByID(28);
}

void SceneCombat::EarlyUpdate(double dt)
{
	transformsystem->EarlyUpdate(dt);
	camerasystem->EarlyUpdate(dt);
	rendersystem->EarlyUpdate(dt);
	canvasimagesystem->EarlyUpdate(dt);
	canvastextsystem->EarlyUpdate(dt);
	entitystatesystem->EarlyUpdate(dt);
	canvasimageupdatesystem->EarlyUpdate(dt);
	raycastingsystem->EarlyUpdate(dt);
	collidersystem->EarlyUpdate(dt);
	unitsystem->EarlyUpdate(dt);
	guitextsystem->EarlyUpdate(dt);
	controllersystem->EarlyUpdate(dt);
	aicontrollersystem->EarlyUpdate(dt);
	pausemenusystem->EarlyUpdate(dt);
	winlosesystem->EarlyUpdate(dt);
}

void SceneCombat::Update(double dt)
{
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	rendersystem->Update(dt);
	transformsystem->Update(dt);
	camerasystem->Update(dt);
	cameracontrollersystem->Update(dt);

	canvasimagesystem->Update(dt);
	canvastextsystem->Update(dt);
	entitystatesystem->Update(dt);
	canvasimageupdatesystem->Update(dt);
	gridcontrollersystem->Update(dt);
	unitsystem->Update(dt);
	guitextsystem->Update(dt);
	controllersystem->Update(dt);

	canvasimageupdatesystem->SetSelectedUnitList(raycastingsystem->selectedunitlist);
	guitextsystem->SetSelectedUnitList(raycastingsystem->selectedunitlist);
	guitextsystem->SetUIopen(canvasimageupdatesystem->LabUIopen, canvasimageupdatesystem->UnitUIopen, canvasimageupdatesystem->BuildingUIopen);
	raycastingsystem->GetCursorInGUI(canvasimageupdatesystem->CursorinGUI);
	raycastingsystem->selectedbuilding = canvasimageupdatesystem->selectedbuilding;
	raycastingsystem->buildingclickdelay = canvasimageupdatesystem->buildingclickdelay;
	raycastingsystem->createonce = canvasimageupdatesystem->createonce;

	particlesystem->Update(dt);
	objectpoolsystem->Update(dt);
	quadtreesystem->SetUnitSystemEntities(unitsystem->m_Entities);
	quadtreesystem->Update(dt);
	raycastingsystem->Update(dt);
	collidersystem->Update(dt);
	aicontrollersystem->Update(dt);
	canvasimageupdatesystem->selectedbuilding = raycastingsystem->selectedbuilding;
	canvasimageupdatesystem->createonce = raycastingsystem->createonce;

	pausemenusystem->Update(dt);
	winlosesystem->NumOfUnitsBuilt = canvasimageupdatesystem->NumberofUnitCreated;
	winlosesystem->NumOfUnitsDestroyed = unitsystem->UnitsDeath;
	winlosesystem->WinLose = unitsystem->WinLose;
	winlosesystem->PlayerTotalUnit = unitsystem->PlayerTotalUnit;
	winlosesystem->Update(dt);
}

void SceneCombat::LateUpdate(double dt)
{
	transformsystem->LateUpdate(dt);
	camerasystem->LateUpdate(dt);
	rendersystem->LateUpdate(dt);
	canvasimagesystem->LateUpdate(dt);
	canvastextsystem->LateUpdate(dt);
	canvasimageupdatesystem->LateUpdate(dt);
	raycastingsystem->LateUpdate(dt);
	collidersystem->LateUpdate(dt);
	unitsystem->LateUpdate(dt);
	guitextsystem->LateUpdate(dt);
	controllersystem->LateUpdate(dt);
	aicontrollersystem->LateUpdate(dt);
	pausemenusystem->LateUpdate(dt);
	winlosesystem->LateUpdate(dt);
}

void SceneCombat::PreRender()
{
	// ImGui PreRender
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	//ImGui PreRender
}

void SceneCombat::Render()
{
	rendersystem->Render();
	particlesystem->Render();
	collidersystem->Render();
	camerasystem->Render();
	canvasimagesystem->Render();
	canvastextsystem->Render();
	canvasimageupdatesystem->Render();
	pausemenusystem->Render();
	winlosesystem->Render();
	/*UpdateImGui();*/
}

void SceneCombat::PostRender()
{
	//ImGui PostRender (Make sure this is called before swapBuffers
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	//ImGui PostRender
}

void SceneCombat::Exit()
{
	coordinator.Exit();
	CSoundController::GetInstance()->StopAllSounds();
}

void SceneCombat::InitGUIText()
{
	// Resources Text
	for (int i = 0; i < 2; ++i)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.0f + (i * 1.4), 1.25, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.01, 0.01, 1);
		if (i == 0)
		{
			coordinator.AddComponent<CanvasText>(UIText, CanvasText("Resources" + std::to_string(i + 1) + ": ", ALIGN_LEFT, glm::vec3(0.5, 0, 1)));
			coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::RESOURCES1));
		}
		else if (i == 1)
		{
			coordinator.AddComponent<CanvasText>(UIText, CanvasText("Resources" + std::to_string(i + 1) + ": ", ALIGN_LEFT, glm::vec3(0, 1, 0)));
			coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::RESOURCES2));
		}
		coordinator.AddComponent<EntityState>(UIText, EntityState());
	}
	// Unit Name Text
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-0.45f, -0.8, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.01, 0.01, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("Name: ", ALIGN_LEFT));
		coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::NAME));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
	}
	// Unit Level Text
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-0.45f, -0.9, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.01, 0.01, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("Level: ", ALIGN_LEFT));
		coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::LEVEL));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
	}
	// Unit Health Text
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-0.45f, -1.0, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.01, 0.01, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("HP: ", ALIGN_LEFT));
		coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::HEALTH));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
	}
	// Unit Damage Text
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-0.45f, -1.1, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.01, 0.01, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("ATK: ", ALIGN_LEFT));
		coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::DAMAGE));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
	}
	// Unit Defense Text
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-0.45f, -1.2, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.01, 0.01, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("DEF: ", ALIGN_LEFT));
		coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::DEFENSE));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
	}
	// Unit Attack Speed Text
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-0.45f, -1.3, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.01, 0.01, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("ATKSPD: ", ALIGN_LEFT));
		coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::ATKSPD));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
	}
	// Nexus Building Button Text
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(1.02f, -0.9, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.01, 0.01, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("Build", ALIGN_CENTER));
		coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::NEXUSBUTTON));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
	}
	// Nexus Unit Button Text
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(1.03f, -1.2, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.01, 0.01, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("Unit", ALIGN_CENTER));
		coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::NEXUSBUTTON));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
	}
	// Lab Level Button Text
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(1.f, -1.2, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.01, 0.01, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("Level Up", ALIGN_CENTER));
		coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::LABBUTTON));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
	}
	// Generator Collect Button Text
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(1.f, -1.2, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.01, 0.01, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("Collect", ALIGN_CENTER));
		coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::GENERATORBUTTON));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
	}
	// Generator resources Text
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(1.f, -0.8, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.01, 0.01, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("Generated:", ALIGN_CENTER));
		coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::GENERATORBUTTON));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
	}
	// Generator resources value Text
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(1.f, -0.9, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.01, 0.01, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("", ALIGN_CENTER));
		coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::GENERATEDRESOURCES));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
	}
	// Generator timer
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(1.f, -1.0, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.01, 0.01, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("Time: 10", ALIGN_CENTER));
		coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::GENERATORBUTTON));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
	}

	// Unit Button Text
	for (int i = 0; i < 3; ++i)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		if (i == 0)
		{
			coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.2f, 0.5, 0);
			coordinator.AddComponent<CanvasText>(UIText, CanvasText("Normal", ALIGN_LEFT));
		}
		else if (i == 1)
		{
			coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-0.8f, 0.5, 0);
			coordinator.AddComponent<CanvasText>(UIText, CanvasText("Range", ALIGN_LEFT));
		}
		else if (i == 2)
		{
			coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-0.4f, 0.5, 0);
			coordinator.AddComponent<CanvasText>(UIText, CanvasText("Tank", ALIGN_LEFT));
		}
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.01, 0.01, 1);
		coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::UNITBUTTON));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
	}
	// Unit Cost
	for (int i = 0; i < 3; ++i)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		if (i == 0)
		{
			coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.2f, 0.4, 0);
			coordinator.AddComponent<CanvasText>(UIText, CanvasText("", ALIGN_LEFT, glm::vec3(0.5, 0, 1)));
			coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::NORMALUNITCOST));
		}
		else if (i == 1)
		{
			coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-0.8f, 0.4, 0);
			coordinator.AddComponent<CanvasText>(UIText, CanvasText("", ALIGN_LEFT, glm::vec3(0.5, 0, 1)));
			coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::RANGEUNITCOST));
		}
		else if (i == 2)
		{
			coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-0.4f, 0.4, 0);
			coordinator.AddComponent<CanvasText>(UIText, CanvasText("", ALIGN_LEFT, glm::vec3(0.5, 0, 1)));
			coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::TANKUNITCOST));
		}
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.01, 0.01, 1);
		coordinator.AddComponent<EntityState>(UIText, EntityState());
	}
	// Unit Cost 2
	for (int i = 0; i < 3; ++i)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		if (i == 0)
		{
			coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.2f, 0.3, 0);
			coordinator.AddComponent<CanvasText>(UIText, CanvasText("", ALIGN_LEFT, glm::vec3(0, 1, 0)));
			coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::NORMALUNITCOST2));
		}
		else if (i == 1)
		{
			coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-0.8f, 0.3, 0);
			coordinator.AddComponent<CanvasText>(UIText, CanvasText("", ALIGN_LEFT, glm::vec3(0, 1, 0)));
			coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::RANGEUNITCOST2));
		}
		else if (i == 2)
		{
			coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-0.4f, 0.3, 0);
			coordinator.AddComponent<CanvasText>(UIText, CanvasText("", ALIGN_LEFT, glm::vec3(0, 1, 0)));
			coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::TANKUNITCOST2));
		}
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.01, 0.01, 1);
		coordinator.AddComponent<EntityState>(UIText, EntityState());
	}
	// Unit Level 
	for (int i = 0; i < 3; ++i)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		if (i == 0)
		{
			coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.2f, 0.2, 0);
			coordinator.AddComponent<CanvasText>(UIText, CanvasText("", ALIGN_LEFT));
			coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::NORMALUNITLEVEL));
		}
		else if (i == 1)
		{
			coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-0.8f, 0.2, 0);
			coordinator.AddComponent<CanvasText>(UIText, CanvasText("", ALIGN_LEFT));
			coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::RANGEUNITLEVEL));
		}
		else if (i == 2)
		{
			coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-0.4f, 0.2, 0);
			coordinator.AddComponent<CanvasText>(UIText, CanvasText("", ALIGN_LEFT));
			coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::TANKUNITLEVEL));
		}
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.01, 0.01, 1);
		coordinator.AddComponent<EntityState>(UIText, EntityState());
	}
	// Building Button Text
	for (int i = 0; i < 4; ++i)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		if (i == 0)
		{
			coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.15f, 0.5, 0);
			coordinator.AddComponent<CanvasText>(UIText, CanvasText("Tower", ALIGN_LEFT));
		}
		else if (i == 1)
		{
			coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-0.75f, 0.5, 0);
			coordinator.AddComponent<CanvasText>(UIText, CanvasText("Wall", ALIGN_LEFT));
		}
		else if (i == 2)
		{
			coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-0.4f, 0.5, 0);
			coordinator.AddComponent<CanvasText>(UIText, CanvasText("GEN1", ALIGN_LEFT));
		}
		else if (i == 3)
		{
			coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.12f, -0.21, 0);
			coordinator.AddComponent<CanvasText>(UIText, CanvasText("GEN2", ALIGN_LEFT));
		}
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.01, 0.01, 1);
		coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::BUILDINGBUTTON));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
	}
	// Building Cost Text
	for (int i = 0; i < 4; ++i)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		if (i == 0)
		{
			coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.15f, 0.4, 0);
			coordinator.AddComponent<CanvasText>(UIText, CanvasText("", ALIGN_LEFT, glm::vec3(0.5, 0, 1)));
			coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::TOWERCOST));
		}
		else if (i == 1)
		{
			coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-0.75f, 0.4, 0);
			coordinator.AddComponent<CanvasText>(UIText, CanvasText("", ALIGN_LEFT, glm::vec3(0.5, 0, 1)));
			coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::WALLCOST));
		}
		else if (i == 2)
		{
			coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-0.4f, 0.4, 0);
			coordinator.AddComponent<CanvasText>(UIText, CanvasText("", ALIGN_LEFT, glm::vec3(0.5, 0, 1)));
			coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::GENERATOR1COST));
		}
		else if (i == 3)
		{
			coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.12f, -0.31, 0);
			coordinator.AddComponent<CanvasText>(UIText, CanvasText("", ALIGN_LEFT, glm::vec3(0.5, 0, 1)));
			coordinator.AddComponent<GUIText>(UIText, GUIText(GUIText::GENERATOR2COST));
		}
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.01, 0.01, 1);
		coordinator.AddComponent<EntityState>(UIText, EntityState());
	}
}


void SceneCombat::InitCanvasGUI()
{
	{
		// Minimap
		Entity UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.7, -0.7, 0.9);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.3, 0.3, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//regulartexture.tga"));
		coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::NONCLICKABLE, CanvasImageUpdate::START2, CanvasImageUpdate::NONPOPUP, CanvasImageUpdate::START4));
		coordinator.AddComponent<EntityState>(UI, EntityState(true));
	}
	{
		// Unit Info Box
		Entity UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(0.3, -0.75, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.7, 0.25, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//regulartexture.tga"));
		coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::NONCLICKABLE, CanvasImageUpdate::START2, CanvasImageUpdate::NONPOPUP, CanvasImageUpdate::START4));
		coordinator.AddComponent<EntityState>(UI, EntityState(true));
	}
	{
		// Resource Box
		Entity UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(0, 0.9, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(1, 0.1, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//regulartexture.tga"));
		coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::NONCLICKABLE, CanvasImageUpdate::START2, CanvasImageUpdate::NONPOPUP, CanvasImageUpdate::START4));
		coordinator.AddComponent<EntityState>(UI, EntityState(true));
	}
	{
		// Generator1 Clickable box
		Entity UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(0.7f, -0.85, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.15, 0.08, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//crate.tga"));
		coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::GENERATOR1BUTTON, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4));
		coordinator.AddComponent<EntityState>(UI, EntityState(true));
	}
	{
		// Generator2 Clickable box
		Entity UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(0.7f, -0.85, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.15, 0.08, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//crate.tga"));
		coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::GENERATOR2BUTTON, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4));
		coordinator.AddComponent<EntityState>(UI, EntityState(true));
	}
	{
		// Lab Clickable Box
		Entity UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(0.7f, -0.85, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.15, 0.08, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//crate.tga"));
		coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::LABBUTTON, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4));
		coordinator.AddComponent<EntityState>(UI, EntityState(true));
	}
	{
		// Lab PopUp unit box
		Entity UI;
		UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.5, 0.2, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.5, 0.6, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//regulartexture.tga"));
		coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::NONCLICKABLE, CanvasImageUpdate::START2, CanvasImageUpdate::POPUP, CanvasImageUpdate::LABUI));
		coordinator.AddComponent<EntityState>(UI, EntityState(true));
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
		{
			coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//normal.tga"));
			coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::LABNORMALUNIT, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4));
		}
		else if (i == 1)
		{
			coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//range.tga"));
			coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::LABRANGEUNIT, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4));
		}
		else if (i == 2)
		{
			coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//tank.tga"));
			coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::LABTANKUNIT, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4));
		}
		coordinator.AddComponent<EntityState>(UI, EntityState(true));
	}
	for (int i = 0; i < 2; ++i)
	{
		// Nexus Clickable box
		Entity UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(0.7f, -0.85 + (i * 0.2), 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.15, 0.08, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//crate.tga"));
		if (i == 0)
			coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::NEXUSCREATEUNITBUTTON, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4));
		else if (i == 1)
			coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::NEXUSCREATEBUILDINGBUTTON, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4));
		coordinator.AddComponent<EntityState>(UI, EntityState(true));
	}
	{
		// Nexus PopUp unit box
		Entity UI;
		UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.5, 0.2, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.5, 0.6, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//regulartexture.tga"));
		coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::NONCLICKABLE, CanvasImageUpdate::START2, CanvasImageUpdate::POPUP, CanvasImageUpdate::NEXUSUNITUI));
		coordinator.AddComponent<EntityState>(UI, EntityState(true));
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
		{
			coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//normal.tga"));
			coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::NEXUSNORMALUNIT, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4));
		}
		else if (i == 1)
		{
			coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//range.tga"));
			coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::NEXUSRANGEUNIT, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4));
		}
		else if (i == 2)
		{
			coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//tank.tga"));
			coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::NEXUSTANKUNIT, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4));
		}
		coordinator.AddComponent<EntityState>(UI, EntityState(true));
	}
	{
		// Nexus PopUp building box
		Entity UI;
		UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.5, 0.2, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.5, 0.6, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//regulartexture.tga"));
		coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::NONCLICKABLE, CanvasImageUpdate::START2, CanvasImageUpdate::POPUP, CanvasImageUpdate::NEXUSBUILDINGUI));
		coordinator.AddComponent<EntityState>(UI, EntityState(true));
	}
	for (int i = 0; i < 4; ++i)
	{
		// Nexus Building Pic
		Entity UI;
		UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		if (i == 0)
		{
			coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.75, 0.5, 1);
			coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//tower.tga"));
			coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::NEXUSBUILDING, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4));
		}
		else if (i == 1)
		{
			coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.5, 0.5, 1);
			coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//wall.tga"));
			coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::NEXUSWALL, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4));
		}
		else if (i == 2)
		{
			coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.25, 0.5, 1);
			coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//generator1.tga"));
			coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::NEXUSGENERATOR1, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4));
		}
		else if (i == 3)
		{
			coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.75, 0, 1);
			coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//generator2.tga"));
			coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::CLICKABLE, CanvasImageUpdate::NEXUSGENERATOR2, CanvasImageUpdate::POPUP, CanvasImageUpdate::START4));
		}
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.11, 0.11, 1);
		coordinator.AddComponent<EntityState>(UI, EntityState(true));
	}
	for (int i = 0; i < 10; ++i)
	{
		// Unit pictures in the unit box
		Entity UI = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UI, Transform());
		if (i < 5)
			coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.1f + (i * 0.2), -0.65, 1);
		else if (5 <= i)
			coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.1f + ((i - 5) * 0.2), -0.85, 1);
		coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.08, 0.08, 1);
		coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//grass.tga"));
		coordinator.AddComponent<CanvasImageUpdate>(UI, CanvasImageUpdate(CanvasImageUpdate::NONCLICKABLE, CanvasImageUpdate::START2, CanvasImageUpdate::POPUP, CanvasImageUpdate::PICUI));
		coordinator.AddComponent<EntityState>(UI, EntityState(true));
	}
}

void SceneCombat::InitUnit()
{
	unitsystem->CreateUnit(Unit::UnitType::NEXUS, Unit::UnitFaction::PLAYER, 1, Transform(glm::vec3(160, 30, 160), glm::vec3(3, 3, 3), glm::vec3(0, -45, 0), TRANSFORM_TYPE::DYNAMIC_TRANSFORM));
	unitsystem->CreateUnit(Unit::UnitType::NEXUS, Unit::UnitFaction::ENEMY, 1, Transform(glm::vec3(-160, 30, -160), glm::vec3(3, 3, 3), glm::vec3(0, -45, 0), TRANSFORM_TYPE::DYNAMIC_TRANSFORM));
	unitsystem->CreateUnit(Unit::UnitType::LAB, Unit::UnitFaction::PLAYER, 1, Transform(glm::vec3(100, 30, 130), glm::vec3(2, 2, 2), glm::vec3(0, 0, 0), TRANSFORM_TYPE::DYNAMIC_TRANSFORM));
	unitsystem->CreateUnit(Unit::UnitType::LAB, Unit::UnitFaction::ENEMY, 1, Transform(glm::vec3(-100, 30, -130), glm::vec3(2, 2, 2), glm::vec3(0, 0, 0), TRANSFORM_TYPE::DYNAMIC_TRANSFORM));
	unitsystem->CreateUnit(Unit::UnitType::GENERATOR1, Unit::UnitFaction::PLAYER, 1, Transform(glm::vec3(100, 30, 100), glm::vec3(2, 2, 2), glm::vec3(0, 0, 0), TRANSFORM_TYPE::DYNAMIC_TRANSFORM));
	unitsystem->CreateUnit(Unit::UnitType::GENERATOR1, Unit::UnitFaction::ENEMY, 1, Transform(glm::vec3(-100, 30, -100), glm::vec3(2, 2, 2), glm::vec3(0, 0, 0), TRANSFORM_TYPE::DYNAMIC_TRANSFORM));
}

void SceneCombat::InitPoolPrefab()
{
	Entity unitPoolPrefab = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(unitPoolPrefab, Transform());
	coordinator.AddComponent<Collider>(unitPoolPrefab, Collider());
	coordinator.AddComponent<RenderData>(unitPoolPrefab, RenderData());
	coordinator.AddComponent<Unit>(unitPoolPrefab, Unit());
	coordinator.AddComponent<EntityState>(unitPoolPrefab, EntityState(false));
	coordinator.AddComponent<ParticleSystemParameters>(unitPoolPrefab,
		ParticleSystemParameters(
			renderer.getMesh(GEO_CODEPARTICLE), 1, 10, 1,
			glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
			glm::vec3(-1, 15, -1), glm::vec3(1, 15, 1),
			glm::vec3(10.f, 10.f, 1.f), glm::vec3(10.f, 10.f, 1.f),
			glm::vec3(0.f), glm::vec3(0.f),
			glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f), false, 10.f
		));

	objectpoolsystem->AddToPool(Pool(Tag::UNIT, unitPoolPrefab, 1500));
}

void SceneCombat::InitMainCamera()
{
	Entity maincamera = coordinator.CreateEntity();
	coordinator.AddComponent<Camera>(maincamera, Camera(
		glm::vec3(0, 100, -3.f),
		glm::vec3(15, 0, 0),
		1080, 1080, //Lower this if the FPS stinks
		45.f,
		CAMERA_TYPE::CAMERA_MAIN,
		CAMERA_MODE::MODE_PERSPECTIVE
	));
	coordinator.AddComponent<CameraController>(maincamera, CameraController());
	coordinator.AddComponent<RayCasting>(maincamera, RayCasting());
	coordinator.AddComponent<EntityState>(maincamera, EntityState());
	cameraHandler = maincamera;

	gridcontrollersystem->getRaycastingEntity(maincamera);

	{
		Entity particle = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(particle, Transform(glm::vec3(160, 30, 160), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), DYNAMIC_TRANSFORM));
		coordinator.AddComponent<EntityState>(particle, EntityState());
		coordinator.AddComponent<ParticleSystemParameters>(particle,
			ParticleSystemParameters(
				renderer.getMesh(GEO_CODEPARTICLE), 5, 50, 1,
				glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
				glm::vec3(-1, 15, -1), glm::vec3(1, 15, 1),
				glm::vec3(10.f, 10.f, 1.f), glm::vec3(10.f, 10.f, 1.f),
				glm::vec3(0.f), glm::vec3(0.f),
				glm::vec3(0.f), glm::vec3(0.f)));
	}
	{
		Entity particle = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(particle, Transform(glm::vec3(-160, 30, -160), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), DYNAMIC_TRANSFORM));
		coordinator.AddComponent<EntityState>(particle, EntityState());
		coordinator.AddComponent<ParticleSystemParameters>(particle,
			ParticleSystemParameters(
				renderer.getMesh(GEO_CODEPARTICLE), 5, 50, 1,
				glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f),
				glm::vec3(-1, 15, -1), glm::vec3(1, 15, 1),
				glm::vec3(10.f, 10.f, 1.f), glm::vec3(10.f, 10.f, 1.f),
				glm::vec3(0.f), glm::vec3(0.f),
				glm::vec3(0.f), glm::vec3(0.f)));
	}
}

void SceneCombat::InitTerrain()
{
	Entity terrain = coordinator.CreateEntity();
	coordinator.AddComponent<RenderData>(terrain, RenderData(renderer.getMesh(GEO_TERRAIN), false));
	coordinator.AddComponent<Transform>(terrain, Transform());
	coordinator.GetComponent<Transform>(terrain).type = TRANSFORM_TYPE::DYNAMIC_TRANSFORM;
	coordinator.GetComponent<Transform>(terrain).scale = glm::vec3(400, 35, 400);
	coordinator.AddComponent<TerrainData>(terrain, TerrainData(GEO_TERRAIN));
	coordinator.AddComponent<EntityState>(terrain, EntityState());
}

void SceneCombat::InitController()
{
	Entity controller = coordinator.CreateEntity();
	coordinator.AddComponent<Controller>(controller, Controller(Controller::PLAYER, glm::vec3(160, 30, 160)));
	coordinator.AddComponent<EntityState>(controller, EntityState());

	Entity enemycontroller = coordinator.CreateEntity();
	coordinator.AddComponent<AIController>(enemycontroller, AIController(gridcontrollersystem, Controller::ENEMY, glm::vec3(-160, 30, -160), glm::vec3(160, 30, 160)));
	coordinator.AddComponent<EntityState>(enemycontroller, EntityState());
}

void SceneCombat::InitMiniMap()
{
	// MINIMAP
	Entity MiniMap = coordinator.CreateEntity();
	coordinator.AddComponent<Camera>(MiniMap, Camera(
		glm::vec3(0, 400, 0.f),
		glm::vec3(60, 0, 0),
		1080, 1080, //Lower this if the FPS stinks
		45.f,
		CAMERA_TYPE::CAMERA_MINIMAP,
		CAMERA_MODE::MODE_PERSPECTIVE
	));
	coordinator.AddComponent<CameraController>(MiniMap, CameraController());
	coordinator.AddComponent<EntityState>(MiniMap, EntityState());

	Entity UI = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(UI, Transform());
	coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.7, -0.7, 0);
	coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.28, 0.28, 1);
	coordinator.AddComponent<CanvasImage>(UI, CanvasImage());
	coordinator.GetComponent<Camera>(MiniMap).assignTargetTexture(&coordinator.GetComponent<CanvasImage>(UI).TextureID);
	coordinator.AddComponent<EntityState>(UI, EntityState());
}

void SceneCombat::InitPauseMenu()
{
	Entity GUI_Resume = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_Resume, Transform());
	coordinator.AddComponent<EntityState>(GUI_Resume, EntityState(false));
	coordinator.AddComponent<CanvasText>(GUI_Resume, CanvasText("Resume", ALIGN_CENTER));
	coordinator.GetComponent<Transform>(GUI_Resume).position.y = 0.3;
	coordinator.AddComponent<PauseMenu>(GUI_Resume, PauseMenu(PauseMenu::RESUME_BUTTON));

	Entity GUI_Options = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_Options, Transform());
	coordinator.AddComponent<EntityState>(GUI_Options, EntityState(false));
	coordinator.AddComponent<CanvasText>(GUI_Options, CanvasText("Options", ALIGN_CENTER));
	coordinator.GetComponent<Transform>(GUI_Options).position.y = 0;
	coordinator.AddComponent<PauseMenu>(GUI_Options, PauseMenu(PauseMenu::OPTION_BUTTON));

	Entity GUI_Exit = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_Exit, Transform());
	coordinator.AddComponent<EntityState>(GUI_Exit, EntityState(false));
	coordinator.AddComponent<CanvasText>(GUI_Exit, CanvasText("Exit", ALIGN_CENTER));
	coordinator.GetComponent<Transform>(GUI_Exit).position.y = -0.2;
	coordinator.AddComponent<PauseMenu>(GUI_Exit, PauseMenu(PauseMenu::EXIT_BUTTON));

	Entity GUI_VolumeUp = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_VolumeUp, Transform());
	coordinator.AddComponent<EntityState>(GUI_VolumeUp, EntityState(false));
	coordinator.AddComponent<CanvasText>(GUI_VolumeUp, CanvasText("VolumeUp", ALIGN_CENTER));
	coordinator.GetComponent<Transform>(GUI_VolumeUp).position.y = 0.3;
	coordinator.AddComponent<PauseMenu>(GUI_VolumeUp, PauseMenu(PauseMenu::AUDIO_INCREASE_BUTTON));

	Entity GUI_VolumeDown = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_VolumeDown, Transform());
	coordinator.AddComponent<EntityState>(GUI_VolumeDown, EntityState(false));
	coordinator.AddComponent<CanvasText>(GUI_VolumeDown, CanvasText("VolumeDown", ALIGN_CENTER));
	coordinator.GetComponent<Transform>(GUI_VolumeDown).position.y = 0.1;
	coordinator.AddComponent<PauseMenu>(GUI_VolumeDown, PauseMenu(PauseMenu::AUDIO_DECREASE_BUTTON));

	Entity GUI_BackToPauseMenu = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_BackToPauseMenu, Transform());
	coordinator.AddComponent<EntityState>(GUI_BackToPauseMenu, EntityState(false));
	coordinator.AddComponent<CanvasText>(GUI_BackToPauseMenu, CanvasText("Back"));
	coordinator.GetComponent<Transform>(GUI_BackToPauseMenu).position.y = -0.5;
	coordinator.AddComponent<PauseMenu>(GUI_BackToPauseMenu, PauseMenu(PauseMenu::BACK_BUTTON));

	Entity GUI_VolumeMeter = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_VolumeMeter, Transform());
	coordinator.AddComponent<EntityState>(GUI_VolumeMeter, EntityState(false));
	coordinator.AddComponent<CanvasText>(GUI_VolumeMeter, CanvasText("Volume: ", ALIGN_CENTER));
	coordinator.GetComponent<Transform>(GUI_VolumeMeter).position.y = 0.5;
	coordinator.AddComponent<PauseMenu>(GUI_VolumeMeter, PauseMenu());

	Entity PauseCanvas = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(PauseCanvas, Transform());
	coordinator.GetComponent<Transform>(PauseCanvas).position = glm::vec3(0, 0, 0);
	coordinator.GetComponent<Transform>(PauseCanvas).scale = glm::vec3(0.5, 0.5, 1);
	coordinator.AddComponent<EntityState>(PauseCanvas, EntityState(false));
	coordinator.AddComponent<CanvasImage>(PauseCanvas, CanvasImage("Images//regulartexture.tga"));
	coordinator.AddComponent<PauseMenu>(PauseCanvas, PauseMenu(PauseMenu::CANVAS));

	pausemenusystem->GUI_BackToPauseMenu = GUI_BackToPauseMenu;
	pausemenusystem->GUI_Exit = GUI_Exit;
	pausemenusystem->GUI_Options = GUI_Options;
	pausemenusystem->GUI_Resume = GUI_Resume;
	pausemenusystem->GUI_VolumeDown = GUI_VolumeDown;
	pausemenusystem->GUI_VolumeUp = GUI_VolumeUp;
	pausemenusystem->GUI_VolumeMeter = GUI_VolumeMeter;
	pausemenusystem->PauseCanvas = PauseCanvas;
}

void SceneCombat::InitWinLose()
{
	Entity GUI_Exit = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_Exit, Transform());
	coordinator.AddComponent<EntityState>(GUI_Exit, EntityState(false));
	coordinator.AddComponent<CanvasText>(GUI_Exit, CanvasText("Exit", ALIGN_CENTER));
	coordinator.GetComponent<Transform>(GUI_Exit).position.y = -0.5;
	coordinator.AddComponent<WinLoseMenu>(GUI_Exit, WinLoseMenu(WinLoseMenu::EXIT_BUTTON));

	Entity GUI_Text = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_Text, Transform());
	coordinator.AddComponent<EntityState>(GUI_Text, EntityState(false));
	coordinator.AddComponent<CanvasText>(GUI_Text, CanvasText("", ALIGN_CENTER));
	coordinator.GetComponent<Transform>(GUI_Text).position.y = 0.4;
	coordinator.AddComponent<WinLoseMenu>(GUI_Text, WinLoseMenu(WinLoseMenu::NO_BUTTON));

	Entity GUI_UnitsBuilt = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_UnitsBuilt, Transform());
	coordinator.AddComponent<EntityState>(GUI_UnitsBuilt, EntityState());
	coordinator.AddComponent<CanvasText>(GUI_UnitsBuilt, CanvasText("Units Built: ", ALIGN_CENTER));
	coordinator.GetComponent<Transform>(GUI_UnitsBuilt).position.y = 0.1;
	coordinator.AddComponent<WinLoseMenu>(GUI_UnitsBuilt, WinLoseMenu(WinLoseMenu::NO_BUTTON));

	Entity GUI_UnitsDestroyed = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_UnitsDestroyed, Transform());
	coordinator.AddComponent<EntityState>(GUI_UnitsDestroyed, EntityState(false));
	coordinator.AddComponent<CanvasText>(GUI_UnitsDestroyed, CanvasText("Death Count: ", ALIGN_CENTER));
	coordinator.GetComponent<Transform>(GUI_UnitsDestroyed).position.y = -0.05;
	coordinator.AddComponent<WinLoseMenu>(GUI_UnitsDestroyed, WinLoseMenu(WinLoseMenu::NO_BUTTON));

	Entity GUI_UnitsLeft = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(GUI_UnitsLeft, Transform());
	coordinator.AddComponent<EntityState>(GUI_UnitsLeft, EntityState(false));
	coordinator.AddComponent<CanvasText>(GUI_UnitsLeft, CanvasText("Alive Count: ", ALIGN_CENTER));
	coordinator.GetComponent<Transform>(GUI_UnitsLeft).position.y = -0.2;
	coordinator.AddComponent<WinLoseMenu>(GUI_UnitsLeft, WinLoseMenu());

	Entity WinLoseCanvas = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(WinLoseCanvas, Transform());
	coordinator.GetComponent<Transform>(WinLoseCanvas).position = glm::vec3(0, 0, 0);
	coordinator.GetComponent<Transform>(WinLoseCanvas).scale = glm::vec3(0.5, 0.5, 1);
	coordinator.AddComponent<EntityState>(WinLoseCanvas, EntityState(false));
	coordinator.AddComponent<CanvasImage>(WinLoseCanvas, CanvasImage("Images//regulartexture.tga"));
	coordinator.AddComponent<WinLoseMenu>(WinLoseCanvas, WinLoseMenu(WinLoseMenu::CANVAS));

	winlosesystem->GUI_Text = GUI_Text;
	winlosesystem->GUI_Exit = GUI_Exit;
	winlosesystem->GUI_UnitsBuilt = GUI_UnitsBuilt;
	winlosesystem->GUI_UnitsDestroyed = GUI_UnitsDestroyed;
	winlosesystem->GUI_UnitsLeft = GUI_UnitsLeft;
	winlosesystem->WinLoseCanvas = WinLoseCanvas;
}

//void SceneCombat::UpdateImGui()
//{
//	static bool unitSpawner = false;
//	static bool entityList = false;
//	static bool raycastInfo = false;
//
//	if (unitSpawner)
//	{
//		UpdateImGuiUnitSpawn();
//	}
//
//	if (entityList)
//	{
//		UpdateImGuiEntityList();
//	}
//
//	if (raycastInfo)
//	{
//		UpdateImGuiRaycast();
//	}
//
//	ImGui::Begin("Main");
//
//	ImGui::Checkbox(" Unit Spawn Menu", &unitSpawner);
//	ImGui::Checkbox(" Entity List", &entityList);
//	ImGui::Checkbox(" Raycast Info", &raycastInfo);
//
//	if (ImGui::Button("Print Quad Tree"))
//	{
//		quadtreesystem->PrintTree(quadtreesystem->root);
//	}
//
//	ImGui::End();
//}
//
//void SceneCombat::UpdateImGuiRaycast()
//{
//	ImGui::Begin("Cursor");
//	ImGui::Text("X: %f", raycastingsystem->cursorOnHeightMapPosition.x);
//	ImGui::SameLine();
//	ImGui::Text("Y: %f", raycastingsystem->cursorOnHeightMapPosition.y);
//	ImGui::End();
//}
//
//void SceneCombat::UpdateImGuiUnitSpawn()
//{
//	static float f = 0.0f;
//	static const char* unitTypes[]{ "NORMAL","TANK","RANGE","TOWER","WALL","NEXUS","GENERATOR","LAB","PROJECTILE" };
//	static const char* unitfaction[]{ "PLAYER","ENEMY" };
//	static int counter = 0;
//	static int selectedItem = 0;
//	static int selectedItem2 = 0;
//	static float translation[] = { 0.f, 0.f, 0.f };
//	static float rotation[] = { 0.f, 0.f, 0.f };
//	static float scale[] = { 1.f, 1.f, 1.f };
//	static int levelOfUnit = 1;
//	static int numOfUnit = 0;
//
//	ImGui::Begin("Debug");                          // Create a window called "Hello, world!" and append into it.
//
//	ImGui::Combo("UnitType", &selectedItem, unitTypes, IM_ARRAYSIZE(unitTypes));
//	ImGui::Combo("UnitFaction", &selectedItem2, unitfaction, IM_ARRAYSIZE(unitfaction));
//
//	ImGui::SliderInt("UnitLevel", &levelOfUnit, 1, 50);
//	ImGui::SliderInt("Number Of Units", &numOfUnit, 0, 100);
//
//	if (ImGui::CollapsingHeader("Transformation"))
//	{
//		ImGui::SliderFloat("Translation X", &translation[0], -2000.0f, 2000.0f);
//		ImGui::SliderFloat("Translation Y", &translation[1], -2000.0f, 2000.0f);
//		ImGui::SliderFloat("Translation Z", &translation[2], -2000.0f, 2000.0f);
//
//		ImGui::SliderFloat("Rotation X", &rotation[0], 0.f, 360.0f);
//		ImGui::SliderFloat("Rotation Y", &rotation[1], 0.f, 360.0f);
//		ImGui::SliderFloat("Rotation Z", &rotation[2], 0.f, 360.0f);
//
//		ImGui::SliderFloat("Scale X", &scale[0], 0.f, 500.0f);
//		ImGui::SliderFloat("Scale Y", &scale[1], 0.f, 500.0f);
//		ImGui::SliderFloat("Scale Z", &scale[2], 0.f, 500.0f);
//	}
//
//	if (ImGui::Button("Spawn Unit"))             // Display some text (you can use a format strings too)
//	{
//		for (int i = 0; i < numOfUnit; i++)
//		{
//			Entity newUnit = unitsystem->CreateUnit((Unit::UnitType)(selectedItem + 1), (Unit::UnitFaction)(selectedItem2 + 1), levelOfUnit, Transform(glm::vec3(translation[0], translation[1], translation[2]), glm::vec3(scale[0], scale[1], scale[2]), glm::vec3(rotation[0], rotation[1], rotation[2]), TRANSFORM_TYPE::DYNAMIC_TRANSFORM));
//			activeEntityList.push_back(newUnit);
//		}
//	}
//
//	ImGui::SameLine();
//	if (ImGui::Button("Spawn Unit (Random Pos)"))
//	{
//		for (int i = 0; i < numOfUnit; i++)
//		{
//			translation[0] = Math::RandFloatMinMax(-200, 200);
//			translation[2] = Math::RandFloatMinMax(-200, 200);
//			Entity newUnit = unitsystem->CreateUnit((Unit::UnitType)(selectedItem + 1), (Unit::UnitFaction)(selectedItem2 + 1), levelOfUnit, Transform(glm::vec3(translation[0], translation[1], translation[2]), glm::vec3(scale[0], scale[1], scale[2]), glm::vec3(rotation[0], rotation[1], rotation[2]), TRANSFORM_TYPE::DYNAMIC_TRANSFORM));
//			activeEntityList.push_back(newUnit);
//		}
//	}
//
//	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//	ImGui::End();
//}
//
//void SceneCombat::UpdateImGuiEntityList()
//{
//	activeEntityList.clear();
//	ImGui::Begin("EntityList");
//	if (activeEntityList.empty())
//	{
//		std::set<Entity> entitySetTest = unitsystem->m_Entities;
//		if (entitySetTest.empty())
//		{
//			ImGui::Text("No active entities");
//		}
//		else
//		{
//			for (auto const& entity : entitySetTest)
//			{
//				activeEntityList.push_back(entity);
//			}
//		}
//	}
//
//	if (!activeEntityList.empty())
//	{
//		static int selection = 0;
//		ImGui::SliderInt(("activeEntities: " + std::to_string(activeEntityList.size())).c_str(), &selection, 0, activeEntityList.size() - 1);
//
//		if (selection >= activeEntityList.size())
//		{
//			selection = activeEntityList.size() - 1;
//		}
//
//		testHandler = activeEntityList[selection];
//		auto& transform = coordinator.GetComponent<Transform>(testHandler);
//		auto& collider = coordinator.GetComponent<Collider>(testHandler);
//		auto& unit = coordinator.GetComponent<Unit>(testHandler);
//		static const char* unitTypes2[]{ "NORMAL","TANK","RANGE","TOWER","WALL","NEXUS","GENERATOR1","GENERATOR2","LAB","PROJECTILE","MELEE_PROJECTILE"};
//		static const char* unitfaction2[]{ "PLAYER","ENEMY" };
//
//		if (ImGui::CollapsingHeader("Unit Data"))
//		{
//			ImGui::Text("EntityID: %d", testHandler);
//			ImGui::Text("UnitName: %s", unit.name.c_str());
//			ImGui::Text("UnitType: %s", unitTypes2[unit.unitType - 1]);
//			ImGui::Text("UnitFaction: %s", unitfaction2[unit.unitFaction - 1]);
//			ImGui::Text("Level: %d", unit.level);
//			ImGui::SliderFloat("Health", &unit.health, 0.f, 1000.f);
//			ImGui::SliderFloat("Damage", &unit.damage, 0.f, 2000.f);
//			ImGui::SliderFloat("Defense", &unit.defense, 0.f, 2000.f);
//			ImGui::SliderFloat("Attack Range", &unit.attackRange, -50.f, 50.f);
//			ImGui::SliderFloat("Attack Speed", &unit.attackSpeed, -50.f, 50.f);
//
//			if (ImGui::CollapsingHeader(("Targeted EntityID: " + std::to_string(unit.target)).c_str()))
//			{
//				if (unit.target != UINT_MAX)
//				{
//					auto& targetTransform = coordinator.GetComponent<Transform>(unit.target);
//					auto& targetUnit = coordinator.GetComponent<Unit>(unit.target);
//					ImGui::Text("[Target] EntityID: %d", targetUnit.target);
//					ImGui::Text("[Target] UnitName: %s", targetUnit.name.c_str());
//					ImGui::Text("[Target] UnitType: %d", targetUnit.unitType);
//					ImGui::Text("[Target] Level: %d", targetUnit.level);
//					ImGui::SliderFloat("[Target] Health", &targetUnit.health, 0.f, 1000.f);
//					ImGui::SliderFloat("[Target] Damage", &targetUnit.damage, 0.f, 2000.f);
//					ImGui::SliderFloat("[Target] Defense", &targetUnit.defense, 0.f, 2000.f);
//					ImGui::SliderFloat("[Target] Attack Range", &targetUnit.attackRange, -50.f, 50.f);
//					ImGui::SliderFloat("[Target] Attack Speed", &targetUnit.attackSpeed, -50.f, 50.f);
//				}
//			}
//		}
//
//		if (ImGui::CollapsingHeader("Transformation"))
//		{
//			ImGui::SliderFloat("Translation X", &transform.position.x, -2000.0f, 2000.0f);
//			ImGui::SliderFloat("Translation Y", &transform.position.y, -2000.0f, 2000.0f);
//			ImGui::SliderFloat("Translation Z", &transform.position.z, -2000.0f, 2000.0f);
//
//			ImGui::SliderFloat("Rotation X", &transform.rotation.x, -2000.f, 2000.0f);
//			ImGui::SliderFloat("Rotation Y", &transform.rotation.y, -2000.f, 2000.0f);
//			ImGui::SliderFloat("Rotation Z", &transform.rotation.z, -2000.f, 2000.0f);
//
//			ImGui::SliderFloat("Scale X", &transform.scale.x, -2000.f, 2000.0f);
//			ImGui::SliderFloat("Scale Y", &transform.scale.y, -2000.f, 2000.0f);
//			ImGui::SliderFloat("Scale Z", &transform.scale.z, -2000.f, 2000.0f);
//		}
//
//		if (ImGui::CollapsingHeader("Collider"))
//		{
//			ImGui::SliderFloat("Mass", &collider.mass, -1.f, 2000.0f);
//			ImGui::SliderFloat("Collider Scale X", &collider.scale.x, -2000.0f, 2000.0f);
//			ImGui::SliderFloat("Collider Scale Y", &collider.scale.y, -2000.0f, 2000.0f);
//			ImGui::SliderFloat("Collider Scale Z", &collider.scale.z, -2000.0f, 2000.0f);
//		}
//
//		if (ImGui::Button("Set to inactive"))
//		{
//			unitsystem->AddInactiveEntity(testHandler);
//
//			if (selection == activeEntityList.size() - 1)
//			{
//				selection = selection - 1;
//			}
//		}
//
//		ImGui::SameLine();	
//
//		if (ImGui::Button("Set all to inactive"))
//		{
//			for (int i = 0; i < activeEntityList.size(); i++)
//			{
//				Entity tmp = activeEntityList[i];
//
//				unitsystem->AddInactiveEntity(tmp);
//			}
//
//			selection = 0;
//		}
//
//	}
//
//	ImGui::End();
//}
