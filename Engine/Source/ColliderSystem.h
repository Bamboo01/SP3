#pragma once

#include "System.h"
#include "Transform.h"
#include "Collider.h"
#include "Coordinator.h"
#include "Unit.h"
#include "RenderData.h"
#include "RayCastingSystem.h"

extern Coordinator coordinator;

#pragma once
class ColliderSystem : public System
{
public:
    void Setup();
    void Init();
    void Update(double dt);
    bool collisionCheck(Entity obj1, Entity obj2);
    void collisionResponse(Entity obj1, Entity obj2);
    bool collisionOnAxis(glm::vec3 rPos, glm::vec3 axis, Transform& firstObject, Transform& secondObject, Collider& firstCollider, Collider& secondCollider);
    float getOverlapMagnitude(glm::vec3 rPos, glm::vec3 axis, Transform& firstObject, Transform& secondObject, Collider& firstCollider, Collider& secondCollider);
    bool raycollisioncheck(Entity ray, Entity obj);
    bool rayplanecheck(glm::vec3 rPos, glm::vec3 axis, Transform& object, Collider& collider);
    void SetRayCastSystem(std::shared_ptr<RayCastingSystem> raycastsystem);

private:
    std::shared_ptr<RayCastingSystem> raycastsystem;

    glm::vec3 firstposclick;
    glm::vec3 secondposclick;
    float maxX, minX;
    float maxZ, minZ;
};