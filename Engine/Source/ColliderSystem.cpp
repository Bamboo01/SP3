#include "ColliderSystem.h"
#include "Application.h"

void ColliderSystem::Update(double dt)
{
    for (std::set<Entity>::iterator it = m_Entities.begin(); it != m_Entities.end(); it++)
    {
        Entity firstObject = *it;
        auto& ObjectTransform = coordinator.GetComponent<Transform>(firstObject);
        auto& ObjectUnit = coordinator.GetComponent<Unit>(firstObject);
        auto& ObjectEntityState = coordinator.GetComponent<EntityState>(firstObject);

        std::vector<Entity> entityInQuadVector = quadTreeSystem->GetEntityInQuad(quadTreeSystem->GetNearbyEntityQuad(firstObject));

        if (entityInQuadVector.size() <= 1)
            break;

        for (int i = 0; i < entityInQuadVector.size(); i++)
        {
            Entity tmp = entityInQuadVector[i];

            if (tmp == firstObject)
                continue;

            auto& ObjectTransform2 = coordinator.GetComponent<Transform>(tmp);
            auto& ObjectUnit2 = coordinator.GetComponent<Unit>(tmp);
            auto& ObjectEntityState2 = coordinator.GetComponent<EntityState>(tmp);

            if ((!ObjectEntityState.active) || (!ObjectEntityState2.active) || (ObjectUnit.unitType == Unit::PROJECTILE && ObjectUnit2.unitType == Unit::PROJECTILE) || (ObjectUnit.unitFaction == ObjectUnit2.unitFaction && ObjectUnit.unitType == Unit::PROJECTILE && ObjectUnit2.unitType == Unit::PROJECTILE))
                continue;

            if (glm::length(ObjectTransform.position - ObjectTransform2.position) <= 100)
            {
                if (collisionCheck(firstObject, tmp))
                {
                    std::cout << "ColliderSystem: Collision Detected" << std::endl;

                    if (ObjectUnit.unitType == Unit::PROJECTILE)
                    {
                        if (ObjectUnit.unitFaction != ObjectUnit2.unitFaction)
                        {
                            unitSystem->ApplyAttack(firstObject, tmp);
                            unitSystem->AddInactiveEntity(firstObject);
                        }
                        continue;
                    }
                    else if (ObjectUnit2.unitType == Unit::PROJECTILE)
                    {
                        if (ObjectUnit.unitFaction != ObjectUnit2.unitFaction)
                        {
                            unitSystem->ApplyAttack(tmp, firstObject);
                            unitSystem->AddInactiveEntity(tmp);
                        }
                        continue;
                    }
                    else
                    {
                        collisionResponse(firstObject, tmp);
                    }
                }
            }
        }

   //     for (std::set<Entity>::iterator it2 = it; it2 != m_Entities.end(); it2++)
   //     {
			//if (it2 == it) // Skips this loop if both loops are on the same entity
			//	continue;

			//Entity secondObject = *it2;
			//auto& ObjectTransform2 = coordinator.GetComponent<Transform>(secondObject);
			//auto& ObjectUnit2 = coordinator.GetComponent<Unit>(secondObject);
   //         auto& ObjectEntityState2 = coordinator.GetComponent<EntityState>(secondObject);


			//if ((!ObjectEntityState.active) || (!ObjectEntityState2.active) || (ObjectUnit.unitType == Unit::PROJECTILE && ObjectUnit2.unitType == Unit::PROJECTILE) || (ObjectUnit.unitFaction == ObjectUnit2.unitFaction && ObjectUnit.unitType == Unit::PROJECTILE && ObjectUnit2.unitType == Unit::PROJECTILE))
			//	continue;

   //         if (collisionCheck(firstObject, secondObject))
   //         {
   //             //std::cout << "ColliderSystem: Collision Detected" << std::endl;

   //             if (ObjectUnit.unitType == Unit::PROJECTILE)
   //             {
   //                 if (ObjectUnit.unitFaction != ObjectUnit2.unitFaction)
   //                 {
   //                     unitSystem->ApplyAttack(firstObject, secondObject);
   //                     unitSystem->AddInactiveEntity(firstObject);
   //                 }
   //                 continue;
   //             }
   //             else if (ObjectUnit2.unitType == Unit::PROJECTILE)
   //             {
   //                 if (ObjectUnit.unitFaction != ObjectUnit2.unitFaction)
   //                 {
   //                     unitSystem->ApplyAttack(secondObject, firstObject);
   //                     unitSystem->AddInactiveEntity(secondObject);
   //                 }
   //                 continue;
   //             }
   //             else
   //             {
   //                 collisionResponse(firstObject, secondObject);
   //             }
   //         }
   //     }
    }
}

void ColliderSystem::Render()
{
    for (auto const& entity : m_Entities)
    {
        auto& transform = coordinator.GetComponent<Transform>(entity);
        auto& collider = coordinator.GetComponent<Collider>(entity);

        glm::mat4 modelmat(1.f);
        glm::vec3 rot = glm::radians(transform.rotation);
        modelmat = glm::translate(modelmat, transform.position);
        modelmat = glm::rotate(modelmat, rot.x, glm::vec3(1, 0, 0));
        modelmat = glm::rotate(modelmat, rot.y, glm::vec3(0, 1, 0));
        modelmat = glm::rotate(modelmat, rot.z, glm::vec3(0, 0, 1));
        modelmat = glm::scale(modelmat, collider.scale);

        renderer.getMesh(GEO_GRIDCUBE)->DynamicTransformMatrices.push_back(modelmat);
    }
}

void ColliderSystem::Setup()
{
    Signature signature;
    signature.set(coordinator.GetComponentType<Transform>());
    signature.set(coordinator.GetComponentType<RenderData>());
    signature.set(coordinator.GetComponentType<Collider>());
    signature.set(coordinator.GetComponentType<Unit>());
    signature.set(coordinator.GetComponentType<EntityState>());
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

void ColliderSystem::SetUnitSystem(std::shared_ptr<UnitSystem> unitSystem)
{
    this->unitSystem = unitSystem;
}

void ColliderSystem::SetQuadTreeSystem(std::shared_ptr<QuadTreeSystem> quadTreeSystem)
{
    this->quadTreeSystem = quadTreeSystem;
}

