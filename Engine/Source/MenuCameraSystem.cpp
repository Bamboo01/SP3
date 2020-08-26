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

void MenuCameraSystem::Update(float dt)
{
	for (const auto& entity : m_Entities)
	{
		auto& camera = coordinator.GetComponent<Camera>(entity);
		camera.target = glm::vec3(0, 0, 0);
		camera.position += camera.right * 3.f * dt;
	}
}
