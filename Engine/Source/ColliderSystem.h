#pragma once

#include "System.h"
#include "Transform.h"
#include "Collider.h"
#include "Coordinator.h"
#include "Unit.h"
#include "RenderData.h"
#include "UnitSystem.h"

extern Coordinator coordinator;

class ColliderSystem : public System
{
public:
    void Setup();
    void Init();
    void Update(double dt);
    virtual void Render();
    bool collisionCheck(Entity obj1, Entity obj2);
    void collisionResponse(Entity obj1, Entity obj2);
    bool collisionOnAxis(glm::vec3 rPos, glm::vec3 axis, Transform& firstObject, Transform& secondObject, Collider& firstCollider, Collider& secondCollider);
    float getOverlapMagnitude(glm::vec3 rPos, glm::vec3 axis, Transform& firstObject, Transform& secondObject, Collider& firstCollider, Collider& secondCollider);

    void SetUnitSystem(std::shared_ptr<UnitSystem> unitSystem);
    void SetQuadTreeSystem(std::shared_ptr<QuadTreeSystem> quadTreeSystem);

private:
    std::shared_ptr<UnitSystem> unitSystem;
    std::shared_ptr<QuadTreeSystem> quadTreeSystem;

};