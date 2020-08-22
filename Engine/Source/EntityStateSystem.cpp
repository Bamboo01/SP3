#include "EntityStateSystem.h"

void EntityStateSystem::Setup()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<EntityState>());
	coordinator.SetSystemSignature<EntityStateSystem>(signature);
}

void EntityStateSystem::Init()
{

}

void EntityStateSystem::Update(float dt)
{
	std::vector<Entity> ActivateList;
	std::vector<Entity> DeactivateList;

	//Check all deactivated entities and see if they need to be activated
	for (auto it = InactiveEntities.begin(); it != InactiveEntities.end(); ++it)
	{
		auto const& entitystate = coordinator.GetComponent<EntityState>(*it);
		if (entitystate.active)
		{
			ActivateList.push_back(*it);
			InactiveEntities.erase(it);
		}
	}

	//Checks if any entities that are not deactivated by the coordinator need to be deactivated
	for (auto const& entity : m_Entities)
	{
		auto& entitystate = coordinator.GetComponent<EntityState>(entity);
		if (!entitystate.active)
		{
			DeactivateList.push_back(entity);
			InactiveEntities.push_back(entity);
		}
	}

	//Activation and Deactivation
	for (auto entity : ActivateList)
	{
		coordinator.ActivateEntity(entity);
	}

	for (auto entity : DeactivateList)
	{
		coordinator.DeactivateEntity(entity);
	}
}
