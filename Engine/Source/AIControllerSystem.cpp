#include "AIControllerSystem.h"
#include <gtc/random.hpp>

void AIControllerSystem::Setup()
{
    Signature signature;
    signature.set(coordinator.GetComponentType<AIController>());
    signature.set(coordinator.GetComponentType<EntityState>());
    coordinator.SetSystemSignature<AIControllerSystem>(signature);
}

void AIControllerSystem::Init()
{

}

void AIControllerSystem::Update(float dt)
{
    for (auto& entity : m_Entities)
    {
        auto& aicontroller = coordinator.GetComponent<AIController>(entity);

        aicontroller.ProcessEventsTimer += dt;
        aicontroller.AIAggroTimer += dt;
        aicontroller.PlayerAggroTimer += dt;
        aicontroller.ProcessTacticsTimer += dt;

        aicontroller.normalunitcost = aicontroller.normalunitlevel * 40;
        aicontroller.rangeunitcost = aicontroller.rangeunitlevel * 60;
        aicontroller.tankunitcost = aicontroller.tankunitlevel * 90;
        aicontroller.normalunitcost2 = aicontroller.normalunitlevel * 30;
        aicontroller.rangeunitcost2 = aicontroller.rangeunitlevel * 50;
        aicontroller.tankunitcost2 = aicontroller.tankunitlevel * 80;
        aicontroller.levelupnormalcost = aicontroller.normalunitlevel * 30;
        aicontroller.leveluprangecost = aicontroller.rangeunitlevel * 70;
        aicontroller.leveluptankcost = aicontroller.tankunitlevel * 100;
        aicontroller.levelupnormalcost2 = aicontroller.normalunitlevel * 40;
        aicontroller.leveluprangecost2 = aicontroller.rangeunitlevel * 100;
        aicontroller.leveluptankcost2 = aicontroller.tankunitlevel * 150;

        if (aicontroller.AIAggroTimer > 20.f)
        {
            aicontroller.AIAggression += 1.f;
            aicontroller.AIAggroTimer = 0.f;

            if (aicontroller.AIAggression > 5.f)
            {
                aicontroller.AIAggression = 5.f;
            }
        }

        if (aicontroller.PlayerAggroTimer > 30.f)
        {
            aicontroller.PlayerAggression -= 1.5f;
            aicontroller.PlayerAggroTimer = 0.f;

            if (aicontroller.AIAggression > 6.f)
            {
                aicontroller.AIAggression = 6.f;
            }
        }

        aicontroller.TotalAggression = aicontroller.AIAggression - aicontroller.PlayerAggression;

        //Movement of units via events
        if (aicontroller.ProcessEventsTimer > 1.f)
        {
            aicontroller.sortEventSeverity();
            aicontroller.ProcessEventsTimer = 0.f;

            for (const auto& e : aicontroller.eventlist)
            {
                float searchdist = 200.f / (1.f / e.severity);

                std::vector<Entity> selectedentities;

                for (const auto& entity : aicontroller.unitlist)
                {
                    auto& transform = coordinator.GetComponent<Transform>(entity);
                    if (glm::length(e.position - transform.position) < searchdist)
                    {
                        selectedentities.push_back(entity);
                    }
                }

                // GridController stuff here!
                aicontroller.gridcontrollersystem->UpdateEnemyGridCost(e.position, selectedentities, true,dt);
                // Make sure that if a unit is enroute to anything, SKIP it and process the next one

            }
            aicontroller.eventlist.clear();
            aicontroller.eventlist.shrink_to_fit();
        }

        //Build order via final aggression amount
        if (aicontroller.ProcessTacticsTimer > 10.f)
        {
            aicontroller.ProcessTacticsTimer = 0.f;

            if (aicontroller.TotalAggression > 1.f)
            {
                // Offensive
                // Build a unit
                // Next, round up aggression counter, that is the number of units to send
                // Create a new vector of pairs, Entity and distance of said entity to enemy nexus. Sort it from smallest to highest.
                // Send those number of units to the enemy nexus
                if (aicontroller.resource1 > 150.f)
                {
                    //Build tank
                    aicontroller.resource1 -= aicontroller.tankunitcost;
                    unitsystem->CreateUnit(Unit::TANK, Unit::ENEMY, aicontroller.tankunitlevel, Transform(glm::vec3(-130, 0, -160), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), DYNAMIC_TRANSFORM));
                }
                else if (aicontroller.resource1 > 100.f)
                {
                    //Build Ranged
                    aicontroller.resource1 -= aicontroller.rangeunitcost;
                    unitsystem->CreateUnit(Unit::RANGE, Unit::ENEMY, aicontroller.rangeunitlevel, Transform(glm::vec3(-130, 0, -160), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), DYNAMIC_TRANSFORM));
                }
                else if (aicontroller.resource1 > 30.f)
                {
                    //Build normal
                    aicontroller.resource1 -= aicontroller.normalunitcost;
                    unitsystem->CreateUnit(Unit::NORMAL, Unit::ENEMY, aicontroller.normalunitlevel, Transform(glm::vec3(-130, 0, -160), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), DYNAMIC_TRANSFORM));
                }

                int attackingUnits = std::ceil(aicontroller.TotalAggression);

                std::vector<std::pair<Entity, float>> EntitiesToNexus;
                for (auto a : aicontroller.unitlist)
                {
                    auto& transform = coordinator.GetComponent<Transform>(a);
                    float dist = (glm::length(transform.position - aicontroller.targetNexusPosition));
                    EntitiesToNexus.push_back(std::make_pair(a, dist));
                }
                std::sort(EntitiesToNexus.begin(), EntitiesToNexus.end(), [](const std::pair<Entity, float>& a, const std::pair<Entity, float>& b) { return a.second < b.second; });
                //Send those units to attack, select those few units and send to grid function, position is player nexus
                std::vector<Entity> selectedEntity;
                for (auto a : EntitiesToNexus)
                {
                    auto& units = coordinator.GetComponent<Unit>(a.first);
                    auto& transform = coordinator.GetComponent<Transform>(a.first);
                    if (selectedEntity.size() >= aicontroller.AIAggression)
                    {
                        break;
                    }
                    if (((units.unitType == Unit::NORMAL) || (units.unitType == Unit::RANGE) || (units.unitType == Unit::TANK)) && (units.unitFaction == Unit::ENEMY) )
                    {
                        selectedEntity.push_back(a.first);
                    }
                }
                aicontroller.gridcontrollersystem->UpdateEnemyGridCost(aicontroller.targetNexusPosition, selectedEntity, false,dt);
                
            }
            else if (aicontroller.TotalAggression > 0.f)
            {
                // Semi-Defensive
                // If number of gen1 > 3 and gen2 > 2
                    //Level up unit based on current resources.
                        //Check which units are available for leveling up
                    //Else, build one unit
                // Else, Build Generators
                if (aicontroller.numGen1 > 3 && aicontroller.numGen2 > 2)
                {
                    if (aicontroller.resource1 > aicontroller.leveluprangecost)
                    {
                        // Level up normal units
                        if (aicontroller.resource1 > aicontroller.levelupnormalcost)
                        {
                            std::cout << "ENEMY NORMAL LEVEL UP! " << std::endl;
                            if (aicontroller.normalunitlevel <= 3)
                            {
                                aicontroller.normalunitlevel++;
                                aicontroller.resource1 -= aicontroller.levelupnormalcost;
                            }
                            else if (aicontroller.normalunitlevel > 3 && aicontroller.resource2 > aicontroller.levelupnormalcost2)
                            {
                                aicontroller.normalunitlevel++;
                                aicontroller.resource1 -= aicontroller.levelupnormalcost;
                                aicontroller.resource2 -= aicontroller.levelupnormalcost2;
                            }

                        }
                        // Level up range units
                        else if (aicontroller.resource1 > aicontroller.leveluprangecost)
                        {
                            std::cout << "ENEMY RANGE LEVEL UP! " << std::endl;
                            if (aicontroller.rangeunitlevel <= 3)
                            {
                                aicontroller.rangeunitlevel++;
                                aicontroller.resource1 -= aicontroller.leveluprangecost;
                            }
                            else if (aicontroller.rangeunitlevel > 3 && aicontroller.resource2 > aicontroller.leveluprangecost2)
                            {
                                aicontroller.rangeunitlevel++;
                                aicontroller.resource1 -= aicontroller.leveluprangecost;
                                aicontroller.resource2 -= aicontroller.leveluprangecost2;
                            }
                        }
                        // Level up tank units
                        else if (aicontroller.resource1 > aicontroller.leveluptankcost)
                        {
                            std::cout << "ENEMY TANK LEVEL UP! " << std::endl;
                            if (aicontroller.tankunitlevel <= 3)
                            {
                                aicontroller.tankunitlevel++;
                                aicontroller.resource1 -= aicontroller.leveluptankcost;
                            }
                            else if (aicontroller.tankunitlevel > 3 && aicontroller.resource2 > aicontroller.leveluptankcost2)
                            {
                                aicontroller.tankunitlevel++;
                                aicontroller.resource1 -= aicontroller.leveluptankcost;
                                aicontroller.resource2 -= aicontroller.leveluptankcost2;
                            }
                        }

                    }
                    else
                    {
                        if (aicontroller.resource1 > 150.f)
                        {
                            //Build tank
                            aicontroller.resource1 -= aicontroller.tankunitcost;
                            unitsystem->CreateUnit(Unit::TANK, Unit::ENEMY, aicontroller.tankunitlevel, Transform(glm::vec3(-130, 0, -160), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), DYNAMIC_TRANSFORM));
                        }
                        else if (aicontroller.resource1 > 100.f)
                        {
                            //Build Ranged
                            aicontroller.resource1 -= aicontroller.rangeunitcost;
                            unitsystem->CreateUnit(Unit::RANGE, Unit::ENEMY, aicontroller.rangeunitlevel, Transform(glm::vec3(-130, 0, -160), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), DYNAMIC_TRANSFORM));
                        }
                        else if (aicontroller.resource1 > 30.f)
                        {
                            //Build normal
                            aicontroller.resource1 -= aicontroller.normalunitcost;
                            unitsystem->CreateUnit(Unit::NORMAL, Unit::ENEMY, aicontroller.normalunitlevel, Transform(glm::vec3(-130, 0, -160), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), DYNAMIC_TRANSFORM));
                        }
                    }
                }
                else
                {
                    //Build Generators
                    if (aicontroller.resource1 > 160.f)
                    {
                        if (aicontroller.numGen1 > 5)
                        {
                            //build generator 2
                            bool found = false;
                            while (!found)
                            {
                                glm::vec2 randomxz = glm::diskRand(200.f);
                                glm::vec3 positiontoplace = glm::vec3(aicontroller.nexusposition.x + randomxz.x, aicontroller.nexusposition.y, aicontroller.nexusposition.z + randomxz.y);

                                // Check if it's within the terrain
                                if (positiontoplace.x > -200 && positiontoplace.x < 200 && positiontoplace.z > -200 && positiontoplace.z < 200)
                                {
                                    for (int i = 0; i < aicontroller.unitlist.size(); ++i)
                                    {
                                        Entity temp = aicontroller.unitlist[i];
                                        auto& transformbuilding = coordinator.GetComponent<Transform>(temp);

                                        if (glm::length(transformbuilding.position - positiontoplace) > 100)
                                        {
                                            aicontroller.resource1 -= aicontroller.generator2cost;
                                            unitsystem->CreateUnit(Unit::GENERATOR2, Unit::ENEMY, 1, Transform(positiontoplace, glm::vec3(2, 2, 2), glm::vec3(0, 0, 0), DYNAMIC_TRANSFORM));
                                            found = true;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            bool found = false;
                            while (!found)
                            {
                                glm::vec2 randomxz = glm::diskRand(200.f);
                                glm::vec3 positiontoplace = glm::vec3(aicontroller.nexusposition.x + randomxz.x, aicontroller.nexusposition.y, aicontroller.nexusposition.z + randomxz.y);

                                // Check if it's within the terrain
                                if (positiontoplace.x > -200 && positiontoplace.x < 200 && positiontoplace.z > -200 && positiontoplace.z < 200)
                                {
                                    for (int i = 0; i < aicontroller.unitlist.size(); ++i)
                                    {
                                        Entity temp = aicontroller.unitlist[i];
                                        auto& transformbuilding = coordinator.GetComponent<Transform>(temp);

                                        if (glm::length(transformbuilding.position - positiontoplace) > 100)
                                        {
                                            aicontroller.resource1 -= aicontroller.generator1cost;
                                            unitsystem->CreateUnit(Unit::GENERATOR1, Unit::ENEMY, 1, Transform(positiontoplace, glm::vec3(2, 2, 2), glm::vec3(0, 0, 0), DYNAMIC_TRANSFORM));
                                            found = true;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        if (aicontroller.resource1 > 150.f)
                        {
                            //Build tank
                            aicontroller.resource1 -= aicontroller.tankunitcost;
                            unitsystem->CreateUnit(Unit::TANK, Unit::ENEMY, aicontroller.tankunitlevel, Transform(glm::vec3(-130, 0, -160), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), DYNAMIC_TRANSFORM));
                        }
                        else if (aicontroller.resource1 > 100.f)
                        {
                            //Build Ranged
                            aicontroller.resource1 -= aicontroller.rangeunitcost;
                            unitsystem->CreateUnit(Unit::RANGE, Unit::ENEMY, aicontroller.rangeunitlevel, Transform(glm::vec3(-130, 0, -160), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), DYNAMIC_TRANSFORM));
                        }
                        else if (aicontroller.resource1 > 30.f)
                        {
                            //Build normal
                            aicontroller.resource1 -= aicontroller.normalunitcost;
                            unitsystem->CreateUnit(Unit::NORMAL, Unit::ENEMY, aicontroller.normalunitlevel, Transform(glm::vec3(-130, 0, -160), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), DYNAMIC_TRANSFORM));
                        }
                    }
                }
            }
            else
            {
                // Full-Defensive
                // Build turrets
                // Find a nice place to build it THEN build it. When turret is built, player aggression should reduce by 0.2f
                if (aicontroller.resource1 > 250.f)
                {
                    //Build turret
                    bool found = false;
                    while (!found)
                    {
                        glm::vec2 randomxz = glm::diskRand(200.f);
                        glm::vec3 positiontoplace = glm::vec3(aicontroller.nexusposition.x + randomxz.x, aicontroller.nexusposition.y, aicontroller.nexusposition.z + randomxz.y);

                        // Check if it's within the terrain
                        if (positiontoplace.x > -200 && positiontoplace.x < 200 && positiontoplace.z > -200 && positiontoplace.z < 200)
                        {
                            for (int i = 0; i < aicontroller.unitlist.size(); ++i)
                            {
                                Entity temp = aicontroller.unitlist[i];
                                auto& transformbuilding = coordinator.GetComponent<Transform>(temp);

                                if (glm::length(transformbuilding.position - positiontoplace) > 100)
                                {
                                    aicontroller.resource1 -= aicontroller.towercost;
                                    unitsystem->CreateUnit(Unit::TOWER, Unit::ENEMY, 1, Transform(positiontoplace, glm::vec3(2, 2, 2), glm::vec3(0, 0, 0), DYNAMIC_TRANSFORM));
                                    found = true;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }

        //Process the collection of resources from ALL generators

        for (const auto& entity : aicontroller.unitlist)
        {
            auto& unitData = coordinator.GetComponent<Unit>(entity);
            
            if (unitData.resourcesgenerated != 0)
            {
                if (unitData.unitType == Unit::GENERATOR1)
                {
                    aicontroller.resource1 += unitData.resourcesgenerated;
                    unitData.resourcesgenerated = 0;
                }
                else if (unitData.unitType == Unit::GENERATOR2)
                {
                    aicontroller.resource2 += unitData.resourcesgenerated;
                    unitData.resourcesgenerated = 0;
                }
            }
        }
    }
}

void AIControllerSystem::SetUnitSystem(std::shared_ptr<UnitSystem> system)
{
    this->unitsystem = system;
}
