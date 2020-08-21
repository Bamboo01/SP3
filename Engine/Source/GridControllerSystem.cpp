#include "GridControllerSystem.h"


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
	for (int Posy = 500; Posy > -500; Posy -= 50)
	{
		int x = 0;
		for (int Posx = -500; Posx < 500; Posx += 50)
		{
			GridPosition[x][y] = glm::vec3(Posx, 2, Posy);
			CheckGridCost(x,y);
			//std::cout << GridPosition[count].x << ", " << GridPosition[count].y << ", " << GridPosition[count].z << " ::::" << GridCost[count] << std::endl;
			x++;
		}
		++y;
	}
	GetDestinationGrid();
	for (int y = 0; y < 20; ++y)
	{
		for (int x = 0; x < 20; ++x)
		{
			std::cout << GridPosition[x][y].x << ", " << GridPosition[x][y].y << ", " << GridPosition[x][y].z << " ::::" << GridCost[x][y] << std::endl;
		}
	}
}

void GridControllerSystem::CheckGridCost(int GridNumX, int GridNumY)
{
	glm::vec3 GridTopLeft = GridPosition[GridNumX][GridNumY];
	glm::vec3 GridBottomRight = glm::vec3(GridTopLeft.x + 50, GridTopLeft.y, GridTopLeft.z - 50);
	for (auto const& entity : m_Entities)
	{
		auto& unit = coordinator.GetComponent<Unit>(entity);
		auto& transform = coordinator.GetComponent<Transform>(entity);
		if (transform.position.x + transform.scale.x>= GridTopLeft.x && transform.position.x + transform.scale.x <= GridBottomRight.x && transform.position.z+ transform.scale.z <= GridTopLeft.z && transform.position.z + transform.scale.z >= GridBottomRight.z)
		{
			GridCost[GridNumX][GridNumY] += unit.FlowFieldCost;
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
		CursorWorldPosition = glm::vec3(CursorScreenPosition.x * (1000 / x), 0, (y - CursorScreenPosition.y) * (1000 / y));
		CreateGrids();
	}
}

void GridControllerSystem::GetDestinationGrid()
{
	// Check Which Grid the destination is at
	glm::vec2 destination = glm::vec2(-1,-1);	// If it is -1 at the end, means that destination is impossible
	for (int y = 0; y < 20; ++y)
	{
		for (int x = 0; x < 20; ++x)
		{
			glm::vec3 GridTopLeft = GridPosition[x][y];
			glm::vec3 GridBottomRight = glm::vec3(GridTopLeft.x + 50, GridTopLeft.y, GridTopLeft.z - 50);
			if (CursorWorldPosition.x >= GridTopLeft.x && CursorWorldPosition.x <= GridBottomRight.x && CursorWorldPosition.z <= GridTopLeft.z && CursorWorldPosition.z >= GridBottomRight.z)
			{
				if (GridCost[x][y] == -1)
				{	// Set The Empty Grid To the Destination Point
					GridCost[x][y] = 0;
					destination.x = x;
					destination.y = y;
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
		CreatePath(destination);
	}
}

void GridControllerSystem::CreatePath(glm::vec2 Destination)
{
	int dX = Destination.x;
	int dY = Destination.y;
	glm::vec3 GridTopLeft = GridPosition[dX][dY];
	glm::vec3 GridBottomRight = glm::vec3(GridTopLeft.x + 50, GridTopLeft.y, GridTopLeft.z - 50);
	// Check at the edge of the world space
	// If not, Check if the grid around it is passable or not
	// World Position is from -500,500 to 500,-500
	for (int y = 0; y < 20; ++y)
	{
		for (int x = 0; x < 20; ++x)
		{
			//North
			if (GridTopLeft.z != 500)
			{
				// There is a Grid in the North Direction!!
				// Check the North Grid ID

				if ((GridPosition[x][y].z == (GridTopLeft.z + 50)) && (GridPosition[x][y].x == GridTopLeft.x) && (GridCost[x][y] == -1)) // Checks if there is grid Cost is uninitialized
				{
					GridCost[x][y] = GridCost[dX][dY] + 1;
				}

			}
			// South
			if (GridBottomRight.z != -500)
			{
				// There is a Grid in the South Direction!!
				// Check the South Grid ID

				if ((GridPosition[x][y].z == GridTopLeft.z - 50) && (GridPosition[x][y].x == GridTopLeft.x) && (GridCost[x][y] == -1)) // Checks if there is grid Cost is uninitialized
				{
					GridCost[x][y] = GridCost[dX][dY] + 1;
				}
			}
			// East
			if (GridBottomRight.x != 500)
			{
				// There is a Grid in the East Direction!
				// Check East Grid ID

				if ((GridPosition[x][y].x == GridBottomRight.x + 50) && (GridPosition[x][y].z == GridTopLeft.z) && (GridCost[x][y] == -1))// Checks if there is grid Cost is uninitialized
				{
					GridCost[x][y] = GridCost[dX][dY] + 1;
				}

			}
			// West
			if (GridTopLeft.x != -500)
			{
				// There is a Grid in the West Direction!
				// Check West Grid ID
				if ((GridPosition[x][y].x == GridTopLeft.x - 50) && (GridPosition[x][y].z == GridTopLeft.z) && (GridCost[x][y]) == -1) // Check if there is grid Cost is uninitialized
				{
					GridCost[x][y] = GridCost[dX][dY] + 1;
				}

			}
		}
	}
}

void GridControllerSystem::SetUp()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<Unit>());
	signature.set(coordinator.GetComponentType<Transform>());
	coordinator.SetSystemSignature<GridControllerSystem>(signature);
}


