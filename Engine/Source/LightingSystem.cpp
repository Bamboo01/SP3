#include "LightingSystem.h"

void LightingSystem::Setup()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<Transform>());
	signature.set(coordinator.GetComponentType<LightSource>());
	signature.set(coordinator.GetComponentType<EntityState>());
	coordinator.SetSystemSignature<LightingSystem>(signature);
}

void LightingSystem::Init()
{
	for (auto& entity : m_Entities)
	{
		auto& lightsource = coordinator.GetComponent<LightSource>(entity);
		lightsource.lightID = renderer.lightingManager.getNewLightID();
	}
}

void LightingSystem::Update(float dt)
{
	for (auto& entity : m_Entities)
	{
		auto& transform = coordinator.GetComponent<Transform>(entity);
		auto& lightsource = coordinator.GetComponent<LightSource>(entity);

		lightsource.light.position = transform.position;
		glm::vec3 rot = glm::radians(transform.rotation);


		glm::mat4 rotmat(1.f);
		rotmat = glm::rotate(rotmat, rot.x, glm::vec3(1, 0, 0));
		rotmat = glm::rotate(rotmat, rot.y, glm::vec3(0, 1, 0));
		rotmat = glm::rotate(rotmat, rot.z, glm::vec3(0, 0, 1));
		lightsource.light.spotDirection = transform.AxisY;
		lightsource.light.position = transform.position;

		renderer.lightingManager.getLightByID(lightsource.lightID) = lightsource.light;
	}
}
