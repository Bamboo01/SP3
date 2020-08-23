#include "RayCastingSystem.h"
#include <iostream>
#include "Application.h"

void RayCastingSystem::Setup()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<Camera>());
	signature.set(coordinator.GetComponentType<RayCasting>());
	signature.set(coordinator.GetComponentType<EntityState>());
	coordinator.SetSystemSignature<RayCastingSystem>(signature);
}

void RayCastingSystem::Init(std::set<Entity>* colliderentitylist)
{
	this->colliderentitylist = colliderentitylist;

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
			ray.RayEndPos = glm::vec3(camera.position.x, camera.position.y, camera.position.z);
			ray.Ray = calculateMouseRay();
		}

        callRayCollision();
	}
}

void RayCastingSystem::Render()
{
}

bool RayCastingSystem::raycollisioncheck(Entity ray, Entity obj)
{
	auto& RayTransform = coordinator.GetComponent<Transform>(ray);
	auto& Ray = coordinator.GetComponent<RayCasting>(ray);
	auto& ObjectTransform = coordinator.GetComponent<Transform>(obj);
	auto& ObjectCollider = coordinator.GetComponent<Collider>(obj);

	glm::vec3 relativePos = ObjectTransform.position - Ray.RayEndPos;

	bool collided = !(rayplanecheck(relativePos, ObjectTransform.AxisX, ObjectTransform, ObjectCollider) ||
		rayplanecheck(relativePos, ObjectTransform.AxisY, ObjectTransform, ObjectCollider) ||
		rayplanecheck(relativePos, ObjectTransform.AxisZ, ObjectTransform, ObjectCollider));


	if (!collided)
		return collided;

	return collided;
	return false;
}

bool RayCastingSystem::rayplanecheck(glm::vec3 rPos, glm::vec3 axis, Transform object, Collider collider)
{
	return (fabs(glm::dot(rPos, axis))) >
		(fabs(glm::dot(object.AxisX * glm::vec3(0.5, 0.5, 0.5) * collider.scale.x, axis)) +
			fabs(glm::dot(object.AxisY * glm::vec3(0.5, 0.5, 0.5) * collider.scale.y, axis)) +
			fabs(glm::dot(object.AxisZ * glm::vec3(0.5, 0.5, 0.5) * collider.scale.z, axis)));
}

void RayCastingSystem::callRayCollision()
{
    // Ray collision 

    std::set<Entity> entityset1 = m_Entities;
    std::set<Entity> entityset2 = *colliderentitylist;

    for (auto const& entity : entityset1)
    {
        auto& transform = coordinator.GetComponent<Transform>(entity);
        auto& ray = coordinator.GetComponent<RayCasting>(entity);

        for (int i = 0; i < 500; ++i)
        {
            for (auto const& entity2 : entityset2)
            {
                auto& ObjectTransform = coordinator.GetComponent<Transform>(entity2);
                if (raycollisioncheck(entity, entity2))
                {
                   // std::cout << "Ray collided with object!" << std::endl;
                    break;
                }
            }

            // If ray overlapped with terrain y
            for (auto const& terrainmap : TerrainEntities)
            {
                auto& terrain = coordinator.GetComponent<TerrainData>(terrainmap);

                if (ray.RayEndPos.y < terrain.ReadHeightMap(ray.RayEndPos.x, ray.RayEndPos.z))
                {
                   // std::cout << "Overlapped with Terrain" << std::endl;

                    if (CursorInGUI == false)
                    {
                        static bool bLButtonState = false;
                        // Add Code to get first left click position and position after you let go here
                        if (Application::IsMousePressed(0) && !bLButtonState)
                        {
                            minX = 0;
                            maxX = 0;
                            minZ = 0;
                            maxZ = 0;
                            std::cout << " Cleared! " << std::endl;
                            selectedunitlist.clear();
                            bLButtonState = true;
                            firstposclick = ray.RayEndPos;
                        }
                        else if (bLButtonState && !Application::IsMousePressed(0))
                        {
                            bLButtonState = false;
                            secondposclick = ray.RayEndPos;
                            //std::cout << "First Pos: " << firstposclick << std::endl;
                            //std::cout << "Second Pos: " << secondposclick << std::endl;
                            // Calculating BottomLeft and TopRight
                            if (firstposclick.x < secondposclick.x)
                            {
                                minX = firstposclick.x;
                                maxX = secondposclick.x;
                            }
                            else if (firstposclick.x > secondposclick.x)
                            {
                                minX = secondposclick.x;
                                maxX = firstposclick.x;
                            }
                            if (firstposclick.z < secondposclick.z)
                            {
                                minZ = firstposclick.z;
                                maxZ = secondposclick.z;
                            }
                            else if (firstposclick.z > secondposclick.z)
                            {
                                minZ = secondposclick.z;
                                maxZ = firstposclick.z;
                            }
                            unitSelection();
                        }
                    }
                }
            }
            ray.RayEndPos += ray.Ray * 3.f;
            glm::mat4 model(1.0);
            model = glm::translate(model, ray.RayEndPos);
            model = glm::scale(model, glm::vec3(0.1f));
            renderer.getMesh(GEO_GRIDCUBE)->DynamicTransformMatrices.push_back(model);
            transform.position = glm::vec3(ray.RayEndPos.x, ray.RayEndPos.y, ray.RayEndPos.z);
        }
    }
}

void RayCastingSystem::unitSelection()
{
    // Unit Selection Check
    if (minX != 0 && maxX != 0 && minZ != 0 && maxZ != 0)
    {
        std::set<Entity> entityset2 = *colliderentitylist;

        for (auto const& entity2 : entityset2)
        {
            auto& transform = coordinator.GetComponent<Transform>(entity2);

            if (transform.position.x > minX && transform.position.x < maxX && transform.position.z > minZ && transform.position.z < maxZ)
            {
                std::cout << " Push! " << std::endl;
                selectedunitlist.push_back(entity2);
            }
        }
    }
    if (selectedunitlist.size() != 0)
    {
        std::cout << selectedunitlist.size() << std::endl;
    }
}

void RayCastingSystem::SetTerrainEntities(std::set<Entity> terrain)
{
    TerrainEntities = terrain;
}

void RayCastingSystem::GetCursorInGUI(bool cursoringui)
{
    CursorInGUI = cursoringui;
}

glm::vec3 RayCastingSystem::calculateMouseRay()
{
	double mousex, mousey;
	Application::GetCursorPos(&mousex, &mousey);
	glm::vec2 normalizedCoords = getNormalizedDeviceCoords(mousex, mousey);
	glm::vec4 clipCoords = glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.f, 1.f);
	glm::vec3 worldCoords = toWorldCoords(clipCoords);

	glm::vec3 dir = glm::normalize(worldCoords);
   // dir.x = dir.x * -1.f;
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
