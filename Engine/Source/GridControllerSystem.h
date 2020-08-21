#pragma once
// After the units are being selected and they are given a new point
//		of destination, this will be called to create a new flow field grid
#include "Coordinator.h"
#include "Application.h"
#include "Unit.h"
#include "glm.hpp"
#include "Transform.h"
extern Coordinator coordinator;

class GridControllerSystem : public System
{
private:
	glm::vec2 GridSize;
	glm::vec2 CursorScreenPosition;
	glm::vec3 CursorWorldPosition;
	

public:
	virtual void CreateGrids();						// Creating of a new grid
	virtual void CheckGridCost(int GridNumX, int GridNumY);		// Checking cost of each Grid
	virtual void Update(float dt);					//Getting Mouse Pressed for position of the unit's destination
	virtual void GetDestinationGrid();				// Get the Destination Grid
	virtual void CreatePathTop(glm::vec2 Destination);		// Get Grid cost for Destination TOP ONLY
	virtual void CreatePathBottom(glm::vec2 Destination);		// Get Grid cost for Destination BOTTOM ONLY
	virtual void CheckSameLine(glm::vec2 Destination);		// If destination is on the same z axis as the grids and there is a wall
	virtual void SetUp();
	glm::vec3 GridPosition[20][20];
	int GridCost[20][20];
};