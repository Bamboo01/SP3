#include "ColliderSystem.h"
#include "Application.h"

void ColliderSystem::Update(double dt)
{
    minX = 0;
    maxX = 0;
    minZ = 0;
    maxZ = 0;

    for (std::set<Entity>::iterator it = m_Entities.begin(); it != m_Entities.end(); it++)
    {
        Entity firstObject = *it;
        auto& ObjectTransform = coordinator.GetComponent<Transform>(firstObject);
        auto& ObjectUnit = coordinator.GetComponent<Unit>(firstObject);

        for (std::set<Entity>::iterator it2 = it; it2 != m_Entities.end(); it2++)
        {
			if (it2 == it)
				continue;

			Entity secondObject = *it2;
			auto& ObjectTransform2 = coordinator.GetComponent<Transform>(secondObject);
			auto& ObjectUnit2 = coordinator.GetComponent<Unit>(secondObject);

			if (!ObjectUnit.active || !ObjectUnit2.active || (ObjectUnit.unitType == Unit::PROJECTILE && ObjectUnit2.unitType == Unit::PROJECTILE) || (ObjectUnit.unitFaction == ObjectUnit2.unitFaction))
				continue;

            if (glm::length(ObjectTransform.position - ObjectTransform2.position) <= 100)
            {
                if (collisionCheck(firstObject, secondObject))
                {
                    std::cout << "ColliderSystem: Collision Detected" << std::endl;

                    if (ObjectUnit.unitType == Unit::PROJECTILE)
                    {
                        unitSystem->ApplyAttack(firstObject, secondObject);
                        continue;
                    }
                    else if (ObjectUnit2.unitType == Unit::PROJECTILE)
                    {
                        unitSystem->ApplyAttack(secondObject, firstObject);
                        continue;
                    }

                    collisionResponse(firstObject, secondObject);
                }
            }
        }
    }

    // Ray collision 
    std::set<Entity> entityset1 = raycastSystem->m_Entities;

    for (auto const& entity : entityset1)
    {
        auto& transform = coordinator.GetComponent<Transform>(entity);
        auto& ray = coordinator.GetComponent<RayCasting>(entity);

        for (int i = 0; i < 500; ++i)
        {
            for (std::set<Entity>::iterator it2 = m_Entities.begin(); it2 != m_Entities.end(); it2++)
            {
                Entity Object = *it2;
                auto& ObjectTransform = coordinator.GetComponent<Transform>(Object);

                if (raycollisioncheck(entity, Object))
                {
                    //std::cout << "Ray collided with object!" << std::endl;
                    break;
                }
            }

            // If ray overlapped with terrain y, break the loop
            //if (ray.RayEndPos.y < 350.f * ReadHeightMap(ray.m_heightMap, ray.RayEndPos.x / 4000, ray.RayEndPos.z / 4000))
            //{
            //    // std::cout << "Overlapped with Terrain" << std::endl;

            //     // Add Code to get first left click position and position after you let go here
            //    static bool bLButtonState = false;
            //    if (Application::IsMousePressed(0) && !bLButtonState)
            //    {
            //        bLButtonState = true;
            //        firstposclick = ray.RayEndPos;
            //    }
            //    else if (bLButtonState && !Application::IsMousePressed(0))
            //    {
            //        bLButtonState = false;
            //        secondposclick = ray.RayEndPos;
            //        //std::cout << "First Pos: " << firstposclick << std::endl;
            //        //std::cout << "Second Pos: " << secondposclick << std::endl;
            //        // Calculating BottomLeft and TopRight
            //        if (firstposclick.x < secondposclick.x)
            //        {
            //            minX = firstposclick.x;
            //            maxX = secondposclick.x;
            //        }
            //        else if (firstposclick.x > secondposclick.x)
            //        {
            //            minX = secondposclick.x;
            //            maxX = firstposclick.x;
            //        }
            //        if (firstposclick.z < secondposclick.z)
            //        {
            //            minZ = firstposclick.z;
            //            maxZ = secondposclick.z;
            //        }
            //        else if (firstposclick.z > secondposclick.z)
            //        {
            //            minZ = secondposclick.z;
            //            maxZ = firstposclick.z;
            //        }
            //    }
            //    break;
            //}
            ray.RayEndPos = glm::vec3(ray.RayEndPos.x + ray.Ray.x * 3, ray.RayEndPos.y + ray.Ray.y * 3, ray.RayEndPos.z + ray.Ray.z * 3);
            transform.position = glm::vec3(ray.RayEndPos.x, ray.RayEndPos.y, ray.RayEndPos.z);
        }
    }

    // Unit Selection Check
    if (minX != 0 && maxX != 0 && minZ != 0 && maxZ != 0)
    {
        std::set<Entity> entityset2 = m_Entities;

        int counter = 0;
        for (auto const& entity2 : entityset2)
        {
            auto& transform = coordinator.GetComponent<Transform>(entity2);
            if (transform.position.x > minX && transform.position.x < maxX && transform.position.z < minZ && transform.position.z > maxZ)
            {
                ++counter;
            }
        }
        if (counter != 0)
            std::cout << counter << std::endl;
    }
}

void ColliderSystem::Setup()
{
    Signature signature;
    signature.set(coordinator.GetComponentType<Transform>());
    signature.set(coordinator.GetComponentType<RenderData>());
    signature.set(coordinator.GetComponentType<Collider>());
    signature.set(coordinator.GetComponentType<Unit>());
    coordinator.SetSystemSignature<ColliderSystem>(signature);
}

void ColliderSystem::Init()
{

}

bool ColliderSystem::collisionCheck(Entity object1, Entity object2)
{
    if (object1 == object2)
        return false;

    auto& ObjectTransform = coordinator.GetComponent<Transform>(object1);
    auto& ObjectTransform2 = coordinator.GetComponent<Transform>(object2);
    auto& ObjectCollider = coordinator.GetComponent<Collider>(object1);
    auto& ObjectCollider2 = coordinator.GetComponent<Collider>(object2);
    glm::vec3 relativePos = ObjectTransform2.position - ObjectTransform.position;

    bool collided = !(collisionOnAxis(relativePos, ObjectTransform.AxisX, ObjectTransform, ObjectTransform2, ObjectCollider, ObjectCollider2) ||
        collisionOnAxis(relativePos, ObjectTransform.AxisY, ObjectTransform, ObjectTransform2, ObjectCollider, ObjectCollider2) ||
        collisionOnAxis(relativePos, ObjectTransform.AxisZ, ObjectTransform, ObjectTransform2, ObjectCollider, ObjectCollider2) ||
        collisionOnAxis(relativePos, ObjectTransform2.AxisX, ObjectTransform, ObjectTransform2, ObjectCollider, ObjectCollider2) ||
        collisionOnAxis(relativePos, ObjectTransform2.AxisY, ObjectTransform, ObjectTransform2, ObjectCollider, ObjectCollider2) ||
        collisionOnAxis(relativePos, ObjectTransform2.AxisZ, ObjectTransform, ObjectTransform2, ObjectCollider, ObjectCollider2) ||
        collisionOnAxis(relativePos, glm::cross(ObjectTransform.AxisX, ObjectTransform2.AxisX), ObjectTransform, ObjectTransform2, ObjectCollider, ObjectCollider2) ||
        collisionOnAxis(relativePos, glm::cross(ObjectTransform.AxisX, ObjectTransform2.AxisY), ObjectTransform, ObjectTransform2, ObjectCollider, ObjectCollider2) ||
        collisionOnAxis(relativePos, glm::cross(ObjectTransform.AxisX, ObjectTransform2.AxisZ), ObjectTransform, ObjectTransform2, ObjectCollider, ObjectCollider2) ||
        collisionOnAxis(relativePos, glm::cross(ObjectTransform.AxisY, ObjectTransform2.AxisX), ObjectTransform, ObjectTransform2, ObjectCollider, ObjectCollider2) ||
        collisionOnAxis(relativePos, glm::cross(ObjectTransform.AxisY, ObjectTransform2.AxisY), ObjectTransform, ObjectTransform2, ObjectCollider, ObjectCollider2) ||
        collisionOnAxis(relativePos, glm::cross(ObjectTransform.AxisY, ObjectTransform2.AxisZ), ObjectTransform, ObjectTransform2, ObjectCollider, ObjectCollider2) ||
        collisionOnAxis(relativePos, glm::cross(ObjectTransform.AxisZ, ObjectTransform2.AxisX), ObjectTransform, ObjectTransform2, ObjectCollider, ObjectCollider2) ||
        collisionOnAxis(relativePos, glm::cross(ObjectTransform.AxisZ, ObjectTransform2.AxisY), ObjectTransform, ObjectTransform2, ObjectCollider, ObjectCollider2) ||
        collisionOnAxis(relativePos, glm::cross(ObjectTransform.AxisZ, ObjectTransform2.AxisZ), ObjectTransform, ObjectTransform2, ObjectCollider, ObjectCollider2));

    if (!collided)
        return collided;

    return collided;
}

void ColliderSystem::collisionResponse(Entity object1, Entity object2)
{
    auto& ObjectTransform = coordinator.GetComponent<Transform>(object1);
    auto& ObjectTransform2 = coordinator.GetComponent<Transform>(object2);
    auto& ObjectCollider = coordinator.GetComponent<Collider>(object1);
    auto& ObjectCollider2 = coordinator.GetComponent<Collider>(object2);
    glm::vec3 relativePos = ObjectTransform2.position - ObjectTransform.position;

    float offset[6] =
    {
        getOverlapMagnitude(relativePos, ObjectTransform.AxisX, ObjectTransform, ObjectTransform2, ObjectCollider, ObjectCollider2),
        getOverlapMagnitude(relativePos, ObjectTransform.AxisY, ObjectTransform, ObjectTransform2, ObjectCollider, ObjectCollider2),
        getOverlapMagnitude(relativePos, ObjectTransform.AxisZ, ObjectTransform, ObjectTransform2, ObjectCollider, ObjectCollider2),
        getOverlapMagnitude(relativePos, ObjectTransform2.AxisX, ObjectTransform, ObjectTransform2, ObjectCollider, ObjectCollider2),
        getOverlapMagnitude(relativePos, ObjectTransform2.AxisY, ObjectTransform, ObjectTransform2, ObjectCollider, ObjectCollider2),
        getOverlapMagnitude(relativePos, ObjectTransform2.AxisZ, ObjectTransform, ObjectTransform2, ObjectCollider, ObjectCollider2),
    };

    glm::vec3 normal, translationalVector, translationalVector2;
    float overlapMagnitude = FLT_MAX; // need to find the lowest
    int axis;

    for (int i = 0; i < 6; i++)
    {
        if (fabs(offset[i]) < overlapMagnitude)
        {
            overlapMagnitude = fabs(offset[i]);
            axis = i;
        }
    }

    switch (axis)
    {
    case 0:
        normal = ObjectTransform.AxisX;
        break;
    case 1:
        normal = ObjectTransform.AxisY;
        break;
    case 2:
        normal = ObjectTransform.AxisZ;
        break;
    case 3:
        normal = ObjectTransform2.AxisX;
        break;
    case 4:
        normal = ObjectTransform2.AxisY;
        break;
    case 5:
        normal = ObjectTransform2.AxisZ;
        break;
    }

    translationalVector = normal * overlapMagnitude;

    // These checks are to prevent the boxes from clipping into each another
    // I compared their relative pos and translational vec, if it's the same direction for that axis, the translational vector will be flipped

    if ((axis == 0 || axis == 3) && ((relativePos.x > 0 && translationalVector.x > 0) || (relativePos.x < 0 && translationalVector.x < 0)) )
        translationalVector *= -1;

    if ((axis == 1 || axis == 4) && ((relativePos.y > 0 && translationalVector.y > 0) || (relativePos.y < 0 && translationalVector.y < 0)))
        translationalVector *= -1;

    if ((axis == 2 || axis == 5) && ((relativePos.z > 0 && translationalVector.z > 0) || (relativePos.z < 0 && translationalVector.z < 0)))
        translationalVector *= -1;

    translationalVector2 = translationalVector * glm::vec3(-1, -1, -1);

    // If mass == -1, it is a static object. No displacement happens

    if (ObjectCollider.mass != -1)
        ObjectTransform.position += translationalVector * (1 / ObjectCollider.mass);

    if (ObjectCollider2.mass != -1)
        ObjectTransform2.position += translationalVector2 * (1 / ObjectCollider2.mass);
}


bool ColliderSystem::collisionOnAxis(glm::vec3 rPos, glm::vec3 axis, Transform& firstObject, Transform& secondObject, Collider& firstCollider, Collider& secondCollider)
{   
    return (fabs(glm::dot(rPos, axis))) >
        fabs(glm::dot(firstObject.AxisX * glm::vec3(0.5, 0.5, 0.5) * firstCollider.scale.x, axis)) +
            fabs(glm::dot(firstObject.AxisY * glm::vec3(0.5, 0.5, 0.5) * firstCollider.scale.y, axis)) +
            fabs(glm::dot(firstObject.AxisZ * glm::vec3(0.5, 0.5, 0.5) * firstCollider.scale.z, axis)) +
            fabs(glm::dot(secondObject.AxisX * glm::vec3(0.5, 0.5, 0.5) * secondCollider.scale.x, axis)) +
            fabs(glm::dot(secondObject.AxisY * glm::vec3(0.5, 0.5, 0.5) * secondCollider.scale.y, axis)) +
            fabs(glm::dot(secondObject.AxisZ * glm::vec3(0.5, 0.5, 0.5) * secondCollider.scale.z, axis));
}



float ColliderSystem::getOverlapMagnitude(glm::vec3 rPos, glm::vec3 axis, Transform& firstObject, Transform& secondObject, Collider& firstCollider, Collider& secondCollider)
{
    return (fabs(glm::dot(firstObject.AxisX * glm::vec3(0.5, 0.5, 0.5) * firstCollider.scale.x, axis)) +
        fabs(glm::dot(firstObject.AxisY * glm::vec3(0.5, 0.5, 0.5) * firstCollider.scale.y, axis)) +
        fabs(glm::dot(firstObject.AxisZ * glm::vec3(0.5, 0.5, 0.5) * firstCollider.scale.z, axis)) +
        fabs(glm::dot(secondObject.AxisX * glm::vec3(0.5, 0.5, 0.5) * secondCollider.scale.x, axis)) +
        fabs(glm::dot(secondObject.AxisY * glm::vec3(0.5, 0.5, 0.5) * secondCollider.scale.y, axis)) +
        fabs(glm::dot(secondObject.AxisZ * glm::vec3(0.5, 0.5, 0.5) * secondCollider.scale.z, axis))) - fabs(glm::dot(rPos, axis));
}

bool ColliderSystem::raycollisioncheck(Entity ray, Entity obj)
{
    auto& RayTransform = coordinator.GetComponent<Transform>(ray);
    auto& Ray = coordinator.GetComponent<RayCasting>(ray);
    auto& ObjectTransform = coordinator.GetComponent<Transform>(obj);
    auto& ObjectCollider = coordinator.GetComponent<Collider>(obj);

    glm::vec3 relativePos = ObjectTransform.position - RayTransform.position;

    bool collided = !(rayplanecheck(relativePos, ObjectTransform.AxisX, ObjectTransform, ObjectCollider) ||
        rayplanecheck(relativePos, ObjectTransform.AxisY, ObjectTransform, ObjectCollider) ||
        rayplanecheck(relativePos, ObjectTransform.AxisZ, ObjectTransform, ObjectCollider));


    if (!collided)
        return collided;

    return collided;
    return false;
}

bool ColliderSystem::rayplanecheck(glm::vec3 rPos, glm::vec3 axis, Transform& object, Collider& collider)
{
    return (fabs(glm::dot(rPos, axis))) >
        (fabs(glm::dot(object.AxisX * glm::vec3(0.5, 0.5, 0.5) * collider.scale.x, axis)) +
            fabs(glm::dot(object.AxisY * glm::vec3(0.5, 0.5, 0.5) * collider.scale.y, axis)) +
            fabs(glm::dot(object.AxisZ * glm::vec3(0.5, 0.5, 0.5) * collider.scale.z, axis)));
}

void ColliderSystem::SetRayCastSystem(std::shared_ptr<RayCastingSystem> raycastsystem)
{
    this->raycastSystem = raycastsystem;
}

void ColliderSystem::SetUnitSystem(std::shared_ptr<UnitSystem> unitSystem)
{
    this->unitSystem = unitSystem;
}

