#include "EntityStateSystem.h"

void EntityStateSystem::Setup()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<EntityState>());
	coordinator.SetSystemSignature<EntityStateSystem>(signature);
}

void EntityStateSystem::Init()
{
	std::vector<Entity> InactiveEntities;
	for (auto const& entity : m_Entities)
	{
		auto& entitystate = coordinator.GetComponent<EntityState>(entity);
		EntityToState.insert({entity, entitystate});
		if (!entitystate.active)
		{
			InactiveEntities.push_back(entity);
		}
	}
	for (auto const& entity : InactiveEntities)
	{
		coordinator.DeactivateEntity(entity);
	}
}

void EntityStateSystem::Update(float dt)
{
	std::vector<Entity> ActiveEntities;

    for (auto const& entity : m_Entities)
    {
		ActiveEntities.push_back(entity);
    }

	for (auto const& entity : ActiveEntities)
	{
		auto& storedentitystate = EntityToState[entity];
		auto& entitystate = coordinator.GetComponent<EntityState>(entity);
		if (entitystate.active != storedentitystate.active)
		{
			if (entitystate.active == false)
			{
				coordinator.DeactivateEntity(entity);
			}
			EntityToState[entity].active = false;
		}
	}

	for (auto const& entitytostate : EntityToState)
	{
		auto const& entity = entitytostate.first;
		auto const& entitystate = coordinator.GetComponent<EntityState>(entity);
		if (entitytostate.second.active != entitystate.active)
		{
			coordinator.ActivateEntity(entity);
		}
	}
}
