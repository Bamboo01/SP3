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
        aicontroller.sortEventSeverity();
        int costbalance = aicontroller.unitlist.size();

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

        aicontroller.AIAggroTimer += dt;
        aicontroller.PlayerAggroTimer += dt;

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
        for (const auto& e : aicontroller.eventlist)
        {
            if (costbalance <= 0)
            {
                break;
            }
            float searchdist = 200.f / (1.f / e.severity);

            std::vector<Entity> selectedentities;

            for (const auto& entity : aicontroller.unitlist)
            {
                if (costbalance <= 0)
                {
                    break;
                }
                auto& transform = coordinator.GetComponent<Transform>(entity);
                if (glm::length(e.position - transform.position) < searchdist)
                {
                    selectedentities.push_back(entity);
                }
            }

            // GridController stuff here!
            // Make sure that if a unit is enroute to anything, SKIP it and process the next one

        }
        aicontroller.eventlist.clear();
        aicontroller.eventlist.shrink_to_fit();


        //Build order via final aggression amount
        if (aicontroller.TotalAggression > 1.f) 
        {
            // Offensive
            // Build a unit
            // Next, round up aggression counter, that is the number of units to send
            // Create a new vector of pairs, Entity and distance of said entity to enemy nexus. Sort it from smallest to highest.
            // Send those number of units to the enemy nexus
        }
        else 
        {
            // Defensive
            // If total aggression is between 0 and 1, build units
            // If total aggression is below 0, build turrets
            // Find a nice place to build it THEN build it. When turret is built, player aggression should reduce by 0.2f
        }
    }
}
