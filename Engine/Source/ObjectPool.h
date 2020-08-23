#include <glm.hpp>
#include "Entity.h"
#include "Tag.h"
#include <vector>

#pragma once

struct Pool
{
	Tag poolType;
	Entity entityPrefab;
	int size;
	std::vector<Entity> pool;

	Pool()
		: poolType(Tag::DEFAULT)
		, entityPrefab(UINT_MAX)
		, size(0)
	{}

	Pool(Tag type, Entity entityPrefab, int poolSize)
		: poolType(type)
		, entityPrefab(entityPrefab)
		, size(poolSize)
	{}

};