#include "System.h"
#include "Unit.h"
#include "Collider.h"
#include "TerrainData.h"
#include "Transform.h"
#include "Coordinator.h"
#include "RenderData.h"
#include "Renderer.h"
#include "ObjectPoolSystem.h"
#include "QuadTreeSystem.h"
#include "SoundController.h"
#include "AIController.h"

extern Coordinator coordinator;
extern Renderer renderer;

#pragma once
class UnitSystem : public System
{
public:
    virtual void Setup();
    virtual void Init(std::set<Entity> terrainEntity, std::set<Entity> aiControllerEntities, Entity cameraEntity);
    virtual void Update(double dt);

    void UpdateUnitToTerrain(Entity entity);

    void SetObjectPoolSystem(std::shared_ptr<ObjectPoolSystem> ptr);
    void SetQuadTreeSystem(std::shared_ptr<QuadTreeSystem> ptr);

    void AddInactiveEntity(Entity entity);

    void FetchNearbyTargetWithinRange(Entity unit);

    Entity CreateUnit(Unit::UnitType type, Unit::UnitFaction faction, int level, Transform transform);
    Entity CreateProjectile(Entity origin, Entity target);

    void ApplyAttack(Entity attacker, Entity receiver);
    void UpdateProjectile(Entity projectile);

    int UnitsDeath;
    int WinLose; // 0 = none, 1 = lose, 2 = win;
    int PlayerTotalUnit;

private:
    double d_elapsedTime;
    Entity cameraEntity;
    std::set<Entity> terrainEntity;
    std::set<Entity> aiControllerEntity;
    std::shared_ptr<ObjectPoolSystem> objectpoolsystem;
    std::shared_ptr<QuadTreeSystem> quadtreesystem;
    CSoundController* cSoundController;
    
};
