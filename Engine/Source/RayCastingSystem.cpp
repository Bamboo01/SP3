#include "RayCastingSystem.h"
#include <iostream>

void RayCastingSystem::Setup()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<Camera>());
	signature.set(coordinator.GetComponentType<RayCasting>());
	//signature.set(coordinator.GetComponentType<Transform>());
	coordinator.SetSystemSignature<RayCastingSystem>(signature);
}

void RayCastingSystem::Init()
{
	for (auto const& entity : m_Entities)
	{
		auto& camera = coordinator.GetComponent<Camera>(entity);
		auto& ray = coordinator.GetComponent<RayCasting>(entity);
		ray.Init(camera);
	}
}

void RayCastingSystem::Update(double dt)
{
	for (auto const& entity : m_Entities)
	{
		auto& camera = coordinator.GetComponent<Camera>(entity);
		auto& ray = coordinator.GetComponent<RayCasting>(entity);
		if (camera.type == CAMERA_TYPE::CAMERA_MAIN)
		{
			ray.viewMatrix = camera.getViewMatrix();
			ray.Ray = calculateMouseRay();
			std::cout << ray.Ray.x << " " << ray.Ray.y << " " << ray.Ray.z << std::endl;
			ray.RayStartPos = glm::vec3(camera.position.x, camera.position.y, camera.position.z);
			ray.RayEndPos = glm::vec3(camera.position.x, camera.position.y, camera.position.z);
		}
	}
}

void RayCastingSystem::Render()
{
}

glm::vec3 RayCastingSystem::calculateMouseRay()
{
	double mousex, mousey;
	Application::GetCursorPos(&mousex, &mousey);
	glm::vec2 normalizedCoords = getNormalizedDeviceCoords(mousex, mousey);
	glm::vec4 clipCoords = glm::vec4(normalizedCoords.x, normalizedCoords.y, 1.f, 1.f);
	glm::vec3 worldCoords = toWorldCoords(clipCoords);

	glm::vec3 dir = glm::normalize(worldCoords);
	return dir;
}

glm::vec2 RayCastingSystem::getNormalizedDeviceCoords(double mousex, double mousey)
{
	double x = (2 * mousex) / Application::GetWindowWidth() - 1;
	double y = (2 * mousey) / Application::GetWindowHeight() - 1;
	return glm::vec2(x, -y);
}

glm::vec3 RayCastingSystem::toWorldCoords(glm::vec4 clipCoords)
{
	for (auto const& entity : m_Entities)
	{
		auto& ray = coordinator.GetComponent<RayCasting>(entity);
		glm::vec4 eyeCoord(glm::inverse(ray.projectionMatrix) * clipCoords);
		eyeCoord = glm::vec4(eyeCoord.x, eyeCoord.y, -1.f, 0);

		return glm::vec3(glm::inverse(ray.viewMatrix) * eyeCoord);
	}
}
