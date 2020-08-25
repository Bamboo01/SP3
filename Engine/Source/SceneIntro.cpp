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
	coordinator.RegisterComponent<ObjectPoolSystem>();
	coordinator.RegisterComponent<ParticleSystemParameters>();
	coordinator.RegisterComponent<Controller>();

	coordinator.RegisterComponent<Pool>();

	transformsystem = coordinator.RegisterSystem<TransformSystem>();
	camerasystem = coordinator.RegisterSystem<CameraSystem>();
	rendersystem = coordinator.RegisterSystem<RenderSystem>();
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
}

void SceneIntro::EarlyUpdate(double dt)
{
}

void SceneIntro::Update(double dt)
{
}

void SceneIntro::LateUpdate(double dt)
{
}

void SceneIntro::PreRender()
{
}

void SceneIntro::Render()
{
}

void SceneIntro::PostRender()
{
}

void SceneIntro::Exit()
{
}
