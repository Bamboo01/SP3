#include "MenuCameraSystem.h"

void MenuCameraSystem::Setup()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<Transform>());
	signature.set(coordinator.GetComponentType<EntityState>());
	signature.set(coordinator.GetComponentType<Camera>());
	coordinator.SetSystemSignature<MenuCameraSystem>(signature);
}

void MenuCameraSystem::Init()
{
}

void MenuCameraSystem::Update()
{
}
