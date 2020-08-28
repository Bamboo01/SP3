#include "UnitSystem.h"
#include "Unit_Data.h"
#include <iostream>

void UnitSystem::Setup()
{
    Signature signature;
    signature.set(coordinator.GetComponentType<Transform>());
    signature.set(coordinator.GetComponentType<Unit>());
    signature.set(coordinator.GetComponentType<Collider>());
    signature.set(coordinator.GetComponentType<RenderData>());
    signature.set(coordinator.GetComponentType<EntityState>());
    coordinator.SetSystemSignature<UnitSystem>(signature);
}

void UnitSystem::Init(std::set<Entity> terrainEntitySet, std::set<Entity> aiControllerSet, Entity cameraentity)
{
    terrainEntity = terrainEntitySet;
    aiControllerEntity = aiControllerSet;
    cameraEntity = cameraentity;
    cSoundController = CSoundController::GetInstance();
    UnitsDeath = 0;
    WinLose = 0;
    PlayerTotalUnit = 0;

    for (int i = 0; i < 100; i++) // Init xxx amount of inactive objects
    {
        Entity myObject3;
        myObject3 = coordinator.CreateEntity();
        coordinator.AddComponent<Transform>(myObject3, Transform());
        coordinator.AddComponent<RenderData>(myObject3, RenderData());
        coordinator.AddComponent<Collider>(myObject3, Collider());
        coordinator.AddComponent<Unit>(myObject3, Unit());
        coordinator.AddComponent<EntityState>(myObject3, EntityState(false));
        AddInactiveEntity(myObject3);
    }
}

void UnitSystem::Update(double dt)
{
    d_elapsedTime += dt;

    PlayerTotalUnit = 0;

    std::vector<Entity> unitList;

    for (auto const& entity : m_Entities)
    {
        auto& transform = coordinator.GetComponent<Transform>(entity);
        auto& unit = coordinator.GetComponent<Unit>(entity);
        auto& entityState = coordinator.GetComponent<EntityState>(entity);

        //POSITION THINGY DON'T MIND ME THANKS - SHERWYN
        if (unit.unitFaction == Unit::PLAYER && unit.unitType != Unit::PROJECTILE && unit.unitType != Unit::MELEE_PROJECTILE && !unit.isPreview)
        {
            renderer.fogofwarManager.positions.push_back(glm::vec4(transform.position, 0));
        }
       
        if (unit.unitFaction == Unit::PLAYER)
        {
            PlayerTotalUnit++;
        }

        if (unit.health <= 0) // In the event the unit's health falls to/below 0, deactivate the unit.
        {
            if (unit.unitType == Unit::NORMAL || unit.unitType == Unit::TANK || unit.unitType == Unit::RANGE)
            {
                cSoundController->SetSoundSourcePosition(23, transform.position.x, transform.position.y, transform.position.z);
                cSoundController->PlaySoundByID(23);
            }
            else
            {
                cSoundController->SetSoundSourcePosition(24, transform.position.x, transform.position.y, transform.position.z);
                cSoundController->PlaySoundByID(24);
            }

            if (unit.unitType == Unit::NEXUS && unit.unitFaction == Unit::PLAYER)
            {
                WinLose = 1;
            }
            else if (unit.unitType == Unit::NEXUS && unit.unitFaction == Unit::ENEMY)
            {
                WinLose = 2;
            }

            if (unit.unitFaction == Unit::PLAYER)
            {
                UnitsDeath++;
            }

            AddInactiveEntity(entity);
            continue;
        }

        // HARD CODE BABY
        
        if (transform.position.x < -199)
        {
            transform.position.x = -199 - (transform.position.x + 199);
        }

        if (transform.position.x > 199)
        {
            transform.position.x = 199 - (transform.position.x - 199);
        }

        if (transform.position.z < -199)
        {
            transform.position.z = -199 - (transform.position.z + 199);
        }
    
        if (transform.position.z > 199)
        {
            transform.position.z = 199 - (transform.position.z - 199);
        }

        if (unit.unitFaction == Unit::ENEMY)
        {
            unitList.push_back(entity);
        }

        UpdateUnitToTerrain(entity);

        switch (unit.unitType)
        {
        case Unit::NORMAL:
            FetchNearbyTargetWithinRange(entity);
            break;
        case Unit::TANK:
            FetchNearbyTargetWithinRange(entity);
            break;
        case Unit::RANGE:
            FetchNearbyTargetWithinRange(entity);
            break;
		case Unit::TOWER:
			FetchNearbyTargetWithinRange(entity);
			break;
        case Unit::PROJECTILE:
            UpdateProjectile(entity);
            break;
        case Unit::MELEE_PROJECTILE:
            UpdateProjectile(entity);
            break;
        }

        if (unit.target != UINT_MAX && unit.unitType != Unit::PROJECTILE && unit.unitType != Unit::MELEE_PROJECTILE /*&& unit.velocity != glm::vec3(0, 0, 0)*/)
        {
            ApplyAttack(entity, unit.target);
        }

        // Generate resources if the unit is an generator
        if (unit.unitType == Unit::GENERATOR1)
        {
            if (unit.generationdelay < d_elapsedTime)
            {
                unit.resourcesgenerated += 50;
                unit.generationdelay = d_elapsedTime + unit.timeforgeneration;
            }
        }
        else if (unit.unitType == Unit::GENERATOR2)
        {
            if (unit.generationdelay < d_elapsedTime)
            {
                unit.resourcesgenerated += 10;
                unit.generationdelay = d_elapsedTime + unit.timeforgeneration;
            }
        }
    }

    for (auto& const aientity : aiControllerEntity)
    {
        auto& aiEntityController = coordinator.GetComponent<AIController>(aientity);
        aiEntityController.updateUnitList(unitList);
    }

    numberOfEnemies = unitList.size();
    numberOfPlayer = m_Entities.size() - unitList.size();
}

void UnitSystem::UpdateUnitToTerrain(Entity entity)
{
    for (auto& entities : terrainEntity)
    {
        auto& terrain = coordinator.GetComponent<TerrainData>(entities);
        auto& unitData = coordinator.GetComponent<Unit>(entity);
        auto& unitTransform = coordinator.GetComponent<Transform>(entity);


        if (unitData.unitType == Unit::PROJECTILE || unitData.unitType == Unit::MELEE_PROJECTILE)
            return;

        float yPos = terrain.ReadHeightMap(unitTransform.position.x, unitTransform.position.z) + unitTransform.scale.y * 3;

        unitTransform.position.y = yPos;
	}
}

void UnitSystem::SetObjectPoolSystem(std::shared_ptr<ObjectPoolSystem> ptr)
{
    objectpoolsystem = ptr;
}

void UnitSystem::SetQuadTreeSystem(std::shared_ptr<QuadTreeSystem> ptr)
{
    quadtreesystem = ptr;
}

void UnitSystem::AddInactiveEntity(Entity entity)
{
    auto& entityState = coordinator.GetComponent<EntityState>(entity);
    entityState.active = false;
}

void UnitSystem::FetchNearbyTargetWithinRange(Entity unitID)
{
    auto& transform = coordinator.GetComponent<Transform>(unitID);
    auto& unit = coordinator.GetComponent<Unit>(unitID);
    auto& currentTargetTransform = coordinator.GetComponent<Transform>(unit.target);
    auto& currentTargetUnit = coordinator.GetComponent<Unit>(unit.target);
    auto& currentTargetEntityState = coordinator.GetComponent<EntityState>(unit.target);

    float distanceWithCurrentTarget = 0;

    if (unit.unitType == Unit::UnitType::WALL || unit.unitType == Unit::UnitType::NEXUS || unit.unitType == Unit::UnitType::GENERATOR1 || unit.unitType == Unit::UnitType::GENERATOR2 || unit.unitType == Unit::UnitType::LAB || unit.unitType == Unit::UnitType::PROJECTILE || unit.unitType == Unit::UnitType::MELEE_PROJECTILE) // These shouldn't call this method!
        return;

    Unit::UnitFaction targetFactionRequirement; // A variable to make sure the unit does not target it's own units

    if (unit.unitFaction == Unit::UnitFaction::PLAYER)
        targetFactionRequirement = Unit::UnitFaction::ENEMY;
    else if (unit.unitFaction == Unit::UnitFaction::ENEMY)
        targetFactionRequirement = Unit::UnitFaction::PLAYER;


    if (unit.target != UINT_MAX) // In the event there's a target entity stored
    {
        if (!currentTargetEntityState.active) // If the target entity is not active, we set the unit->target back to default
            unit.target = UINT_MAX;
    }

    if (unit.target != UINT_MAX) // If the target entity is active, so we need to compare the distance between the rest of the other units and this current target
    {
        distanceWithCurrentTarget = glm::length(transform.position - currentTargetTransform.position);

        if (distanceWithCurrentTarget > unit.attackRange + currentTargetUnit.colliderScale.x / 1.5) // Clear target if current target is too far away from auto attacking range
            unit.target = UINT_MAX;
    }

    for (auto const& entity : m_Entities)
    {
        auto& otherUnit = coordinator.GetComponent<Unit>(entity);

        if (entity == unitID) // If the for loops goes onto the same unit, skip this loop
            continue;

        auto& otherTransform = coordinator.GetComponent<Transform>(entity);

        if (otherUnit.unitFaction == targetFactionRequirement)
        {
            float distanceFromLoopedUnit = glm::length(transform.position - otherTransform.position);

            if ((unit.target == UINT_MAX && distanceFromLoopedUnit <= unit.attackRange + otherUnit.colliderScale.x / 1.5) || (unit.target != UINT_MAX && distanceFromLoopedUnit < distanceWithCurrentTarget)) // If number here is still a raw float, please change it and implement the length with float attackRange! 
            {
                unit.target = entity;
                auto& newTargetTransform = coordinator.GetComponent<Transform>(unit.target);
                distanceWithCurrentTarget = glm::length(transform.position - newTargetTransform.position);
            }
        }
    }
}

Entity UnitSystem::CreateUnit(Unit::UnitType type, Unit::UnitFaction faction, int level, Transform transform)
{
    if ((faction == Unit::PLAYER && numberOfPlayer > 500) || (faction == Unit::ENEMY && numberOfEnemies > 500))
    {
        std::cout << "Failed to create new unit due to too many existing units!" << std::endl;
        return UINT_MAX;
    }

    Entity inactiveID = objectpoolsystem->FetchEntityFromPool(Tag::UNIT);

    auto& UnitTransform = coordinator.GetComponent<Transform>(inactiveID);
    auto& UnitCollider = coordinator.GetComponent<Collider>(inactiveID);
    auto& UnitData = coordinator.GetComponent<Unit>(inactiveID);
    auto& UnitRenderData = coordinator.GetComponent<RenderData>(inactiveID);

    switch (type)
    {
    case Unit::DEFAULT:
        std::cout << "UnitSystem: " << inactiveID << " initiated as DEFAULT type" << std::endl;
        break;
    case Unit::NORMAL:
        UnitData = UNormal(level, faction);
        if (faction == Unit::PLAYER)
        {
			UnitRenderData.mesh = renderer.getMesh(GEO_UNIT_NORMAL_PLAYER);
        }
        else
        {
            UnitRenderData.mesh = renderer.getMesh(GEO_UNIT_NORMAL_ENEMY);
        }
        std::cout << "UnitSystem: " << inactiveID << " initiated as NORMAL type" << std::endl;
        break;
    case Unit::TANK:
        UnitData = UTank(level, faction);
        if (faction == Unit::PLAYER)
        {
            UnitRenderData.mesh = renderer.getMesh(GEO_UNIT_TANK_PLAYER);
        }
        else
        {
            UnitRenderData.mesh = renderer.getMesh(GEO_UNIT_TANK_ENEMY);
        }
        std::cout << "UnitSystem: " << inactiveID << " initiated as TANK type" << std::endl;
        break;
    case Unit::RANGE:
        UnitRenderData.mesh = renderer.getMesh(GEO_GRIDCUBE);
        UnitData = URange(level, faction);
        if (faction == Unit::PLAYER)
        {
            UnitRenderData.mesh = renderer.getMesh(GEO_UNIT_RANGE_PLAYER);
        }
        else
        {
            UnitRenderData.mesh = renderer.getMesh(GEO_UNIT_RANGE_ENEMY);
        }
        std::cout << "UnitSystem: " << inactiveID << " initiated as RANGE type" << std::endl;
        break;
    case Unit::TOWER:
        UnitData = UTower(level, faction);
        if (faction == Unit::PLAYER)
        {
            UnitRenderData.mesh = renderer.getMesh(GEO_UNIT_TOWER_PLAYER);
        }
        else
        {
            UnitRenderData.mesh = renderer.getMesh(GEO_UNIT_TOWER_ENEMY);
        }
        UnitData.FlowFieldCost = 500;
        std::cout << "UnitSystem: " << inactiveID << " initiated as TOWER type" << std::endl;
        break;
    case Unit::WALL:
        UnitData = UWall(level, faction);
        if (faction == Unit::PLAYER)
        {
            UnitRenderData.mesh = renderer.getMesh(GEO_UNIT_WALL_PLAYER);
        }
        else
        {
            UnitRenderData.mesh = renderer.getMesh(GEO_UNIT_WALL_ENEMY);
        }
        UnitData.FlowFieldCost = 500;
        std::cout << "UnitSystem: " << inactiveID << " initiated as WALL type" << std::endl;
        break;
    case Unit::NEXUS:
        UnitData = UNexus(level, faction);
        if (faction == Unit::PLAYER)
        {
            UnitRenderData.mesh = renderer.getMesh(GEO_UNIT_NEXUS_PLAYER);
        }
        else
        {
            UnitRenderData.mesh = renderer.getMesh(GEO_UNIT_NEXUS_ENEMY);
        }
        UnitData.FlowFieldCost = 500;
        std::cout << "UnitSystem: " << inactiveID << " initiated as NEXUS type" << std::endl;
        break;
    case Unit::GENERATOR1:
        UnitData = UGenerator1(level, faction);
        if (faction == Unit::PLAYER)
        {
            UnitRenderData.mesh = renderer.getMesh(GEO_UNIT_GENERATOR1_PLAYER);
        }
        else
        {
            UnitRenderData.mesh = renderer.getMesh(GEO_UNIT_GENERATOR1_ENEMY);
        }
        UnitData.FlowFieldCost = 500;
        std::cout << "UnitSystem: " << inactiveID << " initiated as GENERATOR1 type" << std::endl;
        break;
    case Unit::GENERATOR2:
        UnitData = UGenerator2(level, faction);
        if (faction == Unit::PLAYER)
        {
            UnitRenderData.mesh = renderer.getMesh(GEO_UNIT_GENERATOR2_PLAYER);
        }
        else
        {
            UnitRenderData.mesh = renderer.getMesh(GEO_UNIT_GENERATOR2_ENEMY);
        }
        UnitData.FlowFieldCost = 500;
        std::cout << "UnitSystem: " << inactiveID << " initiated as GENERATOR2 type" << std::endl;
        break;
    case Unit::LAB:
        UnitData = ULab(level, faction);
        if (faction == Unit::PLAYER)
        {
            UnitRenderData.mesh = renderer.getMesh(GEO_LAB_PLAYER);
        }
        else
        {
            UnitRenderData.mesh = renderer.getMesh(GEO_LAB_ENEMY);
        }
        UnitData.FlowFieldCost = 500;
        std::cout << "UnitSystem: " << inactiveID << " initiated as LAB type" << std::endl;
        break;
    }

    UnitCollider.scale = UnitData.colliderScale;
    UnitCollider.mass = UnitData.mass;
    UnitTransform = transform;
    return inactiveID;
}

Entity UnitSystem::CreateProjectile(Entity origin, Entity target)
{
    Entity inactiveID = objectpoolsystem->FetchEntityFromPool(Tag::UNIT);

    auto& UnitTransform = coordinator.GetComponent<Transform>(inactiveID);
    auto& UnitCollider = coordinator.GetComponent<Collider>(inactiveID);
    auto& UnitData = coordinator.GetComponent<Unit>(inactiveID);
    auto& UnitRenderData = coordinator.GetComponent<RenderData>(inactiveID);

    auto& originTransform = coordinator.GetComponent<Transform>(origin);
    auto& originCollider = coordinator.GetComponent<Collider>(origin);
    auto& originUnit = coordinator.GetComponent<Unit>(origin);

    auto& targetTransform = coordinator.GetComponent<Transform>(target);
    auto& targetCollider = coordinator.GetComponent<Collider>(target);
    auto& targetUnit = coordinator.GetComponent<Unit>(target);

    if (originUnit.unitType == Unit::RANGE)
    {
        UnitData = UProjectile(origin, target);
        UnitData.unitFaction = originUnit.unitFaction;
        UnitCollider.mass = UnitData.mass;
        UnitCollider.scale = UnitData.colliderScale;
        std::cout << "UnitSystem: " << inactiveID << " initiated as PROJECTILE type" << std::endl;

        if (originUnit.unitFaction == Unit::PLAYER)
        {
            UnitRenderData.mesh = renderer.getMesh(GEO_PROJECTILE_PLAYER);
        }
        else
        {
            UnitRenderData.mesh = renderer.getMesh(GEO_PROJECTILE_ENEMY);
        }

        UnitTransform = Transform(originTransform.position + originTransform.AxisZ, glm::vec3(0.25, 0.25, 0.25), glm::vec3(0, 0, 0), TRANSFORM_TYPE::DYNAMIC_TRANSFORM);
    }
    else if (originUnit.unitType == Unit::TOWER)
    {
        UnitData = UProjectile(origin, target);
        UnitData.unitFaction = originUnit.unitFaction;
        UnitCollider.mass = UnitData.mass;
        UnitCollider.scale = UnitData.colliderScale;
        std::cout << "UnitSystem: " << inactiveID << " initiated as PROJECTILE type" << std::endl;

        if (originUnit.unitFaction == Unit::PLAYER)
        {
            UnitRenderData.mesh = renderer.getMesh(GEO_PROJECTILE_PLAYER);
        }
        else
        {
            UnitRenderData.mesh = renderer.getMesh(GEO_PROJECTILE_ENEMY);
        }

        UnitTransform = Transform(originTransform.position + originTransform.scale.y / 2, glm::vec3(0.25, 0.25, 0.25), glm::vec3(0, 0, 0), TRANSFORM_TYPE::DYNAMIC_TRANSFORM);
    }
    else
    {
        UnitData = UMeleeProjectile(origin, target);
        UnitData.unitFaction = originUnit.unitFaction;
        UnitCollider.mass = UnitData.mass;
        UnitCollider.scale = UnitData.colliderScale;
        UnitData.delay = d_elapsedTime + (1.0 / originUnit.attackSpeed) / 2;

        if (originUnit.unitFaction == Unit::PLAYER)
        {
            UnitRenderData.mesh = renderer.getMesh(GEO_PROJECTILE_MELEE_PLAYER);
        }
        else
        {
            UnitRenderData.mesh = renderer.getMesh(GEO_PROJECTILE_MELEE_ENEMY);
        }

        std::cout << "UnitSystem: " << inactiveID << " initiated as MELEE_PROJECTILE type" << std::endl;
        
        glm::vec3 relativePos = targetTransform.position - originTransform.position;
        float magnitude = glm::length(relativePos);
        glm::vec3 projectilePos = originTransform.position + relativePos * glm::vec3(0.5, 0.5, 0.5);

        UnitTransform = Transform(projectilePos, glm::vec3(magnitude, 0.2, 0.2), glm::vec3(0, originTransform.rotation.y, 0), TRANSFORM_TYPE::DYNAMIC_TRANSFORM);
    }

    return inactiveID;
}

void UnitSystem::ApplyAttack(Entity attacker, Entity receiver)
{
    auto& attackerTransform = coordinator.GetComponent<Transform>(attacker);
    auto& attackerUnit = coordinator.GetComponent<Unit>(attacker);

    auto& receiverTransform = coordinator.GetComponent<Transform>(receiver);
    auto& receiverUnit = coordinator.GetComponent<Unit>(receiver);

    if (receiverUnit.unitType == Unit::PROJECTILE || attackerUnit.unitType == Unit::MELEE_PROJECTILE || receiverUnit.unitType == Unit::MELEE_PROJECTILE || attackerUnit.isPreview || receiverUnit.isPreview) // In the event a unit targets a projectile, by right shouldnt happen but just incase it gets called
        return;

    if (attackerUnit.unitType == Unit::NORMAL || attackerUnit.unitType == Unit::TANK || attackerUnit.unitType == Unit::RANGE)
    {
        glm::vec3 dir = glm::normalize(attackerTransform.position - receiverTransform.position);
        attackerTransform.rotation.y = Math::RadianToDegree(atan2f(dir.x, dir.z)) - 90;
    }

    if (attackerUnit.unitType == Unit::TOWER)
    {
        glm::vec3 dir = glm::normalize(attackerTransform.position - receiverTransform.position);
        attackerTransform.rotation.y = Math::RadianToDegree(atan2f(dir.x, dir.z)) - 180;
    }

    if (attackerUnit.unitType == Unit::PROJECTILE)
    {
        auto& originTransform = coordinator.GetComponent<Transform>(attackerUnit.originUnit);
        auto& originUnit = coordinator.GetComponent<Unit>(attackerUnit.originUnit);

        float resultantDamage = ((100 - receiverUnit.defense) / 100) * originUnit.damage;
        receiverUnit.health -= resultantDamage;

        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << "UnitSystem: EntityID(" << attackerUnit.originUnit << ")'s projectile attacked EntityID(" << receiver << ")" << std::endl;
        std::cout << "UnitSystem: EntityID(" << attackerUnit.originUnit << ")'s projectile dealt raw damage(" << originUnit.damage << ") and EntityID(" << receiver << ") received resultant mitigated damage(" << resultantDamage << ")" << std::endl;
        return;
    }

    if (d_elapsedTime >= attackerUnit.delay)
    {
        if (attackerUnit.unitType == Unit::NORMAL || attackerUnit.unitType == Unit::TANK)
        {
            cSoundController->SetSoundSourcePosition(20, attackerTransform.position.x, attackerTransform.position.y, attackerTransform.position.z);
            cSoundController->PlaySoundByID(20);
            CreateProjectile(attacker, receiver);
            float resultantDamage = ((100 - receiverUnit.defense) / 100) * attackerUnit.damage;
            receiverUnit.health -= resultantDamage;
            std::cout << "------------------------------------------------------------" << std::endl;
            std::cout << "UnitSystem: EntityID(" << attacker << ") attacked EntityID(" << receiver << ")" << std::endl;
            std::cout << "UnitSystem: EntityID(" << attacker << ") dealt raw damage(" << attackerUnit.damage << ") and EntityID(" << receiver << ") received resultant mitigated damage(" << resultantDamage << ")" << std::endl;
            attackerUnit.delay = d_elapsedTime + (1.0 / attackerUnit.attackSpeed);
        }

        if (attackerUnit.unitType == Unit::RANGE || attackerUnit.unitType == Unit::TOWER)
        {
            if (attackerUnit.unitType == Unit::RANGE)
            {
                cSoundController->SetSoundSourcePosition(21, attackerTransform.position.x, attackerTransform.position.y, attackerTransform.position.z);
                cSoundController->PlaySoundByID(21);
            }
            else
            {
                cSoundController->SetSoundSourcePosition(22, attackerTransform.position.x, attackerTransform.position.y, attackerTransform.position.z);
                cSoundController->PlaySoundByID(22);
            }

            CreateProjectile(attacker, receiver);
        }

        attackerUnit.delay = d_elapsedTime + (1.0 / attackerUnit.attackSpeed); // Adds in the resultant delay after inclusion of attackSpeed

        for (auto& const aientity : aiControllerEntity)
        {
            auto& aiEntityController = coordinator.GetComponent<AIController>(aientity);
            float unitSeverity = 0.5;
            float buildingSeverity = 1.5;
            float nexusSeverity = 5.0;

            if (receiverUnit.unitFaction == Unit::ENEMY)
            {
                if (receiverUnit.unitType == Unit::NORMAL || receiverUnit.unitType == Unit::TANK || receiverUnit.unitType == Unit::RANGE)
                {
                    aiEntityController.LogEvent(attackerTransform.position, unitSeverity);
                }
                else if (receiverUnit.unitType == Unit::NEXUS)
                {
                    aiEntityController.LogEvent(attackerTransform.position, nexusSeverity);
                }
                else
                {
                    aiEntityController.LogEvent(attackerTransform.position, buildingSeverity);
                }
            }
        }
    }

}

void UnitSystem::UpdateProjectile(Entity projectile)
{
    auto& UnitTransform = coordinator.GetComponent<Transform>(projectile);
    auto& UnitData = coordinator.GetComponent<Unit>(projectile);

    if (UnitData.unitType != Unit::PROJECTILE && UnitData.unitType != Unit::MELEE_PROJECTILE) // This method is specifically only for projectiles!
        return;

    auto& OriginTransform = coordinator.GetComponent<Transform>(UnitData.originUnit);
    auto& OriginUnitData = coordinator.GetComponent<Unit>(UnitData.originUnit);
    auto& OriginEntityState = coordinator.GetComponent<EntityState>(UnitData.originUnit);

    auto& TargetTransform = coordinator.GetComponent<Transform>(UnitData.targetUnit);
    auto& TargetUnitData = coordinator.GetComponent<Unit>(UnitData.targetUnit);
    auto& TargetEntityState = coordinator.GetComponent<EntityState>(UnitData.targetUnit);

    if (!TargetEntityState.active)
    {
        AddInactiveEntity(projectile);
        return;
    }

    if (UnitData.unitType == Unit::PROJECTILE)
    {
        glm::vec3 projectileDirection = glm::normalize(TargetTransform.position - UnitTransform.position);
        float projectileSpeed = 0.7f; // Can create a variable for this under unit

        UnitTransform.position += projectileDirection * projectileSpeed;
    }
    else if (UnitData.unitType == Unit::MELEE_PROJECTILE)
    {
        glm::vec3 relativePos = TargetTransform.position - OriginTransform.position;
        float magnitude = glm::length(relativePos);
        glm::vec3 projectilePos = OriginTransform.position + relativePos * glm::vec3(0.5, 0.5, 0.5);

        UnitTransform.position = projectilePos;
        UnitTransform.scale = glm::vec3(magnitude, 0.2, 0.2);
        UnitTransform.rotation = glm::vec3(0, OriginTransform.rotation.y, 0);

        if (d_elapsedTime >= UnitData.delay || !OriginEntityState.active)
        {
            AddInactiveEntity(projectile);
            return;
        }
    }


}

