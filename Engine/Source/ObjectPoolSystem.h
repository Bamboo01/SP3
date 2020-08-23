#pragma once

#include "ObjectPool.h"
#include "Coordinator.h"
#include "System.h"

extern Coordinator coordinator;

class ObjectPoolSystem : public System
{
public:
	void Setup();
	void Init();
	void Update(double dt);

	void AddToPool(Pool pool);
	Entity FetchEntityFromPool(Tag entityTag);

private:
	std::unordered_map<Tag, Pool> PoolDirectory;
};