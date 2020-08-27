#include "GridControllerSystem.h"


void GridControllerSystem::getRaycastingEntity(Entity raycast)
{
	raycastentity = raycast;
}

void GridControllerSystem::CreateGrids()
{
	for (int x = 0; x < 20; ++x)
	{
		for (int y = 0; y < 20; ++y)
		{
			GridCost[x][y] = -1;
		}
	}
	int y = 0;
	for (int Posy = -300; Posy < 300; Posy += 30)
	{
		int x = 0;
		for (int Posx = 300; Posx > -300; Posx -= 30)
		{
			GridPosition[x][y] = glm::vec3(Posy, 2, Posx);
			CheckGridCost(x,y);
			//std::cout << GridPosition[count].x << ", " << GridPosition[count].y << ", " << GridPosition[count].z << " ::::" << GridCost[count] << std::endl;
			x++;
		}
		++y;
	}
	GetDestinationGrid();
	//active = true;

}

void GridControllerSystem::CheckGridCost(int GridNumX, int GridNumY)
{
	glm::vec3 GridTopLeft = GridPosition[GridNumX][GridNumY];
	glm::vec3 GridBottomRight = glm::vec3(GridTopLeft.x + 30, GridTopLeft.y, GridTopLeft.z - 30);
	for (auto const& entity : m_Entities)
	{
		auto& unit = coordinator.GetComponent<Unit>(entity);
		auto& transform = coordinator.GetComponent<Transform>(entity);
		/*if (transform.position.x + transform.scale.x>= GridTopLeft.x && transform.position.x + transform.scale.x <= GridBottomRight.x && transform.position.z+ transform.scale.z <= GridTopLeft.z && transform.position.z + transform.scale.z >= GridBottomRight.z)
		{
			GridCost[GridNumX][GridNumY] += unit.FlowFieldCost;
		}*/
		if (unit.FlowFieldCost != 0)
		{
			if ((transform.position.x >= GridTopLeft.x) && (transform.position.x <= GridBottomRight.x) && (transform.position.y <= GridTopLeft.y) && (transform.position.y >= GridBottomRight.y))
			{
				GridCost[GridNumX][GridNumY] += unit.FlowFieldCost;
			}
		}
	}
	
}


void GridControllerSystem::Update(float dt)
{
	if (Application::IsMousePressed(1))
	{

		int x = Application::GetWindowWidth();
		int y = Application::GetWindowHeight();
		CursorScreenPosition = glm::vec2(Application::mouse_current_x, Application::mouse_current_y);
		auto& raycaster = coordinator.GetComponent<RayCasting>(raycastentity);
		CursorWorldPosition = raycaster.rightClick;

		CreateGrids();
		std::vector <std::vector<int>> temp;
		temp.resize(20);
		for (auto& vec : temp)
		{
			vec.resize(20);
		}

		for (int x = 0; x < 20; ++x)
		{
			for (int y = 0; y < 20; ++y)
			{
				temp[x][y] = GridCost[x][y];
			}
		}
		
		IDtoFlowfield.insert({ FlowfieldIDs.front(),std::make_pair(raycaster.selectedunits.size(), temp) });
		for (auto e : raycaster.selectedunits)
		{
			auto& a = coordinator.GetComponent<Unit>(e);
			if (a.UnitID != INT_MAX)
			{
				IDtoFlowfield.at(a.UnitID).first--;
			}
			a.UnitID = FlowfieldIDs.front();
		}
		FlowfieldIDs.pop();
		UpdateUnitPosition();
	/*	for (int y = 0; y < 20; ++y)
		{
			for (int x = 0; x < 20; ++x)
			{
				std::cout << GridPosition[x][y].x << ", " << GridPosition[x][y].y << ", " << GridPosition[x][y].z << " ::::" << GridCost[x][y] << std::endl;
			}
		}*/
		
	}
	for (auto const& entity : m_Entities)
	{
		auto& unit = coordinator.GetComponent<Unit>(entity);
		auto& transform = coordinator.GetComponent<Transform>(entity);
		if (unit.nextGrid != glm::vec2(-1, -1)) {
			int GTLX = unit.nextGrid.x;
			int GTLY = unit.nextGrid.y;
			glm::vec3 GridTopLeft = GridPosition[GTLX][GTLY];
			glm::vec3 GridBottomRight = glm::vec3(GridTopLeft.x + 30, GridTopLeft.y, GridTopLeft.z - 30);
			if (transform.position.x + transform.scale.x >= GridTopLeft.x && transform.position.x + transform.scale.x <= GridBottomRight.x && transform.position.z + transform.scale.z <= GridTopLeft.z && transform.position.z + transform.scale.z >= GridBottomRight.z)
			{
				UpdateUnitPosition();
			}
		}
		transform.position += unit.velocity;
	//	std::cout << unit.velocity.x << ", " << unit.velocity.z << std::endl;
	}
	UpdateUnitPosition();

}

void GridControllerSystem::GetDestinationGrid()
{
//	std::cout << CursorWorldPosition.x << " " << CursorWorldPosition.z << std::endl;
	// Check Which Grid the destination is at
	glm::vec2 destination = glm::vec2(-1,-1);	// If it is -1 at the end, means that destination is impossible
	for (int x = 0; x < 20; ++x)
	{
		for (int y = 0; y < 20; ++y)
		{
			glm::vec3 GridTopLeft = GridPosition[x][y];
			glm::vec3 GridBottomRight = glm::vec3(GridTopLeft.x + 30, GridTopLeft.y, GridTopLeft.z - 30);
			if (CursorWorldPosition.x >= GridTopLeft.x && CursorWorldPosition.x <= GridBottomRight.x && CursorWorldPosition.z <= GridTopLeft.z && CursorWorldPosition.z >= GridBottomRight.z)
			{
				if (GridCost[x][y] == -1)
				{	// Set The Empty Grid To the Destination Point
					GridCost[x][y] = 0;
					destination.x = x;
					destination.y = y;
					//std::cout << GridPosition[x][y].x << ", " << GridPosition[x][y].z << std::endl;
					break;
				}
				else
					break;		// If there is a wall at the destination point, Destination is impossible to reach
			}
		}
	}
	if (destination.x != -1 && destination.y != -1)
	{
		// A Grid that has been selected
		CreatePathTop(destination);
		
		CreatePathBottom(destination);

		SafetyPathCheck(destination);
	}
}

void GridControllerSystem::CreatePathTop(glm::vec2 Destination)
{
	int dX = Destination.x;
	int dY = Destination.y;
	//glm::vec3 GridTopLeft = GridPosition[dX][dY];
	glm::vec3 GridBottomRight = glm::vec3(GridPosition[dX][dY].x + 30, GridPosition[dX][dY].y, GridPosition[dX][dY].z - 30);
	bool north, east, west;
	if (dX - 1 >= 0 && dX - 1 <= 19)
	{
		north = ((GridPosition[dX - 1][dY].z == (GridPosition[dX][dY].z + 30)) &&
			(GridPosition[dX - 1][dY].x == GridPosition[dX][dY].x) && (GridCost[dX - 1][dY] == -1));
	}
	else 
	{
		north = false;
	}
	if (dY + 1 >= 0 && dY + 1 <= 19)
	{
		east = ((GridPosition[dX][dY + 1].z == GridBottomRight.z + 30) && (GridPosition[dX][dY + 1].x == GridBottomRight.x) &&
			(GridCost[dX][dY + 1] == -1));
	}
	else
	{
		east = false;
	}
	if (dY - 1 >= 0 && dY - 1 <= 19)
	{
		west = ((GridPosition[dX][dY - 1].x == GridPosition[dX][dY].x - 30) && (GridPosition[dX][dY - 1].z == GridPosition[dX][dY].z) &&
			(GridCost[dX][dY - 1] == -1));
	}
	else
	{
		west = false;
	}
	// Check at the edge of the world space
	// If not, Check if the grid around it is passable or not
	
	//North
	
	if (GridPosition[dX][dY].z != 300)
	{
		// There is a Grid in the North Direction!!
		// Check the North Grid ID

		if (north) // Checks if there is grid Cost is uninitialized
		{
			// If the East is a smaller number
			if ((dX - 1 >= 0 && dX - 1 <= 19) && (dY + 1 >= 0 && dY + 1 <= 19) &&(GridCost[dX - 1][dY + 1] >= 0) && (GridCost[dX-1][dY + 1] < GridCost[dX][dY]) && (GridCost[dX-1][dY + 1] < GridCost[dX-1][dY - 1]))
			{
				GridCost[dX - 1][dY] = GridCost[dX -1][dY+1]+1;
			}
			// If the West is a smaller number
			else if ((dX - 1 >= 0 && dX - 1 <= 19) && (dY - 1 >= 0 && dY - 1 <= 19) && (GridCost[dX - 1][dY - 1] >= 0) && (GridCost[dX-1][dY - 1] < GridCost[dX][dY]) && (GridCost[dX-1][dY - 1] < GridCost[dX-1][dY + 1]))
			{
				GridCost[dX - 1][dY] = GridCost[dX-1][dY-1] + 1;
			}
			else
			{
				GridCost[dX - 1][dY] = GridCost[dX][dY] + 1;
			}
		}

	}
	// East
	if (GridBottomRight.x != 300)
	{
		// There is a Grid in the East Direction!
		// Check East Grid ID

		if (east)// Checks if there is grid Cost is uninitialized
		{
			// If the south is a smaller number
			if ((dX + 1 >= 0 && dX + 1 <= 19) && (dY + 1 >= 0 && dY + 1 <= 19) &&(GridCost[dX + 1][dY + 1] >= 0)&&(GridCost[dX + 1][dY + 1] < GridCost[dX][dY]) && (GridCost[dX + 1][dY + 1] < GridCost[dX - 1][dY + 1]))
			{
				GridCost[dX][dY + 1] = GridCost[dX + 1][dY + 1] + 1;
			}
			// If the North is a smaller number
			else if ((dX - 1 >= 0 && dX -1 <= 19) && (dY + 1 >= 0 && dY + 1 <= 19) && (GridCost[dX - 1][dY + 1] >= 0)&& (GridCost[dX - 1][dY + 1] < GridCost[dX][dY]) && (GridCost[dX - 1][dY + 1] < GridCost[dX + 1][dY + 1]))
			{
				GridCost[dX][dY + 1] = GridCost[dX - 1][dY + 1] + 1;
			}
			else
			{
				GridCost[dX][dY + 1] = GridCost[dX][dY] + 1;
			}
		}

	}
	// West
	if (GridPosition[dX][dY].x != -300)
	{
		// There is a Grid in the West Direction!
		// Check West Grid ID
		if(west) // Check if there is grid Cost is uninitialized
		{// If the south is a smaller number
			if ((dX + 1 >= 0 && dX + 1 <= 19)&&(dY - 1 >= 0 && dY - 1 <= 19) && (GridCost[dX + 1][dY - 1] >= 0)&&(GridCost[dX + 1][dY - 1] < GridCost[dX][dY]) && (GridCost[dX + 1][dY - 1] < GridCost[dX - 1][dY - 1]))
			{
				GridCost[dX][dY - 1] = GridCost[dX + 1][dY - 1] + 1;
			}
			else if ((dX + 1 >= 0 && dX - 1 <= 19) && (dY - 1 >= 0 && dY - 1 <= 19) &&(GridCost[dX - 1][dY - 1] >= 0) && (GridCost[dX - 1][dY - 1] < GridCost[dX][dY]) && (GridCost[dX - 1][dY - 1] < GridCost[dX + 1][dY - 1]))
			{
				GridCost[dX][dY - 1] = GridCost[dX - 1][dY - 1] + 1;
			}
			else
			{
				GridCost[dX][dY - 1] = GridCost[dX][dY] + 1;
			}
		}


	}
	if (north)
	{
		CreatePathTop(glm::vec2(dX-1,dY));
	}
	if (east)
	{
		CreatePathTop(glm::vec2(dX,dY+1));
	}
	if (west)
	{
		CreatePathTop(glm::vec2(dX,dY-1));
	}
}

void GridControllerSystem::CreatePathBottom(glm::vec2 Destination)
{
	int dX = Destination.x;
	int dY = Destination.y;
	//glm::vec3 GridTopLeft = GridPosition[dX][dY];
	glm::vec3 GridBottomRight = glm::vec3(GridPosition[dX][dY].x + 30, GridPosition[dX][dY].y, GridPosition[dX][dY].z - 30);
	bool south, east, west;
	if (dX + 1 >= 0 && dX + 1 <= 19)
	{
		south = ((GridPosition[dX + 1][dY].z == GridPosition[dX][dY].z - 30) && (GridPosition[dX + 1][dY].x == GridPosition[dX][dY].x) &&
			(GridCost[dX + 1][dY] == -1));
	}
	else
	{
		south = false;
	}
	if (dY + 1 >= 0 && dY + 1 <= 19)
	{
		east = ((GridPosition[dX][dY + 1].z == GridBottomRight.z + 30) && (GridPosition[dX][dY + 1].x == GridBottomRight.x) &&
			(GridCost[dX][dY + 1] == -1));
	}
	else
	{
		east = false;
	}
	if (dY - 1 >= 0 && dY - 1 <= 19)
	{
		west = ((GridPosition[dX][dY - 1].x == GridPosition[dX][dY].x - 30) && (GridPosition[dX][dY - 1].z == GridPosition[dX][dY].z) &&
			(GridCost[dX][dY - 1] == -1));
	}
	else
	{
		west = false;
	}
	// Check at the edge of the world space
	// If not, Check if the grid around it is passable or not
	// South
	if (GridBottomRight.z != -300)
	{
		// There is a Grid in the South Direction!!
		// Check the South Grid ID

		if (south) // Checks if there is grid Cost is uninitialized
		{
			// If the East is a smaller number
			if ((dX + 1 >= 0 && dX + 1 <= 19) && (dY + 1 >= 0 && dY + 1 <= 19) && (GridCost[dX + 1][dY + 1] >= 0) && (GridCost[dX + 1][dY + 1] < GridCost[dX][dY]) && (GridCost[dX + 1][dY + 1] < GridCost[dX + 1][dY - 1]))
			{
				GridCost[dX + 1][dY] = GridCost[dX + 1][dY + 1] + 1;
			}
			// If the West is a smaller number
			else if ((dX + 1 >= 0 && dX + 1 <= 19) && (dY - 1 >= 0 && dY - 1 <= 19) && (GridCost[dX + 1][dY - 1] >= 0) && (GridCost[dX + 1][dY - 1] < GridCost[dX][dY]) && (GridCost[dX + 1][dY - 1] < GridCost[dX + 1][dY + 1]))
			{
				GridCost[dX + 1][dY] = GridCost[dX + 1][dY - 1] + 1;
			}
			else
			{
				GridCost[dX + 1][dY] = GridCost[dX][dY] + 1;
			}
		}
	}
	// East
	if (GridBottomRight.x != 300)
	{
		// There is a Grid in the East Direction!
		// Check East Grid ID

		if (east)// Checks if there is grid Cost is uninitialized
		{
			// If the south is a smaller number
			if ((dX + 1 >= 0 && dX + 1 <= 19) && (dY + 1 >= 0 && dY + 1 <= 19) && (GridCost[dX + 1][dY + 1] >= 0) && (GridCost[dX + 1][dY + 1] < GridCost[dX][dY]) && (GridCost[dX + 1][dY + 1] < GridCost[dX - 1][dY + 1]))
			{
				GridCost[dX][dY + 1] = GridCost[dX + 1][dY + 1] + 1;
			}
			// If the North is a smaller number
			else if ((dX - 1 >= 0 && dX - 1 <= 19) && (dY + 1 >= 0 && dY + 1 <= 19) && (GridCost[dX - 1][dY + 1] >= 0) && (GridCost[dX - 1][dY + 1] < GridCost[dX][dY]) && (GridCost[dX - 1][dY + 1] < GridCost[dX + 1][dY + 1]))
			{
				GridCost[dX][dY + 1] = GridCost[dX - 1][dY + 1] + 1;
			}
			else
			{
				GridCost[dX][dY + 1] = GridCost[dX][dY] + 1;
			}
		}

	}
	// West
	if (GridPosition[dX][dY].x != -300)
	{
		// There is a Grid in the West Direction!
		// Check West Grid ID
		if (west) // Check if there is grid Cost is uninitialized
		{// If the south is a smaller number
			if ((dX + 1 >= 0 && dX + 1 <= 19) && (dY - 1 >= 0 && dY - 1 <= 19) && (GridCost[dX + 1][dY - 1] >= 0) && (GridCost[dX + 1][dY - 1] < GridCost[dX][dY]) && (GridCost[dX + 1][dY - 1] < GridCost[dX - 1][dY - 1]))
			{
				GridCost[dX][dY - 1] = GridCost[dX + 1][dY - 1] + 1;
			}
			else if ((dX + 1 >= 0 && dX - 1 <= 19) && (dY - 1 >= 0 && dY - 1 <= 19) && (GridCost[dX - 1][dY - 1] >= 0) && (GridCost[dX - 1][dY - 1] < GridCost[dX][dY]) && (GridCost[dX - 1][dY - 1] < GridCost[dX + 1][dY - 1]))
			{
				GridCost[dX][dY - 1] = GridCost[dX - 1][dY - 1] + 1;
			}
			else
			{
				GridCost[dX][dY - 1] = GridCost[dX][dY] + 1;
			}
		}


	}
	if (south)
	{
		CreatePathBottom(glm::vec2(dX + 1, dY));
	}
	if (east)
	{
		CreatePathBottom(glm::vec2(dX, dY + 1));
	}
	if (west)
	{
		CreatePathBottom(glm::vec2(dX, dY - 1));
	}
}

void GridControllerSystem::SafetyPathCheck(glm::vec2 Destination)
{
	for (int x = 0; x < 20; ++x)
	{
		for (int y = 0; y < 20; ++y)
			if (GridCost[x][y] == -1)
			{
				if (x + 1 <= 19 && x + 1 >= 0 && GridCost[x + 1][y] != -1)
				{
					GridCost[x][y] = GridCost[x + 1][y] + 1;
				}
				else if (x - 1 <= 19 && x - 1 >= 0 && GridCost[x - 1][y] != -1)
				{
					GridCost[x][y] = GridCost[x - 1][y] + 1;
				}
				else if (y + 1 <= 19 && y + 1 >= 0 && GridCost[x][y + 1] != -1)
				{
					GridCost[x][y] = GridCost[x][y + 1] + 1;
				}
				else if (y - 1 <= 19 && y - 1 >= 0 && GridCost[x][y - 1] != -1)
				{
					GridCost[x][y] = GridCost[x][y - 1] + 1;
				}
			}
	}
}


void GridControllerSystem::UpdateUnitPosition()
{
	for (auto const& entity : m_Entities)
	{
		auto& unit = coordinator.GetComponent<Unit>(entity);
		auto& transform = coordinator.GetComponent<Transform>(entity);
		if (unit.FlowFieldCost == 0 && unit.UnitID != INT_MAX)
		{
			std::vector <std::vector<int>> temp;
			temp.resize(20);
			for (auto& vec : temp)
			{
				vec.resize(20);
			}
			temp = IDtoFlowfield.at(unit.UnitID).second;
			for (int x = 0; x < 20; ++x)
			{
				for (int y = 0; y < 20; ++y)
				{
					GridCost[x][y] = temp[x][y];
				}
			}

			for (int x = 0; x < 20; ++x)
			{
				for (int y = 0; y < 20; ++y)
				{
					glm::vec3 GridTopLeft = GridPosition[x][y];
					glm::vec3 GridBottomRight = glm::vec3(GridTopLeft.x + 30, GridTopLeft.y, GridTopLeft.z - 30);
					glm::vec3 distance = glm::vec3(0,0,0);
					glm::vec3 direction;
					if (transform.position.x + transform.scale.x >= GridTopLeft.x && transform.position.x + transform.scale.x <= GridBottomRight.x && transform.position.z + transform.scale.z <= GridTopLeft.z && transform.position.z + transform.scale.z >= GridBottomRight.z)
					{
					//	std::cout << GridCost[x][y] << std::endl;
					//	std::cout << GridPosition[x][y].x << ", " << GridPosition[x][y].z << std::endl;
						if (GridCost[x][y] == 0)
						{
							unit.velocity = glm::vec3(0, 0, 0);
							x = 20; y = 20;
							break;
						}
						// Check which ditection has the smallest number
						int cost = -1;
						glm::vec3 lowest(0,0,-1); // x,y = array position; z = gridcost;
					
						// Check for North
						if (x - 1 <= 19 && x - 1 >= 0)
						{
							//If North Grid Exist
							cost = GridCost[x - 1][y];
							if ((lowest.z == -1 || cost < lowest.z) && cost != -1)
							{
								lowest = glm::vec3(x - 1, y, cost);
								distance = glm::vec3(0, 0, 30);
							}
						}
						// Check for South
						if (x + 1 <= 19 && x + 1 >= 0)
						{
							//If south Grid Exist
							cost = GridCost[x + 1][y];
							if ((lowest.z == -1 || cost < lowest.z) && cost != -1)
							{
								lowest = glm::vec3(x + 1, y, cost);
								distance = glm::vec3(0, 0, -30);
							}
						}
						// Check for East
						if (y + 1 <= 19 && y + 1 >= 0)
						{
							//If East Grid Exist
							cost = GridCost[x][y + 1];
							if ((lowest.z == -1 || cost < lowest.z) && cost != -1)
							{
								lowest = glm::vec3(x, y+1, cost);
								distance = glm::vec3(30, 0, 0);
							}
						}
						// Check for West
						if (y - 1 <= 19 && y - 1 >= 0)
						{
							//If West Grid Exist
							cost = GridCost[x][y - 1];
							if ((lowest.z == -1 || cost < lowest.z) && cost != -1)
							{
								lowest = glm::vec3(x, y - 1, cost);
								distance = glm::vec3(-30, 0, 0);
							}
						}
						// Check for North East
						if (y + 1 <= 19 && y + 1 >= 0 && x - 1 <= 19 && x - 1 >= 0)
						{
							//If North East Grid Exist
							cost = GridCost[x - 1][y + 1];
							if ((lowest.z == -1 || cost < lowest.z) && cost != -1)
							{
								lowest = glm::vec3(x - 1, y + 1, cost);
								distance = glm::vec3(25, 0, 25);
							}
						}
						// Check for North West
						if (y - 1 <= 19 && y - 1 >= 0 && x - 1 <= 19 && x - 1 >= 0)
						{
							//If North West Grid Exist
							cost = GridCost[x - 1][y - 1];
							if ((lowest.z == -1 || cost < lowest.z) && cost != -1)
							{
								lowest = glm::vec3(x - 1, y - 1, cost);
								distance = glm::vec3(25, 0, -25);
							}
						}
						// Check for South East
						if (y + 1 <= 19 && y + 1 >= 0 && x + 1 <= 19 && x + 1 >= 0)
						{
							//If South East Grid Exist
							cost = GridCost[x + 1][y + 1];
							if ((lowest.z == -1 || cost < lowest.z) && cost != -1)
							{
								lowest = glm::vec3(x + 1, y + 1, cost);
								distance = glm::vec3(-25, 0, 25);
							}
						}
						// Check for North West
						if (y - 1 <= 19 && y - 1 >= 0 && x + 1 <= 19 && x + 1 >= 0)
						{
							//If North West Grid Exist
							cost = GridCost[x + 1][y - 1];
							if ((lowest.z == -1 || cost < lowest.z) && cost != -1)
							{
								lowest = glm::vec3(x + 1, y - 1, cost);
								distance = glm::vec3(-25, 0, -25);
							}
						}

						if (lowest.z != -1)
						{
							//Set Unit Velocity
							int dX = lowest.x;
							int dY = lowest.y;
							unit.nextGrid = glm::vec2(dX, dY);
							//glm::vec3 distance = GridPosition[dX][dY] + glm::vec3(15,15,15)- transform.position + (transform.scale);
							//glm::vec3 direction = glm::normalize(distance);
							//float temp = direction.x;
							//direction.x = -direction.z;
							//direction.z = temp;
							distance = GridPosition[dX][dY] - transform.position + distance;
							glm::vec3 direction = glm::normalize(distance);
							transform.rotation.y = Math::RadianToDegree(atan2f(direction.x, direction.z)) - 90;
							unit.velocity = 0.6f * direction;
							unit.velocity.y = 0;
						/*	std::cout << GridCost[dX][dY] << std::endl;
							std::cout << GridPosition[dX][dY].x << ", " << GridPosition[dX][dY].z << std::endl;
							std::cout << direction.x << ", " << direction.z << std::endl;*/
						}
						else
						{
							unit.velocity = glm::vec3(0, 0, 0);
						}



					}
				}
			}
		}
	}
}

void GridControllerSystem::UpdateEnemyGridCost(glm::vec3 Destination, std::vector<Entity> units)
{
	CreateGrids();
	glm::vec2 destination = glm::vec2(-1, -1);	// If it is -1 at the end, means that destination is impossible
	for (int x = 0; x < 20; ++x)
	{
		for (int y = 0; y < 20; ++y)
		{
			glm::vec3 GridTopLeft = GridPosition[x][y];
			glm::vec3 GridBottomRight = glm::vec3(GridTopLeft.x + 30, GridTopLeft.y, GridTopLeft.z - 30);
			if (Destination.x >= GridTopLeft.x && Destination.x <= GridBottomRight.x && Destination.z <= GridTopLeft.z && Destination.z >= GridBottomRight.z)
			{
				if (GridCost[x][y] == -1)
				{	// Set The Empty Grid To the Destination Point
					GridCost[x][y] = 0;
					destination.x = x;
					destination.y = y;
					//std::cout << GridPosition[x][y].x << ", " << GridPosition[x][y].z << std::endl;
					break;
				}
				else
					break;		// If there is a wall at the destination point, Destination is impossible to reach
			}
		}
	}
	if (destination.x != -1 && destination.y != -1)
	{
		// A Grid that has been selected
		CreatePathTop(destination);

		CreatePathBottom(destination);

		SafetyPathCheck(destination);


		std::vector <std::vector<int>> temp;
		temp.resize(20);
		for (auto& vec : temp)
		{
			vec.resize(20);
		}

		for (int x = 0; x < 20; ++x)
		{
			for (int y = 0; y < 20; ++y)
			{
				temp[x][y] = GridCost[x][y];
			}
		}

		IDtoFlowfield.insert({ FlowfieldIDs.front(),std::make_pair(units.size(), temp) });
		for (auto e : units)
		{
			auto& a = coordinator.GetComponent<Unit>(e);
			if (a.UnitID != INT_MAX)
			{
				IDtoFlowfield.at(a.UnitID).first--;
			}
			a.UnitID = FlowfieldIDs.front();
		}
		FlowfieldIDs.pop();
		UpdateUnitPosition();
	}

}

void GridControllerSystem::SetUp()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<Unit>());
	signature.set(coordinator.GetComponentType<Transform>());
	signature.set(coordinator.GetComponentType<EntityState>());
	coordinator.SetSystemSignature<GridControllerSystem>(signature);
}

void GridControllerSystem::Init()
{
	for (int i = 0; i < 1000; ++i)
	{
		FlowfieldIDs.push(i);
	}
}

void GridControllerSystem::getUnitEntity(std::set<Entity> *entitylist)
{
	UnitList = entitylist;
}


