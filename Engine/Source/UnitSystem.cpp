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

void UnitSystem::Init()
{
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

    for (auto const& entity : m_Entities)
    {
        auto& transform = coordinator.GetComponent<Transform>(entity);
        auto& unit = coordinator.GetComponent<Unit>(entity);
        auto& entityState = coordinator.GetComponent<EntityState>(entity);

        if (unit.health <= 0) // In the event the unit's health falls to/below 0, deactivate the unit.
        {
            AddInactiveEntity(entity);
            continue;
        }

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
        case Unit::PROJECTILE:
            UpdateProjectile(entity);
            break;
        }

        if (unit.target != UINT_MAX && unit.unitType != Unit::PROJECTILE)
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

    if (unit.unitType == Unit::UnitType::WALL || unit.unitType == Unit::UnitType::NEXUS || unit.unitType == Unit::UnitType::GENERATOR1 || unit.unitType == Unit::UnitType::GENERATOR2 || unit.unitType == Unit::UnitType::LAB || unit.unitType == Unit::UnitType::PROJECTILE) // These shouldn't call this method!
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

        if (distanceWithCurrentTarget > 150)
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

            if ((unit.target == UINT_MAX && distanceFromLoopedUnit <= 150.f) || (unit.target != UINT_MAX && distanceFromLoopedUnit < distanceWithCurrentTarget)) // If number here is still a raw float, please change it and implement the length with float attackRange! 
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
        UnitRenderData.mesh = renderer.getMesh(GEO_CUBE);
        std::cout << "UnitSystem: " << inactiveID << " initiated as NORMAL type" << std::endl;
        break;
    case Unit::TANK:
        UnitData = UTank(level, faction);
        std::cout << "UnitSystem: " << inactiveID << " initiated as TANK type" << std::endl;
        break;
    case Unit::RANGE:
        UnitRenderData.mesh = renderer.getMesh(GEO_GRIDCUBE);
        UnitData = URange(level, faction);
        std::cout << "UnitSystem: " << inactiveID << " initiated as RANGE type" << std::endl;
        break;
    case Unit::TOWER:
        UnitData = UTower(level, faction);
        std::cout << "UnitSystem: " << inactiveID << " initiated as TOWER type" << std::endl;
        break;
    case Unit::WALL:
        UnitData = UWall(level, faction);
        std::cout << "UnitSystem: " << inactiveID << " initiated as WALL type" << std::endl;
        break;
    case Unit::NEXUS:
        UnitData = UNexus(level, faction);
        std::cout << "UnitSystem: " << inactiveID << " initiated as NEXUS type" << std::endl;
        break;
    case Unit::GENERATOR1:
        UnitData = UGenerator1(level, faction);
        std::cout << "UnitSystem: " << inactiveID << " initiated as GENERATOR1 type" << std::endl;
        break;
    case Unit::GENERATOR2:
        UnitData = UGenerator2(level, faction);
        std::cout << "UnitSystem: " << inactiveID << " initiated as GENERATOR2 type" << std::endl;
        break;
    case Unit::LAB:
        UnitData = ULab(level, faction);
        std::cout << "UnitSystem: " << inactiveID << " initiated as LAB type" << std::endl;
        break;
    case Unit::PROJECTILE:
        break;
    default:
        std::cout << "UnitSystem: Unable to init " << inactiveID << " due to undefined unit type" << std::endl;
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

    UnitData = UProjectile(origin, target);
    UnitData.unitFaction = originUnit.unitFaction;
    UnitCollider.mass = UnitData.mass;
    UnitCollider.scale = UnitData.colliderScale;
    std::cout << "UnitSystem: " << inactiveID << " initiated as PROJECTILE type" << std::endl;

    if (originUnit.unitType == Unit::RANGE)
    {
        UnitRenderData.mesh = renderer.getMesh(GEO_CUBE);
        UnitTransform = Transform(originTransform.position + originTransform.AxisZ, glm::vec3(0.5, 0.5, 0.5), glm::vec3(0, 0, 0), TRANSFORM_TYPE::DYNAMIC_TRANSFORM);
    }
    else if (originUnit.unitType == Unit::TOWER)
    {

    }
    return inactiveID;
}

void UnitSystem::ApplyAttack(Entity attacker, Entity receiver)
{
    auto& attackerTransform = coordinator.GetComponent<Transform>(attacker);
    auto& attackerUnit = coordinator.GetComponent<Unit>(attacker);

    auto& receiverTransform = coordinator.GetComponent<Transform>(receiver);
    auto& receiverUnit = coordinator.GetComponent<Unit>(receiver);

    if (receiverUnit.unitType == Unit::PROJECTILE) // In the event a unit targets a projectile, by right shouldnt happen but just incase it gets called
        return;

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
            float resultantDamage = ((100 - receiverUnit.defense) / 100) * attackerUnit.damage;
            receiverUnit.health -= resultantDamage;
            std::cout << "------------------------------------------------------------" << std::endl;
            std::cout << "UnitSystem: EntityID(" << attacker << ") attacked EntityID(" << receiver << ")" << std::endl;
            std::cout << "UnitSystem: EntityID(" << attacker << ") dealt raw damage(" << attackerUnit.damage << ") and EntityID(" << receiver << ") received resultant mitigated damage(" << resultantDamage << ")" << std::endl;
            attackerUnit.delay = d_elapsedTime + (1.0 / attackerUnit.attackSpeed);
        }

        if (attackerUnit.unitType == Unit::RANGE)
        {
            CreateProjectile(attacker, receiver);
        }

        attackerUnit.delay = d_elapsedTime + (1.0 / attackerUnit.attackSpeed); // Adds in the resultant delay after inclusion of attackSpeed
    }

}

void UnitSystem::UpdateProjectile(Entity projectile)
{
    auto& UnitTransform = coordinator.GetComponent<Transform>(projectile);
    auto& UnitData = coordinator.GetComponent<Unit>(projectile);

    if (UnitData.unitType != Unit::PROJECTILE) // This method is specifically only for projectiles!
        return;

    auto& TargetTransform = coordinator.GetComponent<Transform>(UnitData.targetUnit);
    auto& TargetUnitData = coordinator.GetComponent<Unit>(UnitData.targetUnit);
    auto& TargetEntityState = coordinator.GetComponent<EntityState>(UnitData.targetUnit);

    if (!TargetEntityState.active)
    {
        AddInactiveEntity(projectile);
        return;
    }

    glm::vec3 projectileDirection = glm::normalize(TargetTransform.position - UnitTransform.position);
    float projectileSpeed = 1.f; // Can create a variable for this under unit

    UnitTransform.position += projectileDirection * projectileSpeed;
}

