#pragma once

#include "System.h"
#include "QuadTree.h"
#include "Transform.h"
#include "Coordinator.h"
#include <string>

extern Coordinator coordinator;

class QuadTreeSystem : public System
{
public:
	virtual void Setup();
	virtual void Init();
	virtual void Update(double dt);

	QuadTree* root;

	void SetUnitSystemEntities(std::set<Entity> entities);

	void PrintTree(QuadTree* quad);

	QuadTree* GetNearbyEntityQuad(Entity entity);
	QuadTree* GetNearbyEntityQuad(glm::vec3 pos);
	std::vector<Entity> GetEntityInQuad(QuadTree* quad);

	void SortQuad(QuadTree* quad);
	void SplitQuad(QuadTree* quad);
	bool CheckEntityExist(Entity entity, QuadTree* quad);

	QUAD_TYPE findEntityQuad(Entity entity, QuadTree* quad);
	QUAD_TYPE findEntityQuad(glm::vec3 pos, QuadTree* quad);

	void DeleteQuad(QuadTree* quad);

	float rootHalfWidth;
	float rootHalfHeight;

private:
	std::set<Entity> unitEntities;
};