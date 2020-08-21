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

    coordinator.SetSystemSignature<UnitSystem>(signature);
}

void UnitSystem::Init()
{
    for (auto const& entity : m_Entities)
    {
        auto& unit = coordinator.GetComponent<Unit>(entity);
        auto& transform = coordinator.GetComponent<Transform>(entity);

        glm::mat4 mrot(1.f);

        glm::vec3 rotation = glm::radians(transform.rotation);

        mrot = glm::mat4(1.f);
        mrot = glm::rotate(mrot, rotation.x, glm::vec3(1, 0, 0));
        mrot = glm::rotate(mrot, rotation.y, glm::vec3(0, 1, 0));
        mrot = glm::rotate(mrot, rotation.z, glm::vec3(0, 0, 1));

        transform.AxisX = glm::vec3(mrot * glm::vec4(1, 0, 0, 0.f));
        transform.AxisY = glm::vec3(mrot * glm::vec4(0, 1, 0, 0.f));
        transform.AxisZ = glm::vec3(mrot * glm::vec4(0, 0, 1, 0.f));
    }
}

void UnitSystem::Update(double dt)
{

}

Entity UnitSystem::FetchInactiveUnit()
{
    for (auto const& entity : m_Entities) // Checks through the entity list and search for the next inactive object
    {
        auto& unit = coordinator.GetComponent<Unit>(entity);
        if (!unit.active)
        {
            return entity;
        }
    }

    int numOfNewEntity = 20;
    Entity returnEntity;

    for (int i = 0; i < numOfNewEntity; i++) // If entity list does not have anymore inactive units, create 20 entities to store
    {
        Entity tempObject;
        tempObject = coordinator.CreateEntity();
        coordinator.AddComponent<Transform>(tempObject, Transform());
        coordinator.AddComponent<Collider>(tempObject, Collider());
        coordinator.AddComponent<RenderData>(tempObject, RenderData());
        coordinator.AddComponent<Unit>(tempObject, Unit());

        if (i == 0)
        {
            returnEntity = tempObject;
        }
    }

    return returnEntity;
}

void UnitSystem::FetchNearbyTargetWithinRange(Entity unitID)
{
    auto& transform = coordinator.GetComponent<Transform>(unitID);
    auto& unit = coordinator.GetComponent<Unit>(unitID);
    auto& currentTargetTransform = coordinator.GetComponent<Transform>(unit.target);
    auto& currentTargetUnit = coordinator.GetComponent<Unit>(unit.target);
    float distanceWithCurrentTarget = 0;

    if (unit.unitType == Unit::UnitType::WALL || unit.unitType == Unit::UnitType::NEXUS || unit.unitType == Unit::UnitType::GENERATOR || unit.unitType == Unit::UnitType::LAB || unit.unitType == Unit::UnitType::PROJECTILE) // These shouldn't call this method!
        return;

    Unit::UnitFaction targetFactionRequirement; // A variable to make sure the unit does not target it's own units

    if (unit.unitFaction == Unit::UnitFaction::PLAYER)
        targetFactionRequirement = Unit::UnitFaction::ENEMY;
    else if (unit.unitFaction == Unit::UnitFaction::ENEMY)
        targetFactionRequirement = Unit::UnitFaction::PLAYER;


    if (unit.target != UINT_MAX) // In the event there's a target entity stored
    {
        if (!currentTargetUnit.active) // If the target entity is not active, we set the unit->target back to default
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

        if (entity == unitID || !otherUnit.active) // If the for loops goes onto the same unit, skip this loop
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
    Entity inactiveID = FetchInactiveUnit();

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
        UnitRenderData.mesh = renderer.getMesh(GEO_CUBE);
        UnitData = UNormal(level, faction);
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
    case Unit::GENERATOR:
        UnitData = UGenerator(level, faction);
        std::cout << "UnitSystem: " << inactiveID << " initiated as GENERATOR type" << std::endl;
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
    Entity inactiveID = FetchInactiveUnit();

    auto& UnitTransform = coordinator.GetComponent<Transform>(inactiveID);
    auto& UnitCollider = coordinator.GetComponent<Collider>(inactiveID);
    auto& UnitData = coordinator.GetComponent<Unit>(inactiveID);

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

    if (originUnit.unitType == Unit::RANGE)
    {
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

    if (attackerUnit.unitType == Unit::PROJECTILE)
    {
        auto& originTransform = coordinator.GetComponent<Transform>(attackerUnit.originUnit);
        auto& originUnit = coordinator.GetComponent<Unit>(attackerUnit.originUnit);

        float resultantDamage = ((100 - receiverUnit.defense) / 100) * originUnit.damage;
        receiverUnit.health -= resultantDamage;

        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << "UnitSystem: EntityID(" << attackerUnit.originUnit << ")'s projectile attacked EntityID(" << receiver << ")" << std::endl;
        std::cout << "UnitSystem: EntityID(" << attackerUnit.originUnit << ")'s projectile dealt raw damage(" << originUnit.damage << ") and EntityID(" << receiver << ") received resultant mitigated damage(" << resultantDamage << ")" << std::endl;
        attackerUnit.active = false;
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
    auto& UnitCollider = coordinator.GetComponent<Collider>(projectile);
    auto& UnitData = coordinator.GetComponent<Unit>(projectile);

    if (UnitData.unitType != Unit::PROJECTILE)
        return;

    auto& TargetTransform = coordinator.GetComponent<Transform>(UnitData.targetUnit);
    auto& TargetCollider = coordinator.GetComponent<Collider>(UnitData.targetUnit);
    auto& TargetUnitData = coordinator.GetComponent<Unit>(UnitData.targetUnit);

    if (!TargetUnitData.active)
    {
        UnitData.active = false;
        return;
    }

    glm::vec3 projectileDirection = glm::normalize(TargetTransform.position - UnitTransform.position);
    float projectileSpeed = 1.f; // Can create a variable for this under unit

    UnitTransform.position += projectileDirection * projectileSpeed;
}

