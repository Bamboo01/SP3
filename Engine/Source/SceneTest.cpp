#include "SceneTest.h"
#include "Application.h"

#include "../Dependencies/ImGui/imgui.h"
#include "../Dependencies/ImGui/imgui_impl_glfw.h"
#include "../Dependencies/ImGui/imgui_impl_opengl3.h"

void SceneTest::Init()
{
	coordinator.Init();
	coordinator.RegisterComponent<Camera>();
	coordinator.RegisterComponent<Transform>();
	coordinator.RegisterComponent<RenderData>();
	coordinator.RegisterComponent<CanvasImage>();
	
	transformsystem = coordinator.RegisterSystem<TransformSystem>();
	camerasystem = coordinator.RegisterSystem<CameraSystem>();
	rendersystem = coordinator.RegisterSystem<RenderSystem>();
	canvasimagesystem = coordinator.RegisterSystem<CanvasImageSystem>();

	transformsystem->Setup();
	camerasystem->Setup();
	rendersystem->Setup();
	canvasimagesystem->Setup();

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

	Entity UI = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(UI, Transform());
	coordinator.GetComponent<Transform>(UI).position = glm::vec3(-0.5, -0.25, 1);
	coordinator.GetComponent<Transform>(UI).scale = glm::vec3(0.5, 0.5, 1);
	coordinator.AddComponent<CanvasImage>(UI, CanvasImage("Images//crate.tga"));

	/*Init all systems*/
	camerasystem->Init();
	rendersystem->Init();
	transformsystem->Init();
	canvasimagesystem->Init();
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
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void SceneTest::Render()
{
	rendersystem->Render();
	camerasystem->Render();
	canvasimagesystem->Render();
	renderImGui();
}

void SceneTest::PostRender()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void SceneTest::Exit()
{
	coordinator.Exit();
}

void SceneTest::renderImGui()
{
	ImGui::Begin("Demo window");
	ImGui::Button("Hello!");
	ImGui::End();
}
