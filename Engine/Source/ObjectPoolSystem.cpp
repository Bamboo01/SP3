#include "ObjectPoolSystem.h"

void ObjectPoolSystem::Setup()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<EntityState>());

	coordinator.SetSystemSignature<ObjectPoolSystem>(signature);
}

void ObjectPoolSystem::Init()
{
	for (auto& i : PoolDirectory) // For every pool in the Pool Directory, add their cloned entity prefab into their Pool Vector
	{
		Pool* tempPool = &i.second;

		for (int j = 0; j < tempPool->size; j++)
		{
			Entity clonedEntity = coordinator.CloneEntity(tempPool->entityPrefab);
			auto& clonedEntityState = coordinator.GetComponent<EntityState>(clonedEntity);
			clonedEntityState.active = false;
			tempPool->pool.push_back(clonedEntity);
		}
	}
}

void ObjectPoolSystem::Update(double dt)
{
}

void ObjectPoolSystem::AddToPool(Pool pool)
{
	if (pool.size <= 0)
	{
		std::cout << "Pool size must be at least 1." << std::endl;

		return;
	}

	PoolDirectory.insert({pool.poolType, pool});
}

Entity ObjectPoolSystem::FetchEntityFromPool(Tag entityTag)
{

	if (PoolDirectory.find(entityTag) == PoolDirectory.end()) // If the entityTag that was passed in doesn't exist
	{
		std::cout << "EntityType " << entityTag << " does not exist." << std::endl;
		return UINT_MAX;
	}

	Pool* fetchedPool = &PoolDirectory[entityTag];
	Entity inactiveEntity = UINT_MAX;

	for (int i = 0; i < fetchedPool->pool.size(); i++) // Loops through the pool and find for the closest inactive Entity
	{
		Entity entityInFetched = fetchedPool->pool[i];
		auto& poolEntityState = coordinator.GetComponent<EntityState>(entityInFetched);

		if (!poolEntityState.active)
		{
			inactiveEntity = entityInFetched;
			break;
		}
	}

	if (inactiveEntity == UINT_MAX) // If there isn't any inactive entity, make some
	{
		int numberOfEntity = 20;

		for (int i = 0; i < numberOfEntity; i++)
		{
			Entity clonedEntity = coordinator.CloneEntity(fetchedPool->entityPrefab);
			auto& clonedEntityState = coordinator.GetComponent<EntityState>(clonedEntity);
			clonedEntityState.active = false;
			fetchedPool->pool.push_back(clonedEntity);

			if (i == 0) // Pass the inactiveEntity the first newly cloned entity
			{
				inactiveEntity = clonedEntity;
			}
		}
	}

	auto& inactiveEntityState = coordinator.GetComponent<EntityState>(inactiveEntity);

	if (!inactiveEntityState.active)
	{
		inactiveEntityState.active = true;
	}

	return inactiveEntity;
}
