#include "QuadTreeSystem.h"

void QuadTreeSystem::Setup()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<Transform>());
	signature.set(coordinator.GetComponentType<QuadTree>());

	coordinator.SetSystemSignature<QuadTreeSystem>(signature);
}

void QuadTreeSystem::Init()
{
}

void QuadTreeSystem::Update(double dt)
{
	DeleteQuad(root);

	root = new QuadTree(glm::vec2(-200.f, 200.f), 400.f, 400.f, 0, QUAD_TYPE::ROOT);

	for (auto const& entity : unitEntities)
	{
		root->EntityList.push_back(entity);
	}

	SortQuad(root);
}

void QuadTreeSystem::SetUnitSystemEntities(std::set<Entity> entities)
{
	unitEntities = entities;
}

void QuadTreeSystem::PrintTree(QuadTree* quad)
{
	if (quad == nullptr)
	{
		return;
	}

	std::string outputString, quadTypeString;

	for (int i = 0; i < quad->level; i++)
	{
		outputString += " ";
	}

	switch (quad->quadType)
	{
	case QUAD_TYPE::ROOT:
		quadTypeString = "Root";
		break;
	case QUAD_TYPE::TOP_L:
		quadTypeString = "UpL";
		break;
	case QUAD_TYPE::TOP_R:
		quadTypeString = "UpR";
		break;
	case QUAD_TYPE::BOT_L:
		quadTypeString = "BotL";
		break;
	case QUAD_TYPE::BOT_R:
		quadTypeString = "BotR";
		break;
	}

	outputString = outputString + std::to_string(quad->level) + "-" + quadTypeString + " (" + std::to_string(quad->EntityList.size()) + ")";
	std::cout << outputString << std::endl;

	PrintTree(quad->TopL);
	PrintTree(quad->TopR);
	PrintTree(quad->BotL);
	PrintTree(quad->BotR);
}

QuadTree* QuadTreeSystem::GetNearbyEntityQuad(Entity entity)
{
	QuadTree* searchedQuad = nullptr;

	if (std::find(root->EntityList.begin(), root->EntityList.end(), entity) == root->EntityList.end())
	{
		std::cout << entity << " ID does not exist in the entityList!" << std::endl;
		return nullptr;
	}

	QuadTree* currentQuad = root;

	while (true)
	{
		QUAD_TYPE nextQuad = findEntityQuad(entity, currentQuad);

		switch (nextQuad)
		{
		case QUAD_TYPE::TOP_L:
			currentQuad = currentQuad->TopL;
			break;
		case QUAD_TYPE::TOP_R:
			currentQuad = currentQuad->TopR;
			break;
		case QUAD_TYPE::BOT_L:
			currentQuad = currentQuad->BotL;
			break;
		case QUAD_TYPE::BOT_R:
			currentQuad = currentQuad->BotR;
			break;
		}

		if (currentQuad->TopL == nullptr || currentQuad->TopR == nullptr || currentQuad->BotL == nullptr || currentQuad->BotR == nullptr)
		{
			searchedQuad = currentQuad;
			break;
		}
	}

	return nullptr;
}

void QuadTreeSystem::DeleteEntity(Entity entity, QuadTree* quad)
{
}

void QuadTreeSystem::SortQuad(QuadTree* quad)
{
	int entityPerQuadThreshold = 3;

	if (quad == nullptr || quad->EntityList.size() < entityPerQuadThreshold)
	{
		return;
	}

	SplitQuad(quad);

	for (int i = 0; i < quad->EntityList.size(); i++)
	{
		Entity tmpEntity = quad->EntityList[i];

		QUAD_TYPE entityQuad = findEntityQuad(tmpEntity, quad);

		switch (entityQuad)
		{
		case QUAD_TYPE::TOP_L:
			quad->TopL->EntityList.push_back(tmpEntity);
			break;
		case QUAD_TYPE::TOP_R:
			quad->TopR->EntityList.push_back(tmpEntity);
			break;
		case QUAD_TYPE::BOT_L:
			quad->BotL->EntityList.push_back(tmpEntity);
			break;
		case QUAD_TYPE::BOT_R:
			quad->BotR->EntityList.push_back(tmpEntity);
			break;
		default:
			std::cout << tmpEntity << "is an edge case" << std::endl;
			break;
		}


	}

	SortQuad(quad->TopL);
	SortQuad(quad->TopR);
	SortQuad(quad->BotL);
	SortQuad(quad->BotR);
}

void QuadTreeSystem::SplitQuad(QuadTree* quad)
{
	float halfWidth = quad->width / 2;
	float halfHeight = quad->height / 2;
	int nextQuadLevel = quad->level + 1;

	if (quad->TopL == nullptr)
	{
		QuadTree* newTopL = new QuadTree(glm::vec2(quad->topBoundary), halfWidth, halfHeight, nextQuadLevel, QUAD_TYPE::TOP_L);
		newTopL->parent = quad;
		quad->TopL = newTopL;
	}

	if (quad->TopR == nullptr)
	{
		QuadTree* newTopR = new QuadTree(glm::vec2(quad->topBoundary.x + halfWidth, quad->topBoundary.y), halfWidth, halfHeight, nextQuadLevel, QUAD_TYPE::TOP_R);
		newTopR->parent = quad;
		quad->TopR = newTopR;
	}

	if (quad->BotL == nullptr)
	{
		QuadTree* newBotL = new QuadTree(glm::vec2(quad->topBoundary.x, quad->topBoundary.y - halfHeight), halfWidth, halfHeight, nextQuadLevel, QUAD_TYPE::BOT_L);
		newBotL->parent = quad;
		quad->BotL = newBotL;
	}

	if (quad->BotR == nullptr)
	{
		QuadTree* newBotR = new QuadTree(glm::vec2(quad->topBoundary.x + halfWidth, quad->topBoundary.y - halfHeight), halfWidth, halfHeight, nextQuadLevel, QUAD_TYPE::BOT_R);
		newBotR->parent = quad;
		quad->BotR = newBotR;
	}
}

bool QuadTreeSystem::CheckEntityExist(Entity entity, QuadTree* quad)
{
	return false;
}

QUAD_TYPE QuadTreeSystem::findEntityQuad(Entity entity, QuadTree* quad)
{
	auto& entityTransform = coordinator.GetComponent<Transform>(entity);

	glm::vec2 TopL_TopBoundary = quad->TopL->topBoundary;
	glm::vec2 TopL_BottomBoundary = quad->TopL->bottomBoundary;

	glm::vec2 TopR_TopBoundary = quad->TopR->topBoundary;
	glm::vec2 TopR_BottomBoundary = quad->TopR->bottomBoundary;

	glm::vec2 BotL_TopBoundary = quad->BotL->topBoundary;
	glm::vec2 BotL_BottomBoundary = quad->BotL->bottomBoundary;

	glm::vec2 BotR_TopBoundary = quad->BotR->topBoundary;
	glm::vec2 BotR_BottomBoundary = quad->BotR->bottomBoundary;

	if (entityTransform.position.x >= TopL_TopBoundary.x && entityTransform.position.x <= TopL_BottomBoundary.x && entityTransform.position.z >= TopL_BottomBoundary.y && entityTransform.position.z <= TopL_TopBoundary.y) // If GO is in UpL
	{
		return QUAD_TYPE::TOP_L;
	}
	else if (entityTransform.position.x >= TopR_TopBoundary.x && entityTransform.position.x <= TopR_BottomBoundary.x && entityTransform.position.z >= TopR_BottomBoundary.y && entityTransform.position.z <= TopR_TopBoundary.y) // If GO is in UpR
	{
		return QUAD_TYPE::TOP_R;
	}
	else if (entityTransform.position.x >= BotL_TopBoundary.x && entityTransform.position.x <= BotL_BottomBoundary.x && entityTransform.position.z >= BotL_BottomBoundary.y && entityTransform.position.z <= BotL_TopBoundary.y) // If GO is in BotL
	{
		return QUAD_TYPE::BOT_L;
	}
	else if (entityTransform.position.x >= BotR_TopBoundary.x && entityTransform.position.x <= BotR_BottomBoundary.x && entityTransform.position.z >= BotR_BottomBoundary.y && entityTransform.position.z <= BotR_TopBoundary.y) // If GO is in BotR
	{
		return QUAD_TYPE::BOT_R;
	}
}

void QuadTreeSystem::DeleteQuad(QuadTree* quad)
{
	if (quad == nullptr)
	{
		return;
	}

	DeleteQuad(quad->TopL);
	DeleteQuad(quad->TopR);
	DeleteQuad(quad->BotL);
	DeleteQuad(quad->BotR);
	delete quad;
}
