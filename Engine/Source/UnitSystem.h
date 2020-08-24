#include "System.h"
#include "Unit.h"
#include "Collider.h"
#include "Transform.h"
#include "Coordinator.h"
#include "RenderData.h"
#include "Renderer.h"
#include "ObjectPoolSystem.h"
#include "QuadTreeSystem.h"

extern Coordinator coordinator;
extern Renderer renderer;

#pragma once
class UnitSystem : public System
{
public:
    virtual void Setup();
    virtual void Init();
    virtual void Update(double dt);

    void SetObjectPoolSystem(std::shared_ptr<ObjectPoolSystem> ptr);
    void SetQuadTreeSystem(std::shared_ptr<QuadTreeSystem> ptr);

    void AddInactiveEntity(Entity entity);

    void FetchNearbyTargetWithinRange(Entity unit);

    Entity CreateUnit(Unit::UnitType type, Unit::UnitFaction faction, int level, Transform transform);
    Entity CreateProjectile(Entity origin, Entity target);

    void ApplyAttack(Entity attacker, Entity receiver);
    void UpdateProjectile(Entity projectile);
private:
    double d_elapsedTime;
    std::shared_ptr<ObjectPoolSystem> objectpoolsystem;
    std::shared_ptr<QuadTreeSystem> quadtreesystem;
};
