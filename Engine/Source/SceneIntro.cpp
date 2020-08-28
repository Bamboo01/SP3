#include "SceneIntro.h"

void SceneIntro::Init()
{
	coordinator.Init();
	coordinator.RegisterComponent<Camera>();
	coordinator.RegisterComponent<Transform>();
	coordinator.RegisterComponent<RenderData>();
	coordinator.RegisterComponent<CanvasImage>();
	coordinator.RegisterComponent<CanvasText>();
	coordinator.RegisterComponent<EntityState>();
	coordinator.RegisterComponent<CanvasImageUpdate>();

	transformsystem = coordinator.RegisterSystem<TransformSystem>();
	camerasystem = coordinator.RegisterSystem<CameraSystem>();
	rendersystem = coordinator.RegisterSystem<RenderSystem>();
	canvasimagesystem = coordinator.RegisterSystem<CanvasImageSystem>();
	canvastextsystem = coordinator.RegisterSystem<CanvasTextSystem>();
	entitystatesystem = coordinator.RegisterSystem<EntityStateSystem>();
	canvasimageupdatesystem = coordinator.RegisterSystem<CanvasImageUpdateSystem>();
	introtextsystem = coordinator.RegisterSystem<IntroTextSystem>();

	transformsystem->Setup();
	camerasystem->Setup();
	rendersystem->Setup();
	canvasimagesystem->Setup();
	canvastextsystem->Setup();
	entitystatesystem->Setup();
	canvasimageupdatesystem->Setup();

	Entity maincamera = coordinator.CreateEntity();
	coordinator.AddComponent<Camera>(maincamera, Camera(
		glm::vec3(0, 100, -3.f),
		glm::vec3(60, 0, 0),
		1080, 1080, //Lower this if the FPS stinks
		45.f,
		CAMERA_TYPE::CAMERA_MAIN,
		CAMERA_MODE::MODE_PERSPECTIVE
	));
	//coordinator.AddComponent<CameraController>(maincamera, CameraController());
	//coordinator.AddComponent<RayCasting>(maincamera, RayCasting());
	coordinator.AddComponent<EntityState>(maincamera, EntityState());
	camerasystem->Init();
	rendersystem->Init();
	transformsystem->Init();
	canvasimagesystem->Init();
	canvastextsystem->Init();
	entitystatesystem->Init();
	introtextsystem->Init();
}

void SceneIntro::EarlyUpdate(double dt)
{
	transformsystem->EarlyUpdate(dt);
	camerasystem->EarlyUpdate(dt);
	rendersystem->EarlyUpdate(dt);
	canvasimagesystem->EarlyUpdate(dt);
	canvastextsystem->EarlyUpdate(dt);
	entitystatesystem->EarlyUpdate(dt);
	canvasimageupdatesystem->EarlyUpdate(dt);
}

void SceneIntro::Update(double dt)
{
	transformsystem->Update(dt);
	camerasystem->Update(dt);
	rendersystem->Update(dt);
	canvasimagesystem->Update(dt);
	canvastextsystem->Update(dt);
	entitystatesystem->Update(dt);
	canvasimageupdatesystem->Update(dt);
	introtextsystem->Update(dt);
}

void SceneIntro::LateUpdate(double dt)
{
	transformsystem->LateUpdate(dt);
	camerasystem->LateUpdate(dt);
	rendersystem->LateUpdate(dt);
	canvasimagesystem->LateUpdate(dt);
	canvastextsystem->LateUpdate(dt);
	canvasimageupdatesystem->LateUpdate(dt);
}

void SceneIntro::PreRender()
{
	// ImGui PreRender
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	//ImGui PreRender
}

void SceneIntro::Render()
{
	rendersystem->Render();
	camerasystem->Render();
	canvasimagesystem->Render();
	canvastextsystem->Render();
	canvasimageupdatesystem->Render();
}

void SceneIntro::PostRender()
{
	//ImGui PostRender (Make sure this is called before swapBuffers
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	//ImGui PostRender
}

void SceneIntro::Exit()
{
	coordinator.Exit();
	CSoundController::GetInstance()->StopAllSounds();
}
