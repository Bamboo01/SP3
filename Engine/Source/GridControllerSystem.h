#pragma once
// After the units are being selected and they are given a new point
//		of destination, this will be called to create a new flow field grid
#include "Coordinator.h"
#include "Application.h"
#include "Unit.h"
#include "glm.hpp"
#include "RayCasting.h"
#include "Transform.h"
extern Coordinator coordinator;

class GridControllerSystem : public System
{
private:
	glm::vec2 GridSize;
	glm::vec2 CursorScreenPosition;

	glm::vec3 GridPosition[20][20];
	std::queue<unsigned> FlowfieldIDs;
	std::map<unsigned,std::pair<int, std::vector <std::vector<int>>>> IDtoFlowfield; // unsigned = ID , int = num of units inside
	std::set<Entity>* UnitList;
	int GridCost[20][20];
	float timer = 0;
	//bool active = false;
	

public:
	Entity raycastentity;
	void getRaycastingEntity(Entity raycast);

	glm::vec3 CursorWorldPosition;
	virtual void CreateGrids();						// Creating of a new grid
	virtual void CheckGridCost(int GridNumX, int GridNumY);		// Checking cost of each Grid
	virtual void Update(float dt);					//Getting Mouse Pressed for position of the unit's destination
	virtual void GetDestinationGrid();				// Get the Destination Grid
	virtual void CreatePathTop(glm::vec2 Destination);		// Get Grid cost for Destination TOP ONLY
	virtual void CreatePathBottom(glm::vec2 Destination);		// Get Grid cost for Destination BOTTOM ONLY
	virtual void SafetyPathCheck(glm::vec2 Destination);		// Just in case there is a -1
	virtual void UpdateUnitPosition();				// Update unit position
	virtual void SetUp();
	virtual void Init();
	void getUnitEntity(std::set<Entity>* entitylist);
};