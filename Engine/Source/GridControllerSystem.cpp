#include "GridControllerSystem.h"


void GridControllerSytem::CreateGrids()
{
	int count = 0;
	for (int y = 500; y > -500; y -= 50)
	{
		for (int x = -500; x < 500; x += 50)
		{
			GridPosition[count] = glm::vec3(x, 2, y);
			std::cout << GridPosition[count].x << ", " << GridPosition[count].y << ", " << GridPosition[count].z << std::endl;
			count++;
		}
		rendered = false;
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

void GridControllerSytem::SetUp()
{
	Signature signature;
	coordinator.SetSystemSignature<GridControllerSytem>(signature);
}


