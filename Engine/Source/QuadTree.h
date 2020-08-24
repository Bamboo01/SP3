#pragma once

#include "Entity.h"
#include "glm.hpp"
#include <vector>

enum QUAD_TYPE
{
	TOP_L,
	TOP_R,
	BOT_L,
	BOT_R,
	ROOT
};

class QuadTree {
public:
	
	int level;
	float width;
	float height;
	glm::vec2 topBoundary;
	glm::vec2 bottomBoundary;

	QuadTree* parent;
	QuadTree* TopL;
	QuadTree* TopR;
	QuadTree* BotL;
	QuadTree* BotR;

	QUAD_TYPE quadType;

	std::vector<Entity> EntityList;

	QuadTree() {};

	QuadTree(glm::vec2 topLeftBoundary, float width, float height, int level, QUAD_TYPE type)
	{
		this->level = level;
		this->width = width;
		this->height = height;
		topBoundary = topLeftBoundary;
		bottomBoundary = glm::vec2(topLeftBoundary.x + width - 0.001f, topLeftBoundary.y - height - 0.001f);
		parent = TopL = TopR = BotL = BotR = nullptr;
		quadType = type;
	}

	~QuadTree() {};
};
