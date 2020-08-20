#pragma once
// After the units are being selected and they are given a new point
//		of destination, this will be called to create a new flow field grid
#include "Coordinator.h"
#include "Application.h"
#include "Unit.h"
#include "glm.hpp"
extern Coordinator coordinator;

class GridControllerSytem : public System
{
private:
	glm::vec2 GridSize;
	glm::vec2 CursorScreenPosition;
	glm::vec3 CursorWorldPosition;
	

public:
	virtual void CreateGrids();						// Creating of a new grid
	virtual void CheckGridCost(int GridNum);		// Checking cost of each Grid
	virtual void Update(float dt);					//Getting Mouse Pressed for position of the unit's destination
	virtual void CreatePath();
	virtual void SetUp();
	glm::vec3 GridPosition[500];
	int GridCost[500];
};