#include "CameraControllerSystem.h"
#include "gtc/constants.hpp"

void CameraControllerSystem::Update(float dt)
{
    for (auto const& entity : m_Entities)
    {

		auto& camera = coordinator.GetComponent<Camera>(entity);

		if (Application::IsKeyPressed('E'))
		{
			camera.position += camera.right * 20.f * dt;
		}
		if (Application::IsKeyPressed('Q'))
		{
			camera.position -= camera.right * 20.f * dt;
		}
    }
}

void CameraControllerSystem::Setup()
{
    Signature signature;
    signature.set(coordinator.GetComponentType<Camera>());
    signature.set(coordinator.GetComponentType<CameraController>());
    signature.set(coordinator.GetComponentType<EntityState>());
    coordinator.SetSystemSignature<CameraControllerSystem>(signature);
}
	

