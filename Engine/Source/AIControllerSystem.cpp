#include "AIControllerSystem.h"

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

        aicontroller.normalunitcost = aicontroller.normalunitlevel * 50;
        aicontroller.rangeunitcost = aicontroller.rangeunitlevel * 100;
        aicontroller.tankunitcost = aicontroller.tankunitlevel * 150;
        aicontroller.normalunitcost2 = aicontroller.normalunitlevel * 40;
        aicontroller.rangeunitcost2 = aicontroller.rangeunitlevel * 80;
        aicontroller.tankunitcost2 = aicontroller.tankunitlevel * 110;
        aicontroller.levelupnormalcost = aicontroller.normalunitlevel * 30;
        aicontroller.leveluprangecost = aicontroller.rangeunitlevel * 130;
        aicontroller.leveluptankcost = aicontroller.tankunitlevel * 200;
        aicontroller.levelupnormalcost2 = aicontroller.normalunitlevel * 70;
        aicontroller.leveluprangecost2 = aicontroller.rangeunitlevel * 120;
        aicontroller.leveluptankcost2 = aicontroller.tankunitlevel * 160;

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
                aicontroller.gridcontrollersystem->UpdateEnemyGridCost(e.position, selectedentities);
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
                }
                else if (aicontroller.resource1 > 100.f)
                {
                    //Build Ranged
                }
                else if (aicontroller.resource1 > 30.f)
                {
                    //Build normal
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
                //Send those units to attack, select 2 units and send to grid function, position is player nexus
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

                    }
                    else
                    {
                        if (aicontroller.resource1 > 150.f)
                        {
                            //Build tank
                        }
                        else if (aicontroller.resource1 > 100.f)
                        {
                            //Build Ranged
                        }
                        else if (aicontroller.resource1 > 30.f)
                        {
                            //Build normal
                        }
                    }
                }
                else
                {
                    //Build Generators
                    if (aicontroller.resource1 > 160.f)
                    {
                        if (aicontroller.numGen1 > 3)
                        {
                            //build generator 2
                        }
                        else
                        {
                            //build generator 1
                        }
                    }
                    else
                    {
                        if (aicontroller.resource1 > 150.f)
                        {
                            //Build tank
                        }
                        else if (aicontroller.resource1 > 100.f)
                        {
                            //Build Ranged
                        }
                        else if (aicontroller.resource1 > 30.f)
                        {
                            //Build normal
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
                }
            }
        }

        //Process the collection of resources from ALL generators
    }
}
