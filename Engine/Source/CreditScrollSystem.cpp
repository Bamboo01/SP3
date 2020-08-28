#include "CreditScrollSystem.h"
#include "SceneManager.h"

void CreditScrollSystem::Init()
{
	timer = 0;
	count = 0;
	cSoundController = CSoundController::GetInstance();
	cSoundController->PlaySoundByID(700);
}

void CreditScrollSystem::Update(float dt)
{
	timer += 0.5f * dt;
	
	if (timer > 0 && count == 0)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 1.35, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<ESCAPE> Back to Main Menu", ALIGN_LEFT,glm::vec3(1.f,1.0f,1.0f),0.08f));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 2 && count == 1)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-0.4f, 0, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("H0LOWARS", ALIGN_LEFT, glm::vec3(1.f, 1.0f, 1.0f), 0.2));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}

	else if (timer > 4 && count == 2)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(0.f, 0, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("SHERWYN LOW YUEN KAI", ALIGN_CENTER, glm::vec3(1.f, 1.0f, 1.0f), 0.15));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;

	}

	else if (timer > 6 && count == 3)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(0.f, 0, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("MA WEN XI", ALIGN_CENTER, glm::vec3(1.f, 1.0f, 1.0f), 0.15));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;

	}

	else if (timer > 8 && count == 4)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(0.f, 0, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("WOO GUANG THENG", ALIGN_CENTER, glm::vec3(1.f, 1.0f, 1.0f), 0.15));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;

	}

	else if (timer > 10 && count == 5)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(0.f, 0, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("LOW YAN TONG, GLENDA", ALIGN_CENTER, glm::vec3(1.f, 1.0f, 1.0f), 0.15));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;

	}

	else if (timer > 12 && count == 6)
	{
		timer = 0;
		count = 0;
	}

	for (auto& a : m_Entities)
	{
		auto& text = coordinator.GetComponent<CanvasText>(a);
		auto& scroll = coordinator.GetComponent<Transform>(a);
		if (text.color.r > 0 && text.color.g > 0 && text.color.b > 0)
		{
			text.color.r -= 0.005f;
			text.color.g -= 0.005f;
			text.color.b -= 0.005f;
		}
	}

	if (Application::IsKeyPressed(VK_ESCAPE))
	{
		cSoundController->StopAllSounds();
		SceneManager::getInstance()->ChangeScene(SCENE_MENU);
	}
}

void CreditScrollSystem::ScrollUpdate()
{
	for (auto& a : m_Entities)
	{
		auto& scroll = coordinator.GetComponent<Transform>(a);
		auto& text = coordinator.GetComponent<CanvasText>(a);

		scroll.position.y += 0.1;
	}
}
