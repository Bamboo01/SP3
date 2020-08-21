#include "GridControllerSystem.h"


void GridControllerSytem::CreateGrids()
{
	int count = 0;
	for (int i = 0; i < 500; ++i)
	{
		GridCost[i] = -1;
	}
	for (int y = 500; y > -500; y -= 50)
	{
		for (int x = -500; x < 500; x += 50)
		{
			GridPosition[count] = glm::vec3(x, 2, y);
			CheckGridCost(count);
			//std::cout << GridPosition[count].x << ", " << GridPosition[count].y << ", " << GridPosition[count].z << " ::::" << GridCost[count] << std::endl;
			count++;
		}
	
	}
}

void GridControllerSytem::CheckGridCost(int GridNum)
{
	glm::vec3 GridTopLeft = GridPosition[GridNum];
	glm::vec3 GridBottomRight = glm::vec3(GridTopLeft.x + 50, GridTopLeft.y, GridTopLeft.z - 50);
	for (auto const& entity : m_Entities)
	{
		auto& unit = coordinator.GetComponent<Unit>(entity);
		auto& transform = coordinator.GetComponent<Transform>(entity);
		if (transform.position.x + transform.scale.x>= GridTopLeft.x && transform.position.x + transform.scale.x <= GridBottomRight.x && transform.position.z+ transform.scale.z <= GridTopLeft.z && transform.position.z + transform.scale.z >= GridBottomRight.z)
		{
			GridCost[GridNum] += unit.FlowFieldCost;
		}
	}
	// Check Which Grid the destination is at
	int destination = -1;	// If it is -1 at the end, means that destination is impossible
	for (int i = 0; i < 500; ++i)
	{
		glm::vec3 GridTopLeft = GridPosition[i];
		glm::vec3 GridBottomRight = glm::vec3(GridTopLeft.x + 50, GridTopLeft.y, GridTopLeft.z - 50);
		if (CursorWorldPosition.x >= GridTopLeft.x && CursorWorldPosition.x <= GridBottomRight.x && CursorWorldPosition.z <= GridTopLeft.z && CursorWorldPosition.z >= GridBottomRight.z)
		{
			if (GridCost[i] == -1)
			{	// Set The Empty Grid To the Destination Point
				GridCost[i] = 0;
				destination = i;
				break;
			}
			else
				break;		// If there is a wall at the destination point, Destination is impossible to reach
		}
	}
	if (destination != -1)
	{
		// A Grid that has been selected
		CreatePath(destination);
	}
}


void GridControllerSytem::Update(float dt)
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

void GridControllerSytem::CreatePath(int Destination)
{
	glm::vec3 GridTopLeft = GridPosition[Destination];
	glm::vec3 GridBottomRight = glm::vec3(GridTopLeft.x + 50, GridTopLeft.y, GridTopLeft.z - 50);
	// Check at the edge of the world space
	// If not, Check if the grid around it is passable or not
	// World Position is from -500,500 to 500,-500

	//North
	if (GridTopLeft.z != 500)
	{
		// There is a Grid in the North Direction!!
		// Check the North Grid ID
		for (int i = 0; i < 500; ++i)
		{
			if ((GridPosition[i].z == (GridTopLeft.z + 50)) && (GridPosition[i].x == GridTopLeft.x) && (GridCost[i] == -1)) // Checks if there is grid Cost is uninitialized
			{
				GridCost[i] = GridCost[Destination] + 1;
				std::cout << GridCost[i] << std::endl;
				CreatePath(i);
				break;
			}
		}
	}
	// South
	if (GridBottomRight.z != -500)
	{
		// There is a Grid in the South Direction!!
		// Check the South Grid ID
		for (int i = 0; i < 500; ++i)
		{
			if ((GridPosition[i].z == GridTopLeft.z - 50) && (GridPosition[i].x == GridTopLeft.x) && (GridCost[i] == -1)) // Checks if there is grid Cost is uninitialized
			{
				GridCost[i] = ++GridCost[Destination];
				CreatePath(i);
				break;
			}
		}
	}
	// East
	if (GridBottomRight.x != 500)
	{
		// There is a Grid in the East Direction!
		// Check East Grid ID
		for (int i = 0; i < 500; ++i)
		{
			if ((GridPosition[i].x == GridBottomRight.x + 50) && (GridPosition[i].z == GridTopLeft.z) && (GridCost[i] == -1))// Checks if there is grid Cost is uninitialized
			{
				GridCost[i] = ++GridCost[Destination];
				CreatePath(i);
				break;
			}
		}
	}
	// West
	if (GridTopLeft.x != -500)
	{
		// There is a Grid in the West Direction!
		// Check West Grid ID
		for (int i = 0; i < 500; ++i)
		{
			if ((GridPosition[i].x == GridTopLeft.x - 50) && (GridPosition[i].z == GridTopLeft.z) && (GridCost[i]) == -1) // Check if there is grid Cost is uninitialized
			{
				GridCost[i] = ++GridCost[Destination];
				CreatePath(i);
				break;
			}
		}
	}
	
}

void GridControllerSytem::SetUp()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<Unit>());
	signature.set(coordinator.GetComponentType<Transform>());
	coordinator.SetSystemSignature<GridControllerSytem>(signature);
}


