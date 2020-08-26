#include "IntroTextSystem.h"
#include "GUIText.h"

void IntroTextSystem::Init()
{
	timer = 0;
	count = 0;
}

void IntroTextSystem::Update(float dt)
{
	timer += 0.5f * dt;

	if (timer > 0 && count == 0)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 1.35, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("computer rebooting...", ALIGN_LEFT));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if(timer > 0.8 && count == 1)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 1.25, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<ERROR> 00G%SK001", ALIGN_LEFT,glm::vec3(1,0,0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 1 && count == 2)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 1.15, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<ERROR> 0$UIS%07^", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 1.3 && count == 3)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 1.05, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("Loading Resources...0%", ALIGN_LEFT));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 2 && count == 4)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 0.95, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("Loading Resources...63%", ALIGN_LEFT));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 2.7 && count == 5)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 0.85, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("Loading Re$o%r&es... 100%", ALIGN_LEFT));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 3 && count == 6)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 0.75, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<ERROR> 7&*UYA_0E", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 3.5 && count == 7)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 0.65, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("Loading Comp&e^t(d...", ALIGN_LEFT));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 3.8 && count == 8)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 0.55, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("ProCe$$inG...", ALIGN_LEFT));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 4 && count == 9)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 0.45, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<ERROR> 8^DJ000E", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 4.5 && count == 10)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 0.35, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("R%b00t su(e$$fu1ly...", ALIGN_LEFT));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 4.8 && count == 11)
	{
		Entity UIText = coordinator.CreateEntity();
		coordinator.AddComponent<Transform>(UIText, Transform());
		coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 0.25, 0);
		coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
		coordinator.AddComponent<CanvasText>(UIText, CanvasText("<ERROR> installing ##082##", ALIGN_LEFT, glm::vec3(1, 0, 0)));
		coordinator.AddComponent<EntityState>(UIText, EntityState());
		++count;
	}
	else if (timer > 5 && count == 12)
	{
	Entity UIText = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(UIText, Transform());
	coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 0.15, 0);
	coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
	coordinator.AddComponent<CanvasText>(UIText, CanvasText("<ERROR> installing ##793##", ALIGN_LEFT, glm::vec3(1, 0, 0)));
	coordinator.AddComponent<EntityState>(UIText, EntityState());
	++count;
	}
	else if (timer > 5.5 && count == 13)
	{
	Entity UIText = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(UIText, Transform());
	coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, 0.05, 0);
	coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
	coordinator.AddComponent<CanvasText>(UIText, CanvasText("<VIRUS DETECTED> &#0&*AQ0", ALIGN_LEFT, glm::vec3(1, 0, 0)));
	coordinator.AddComponent<EntityState>(UIText, EntityState());
	++count;
	}
	else if (timer > 5.8 && count == 14)
	{
	Entity UIText = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(UIText, Transform());
	coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -0.05, 0);
	coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
	coordinator.AddComponent<CanvasText>(UIText, CanvasText("<VIRUS DETECTED> 56&*^PQ", ALIGN_LEFT, glm::vec3(1, 0, 0)));
	coordinator.AddComponent<EntityState>(UIText, EntityState());
	++count;
	}
	else if (timer > 6.5 && count == 15)
	{
	Entity UIText = coordinator.CreateEntity();
	coordinator.AddComponent<Transform>(UIText, Transform());
	coordinator.GetComponent<Transform>(UIText).position = glm::vec3(-1.30, -0.15, 0);
	coordinator.GetComponent<Transform>(UIText).scale = glm::vec3(0.0001, 0.0001, 1);
	coordinator.AddComponent<CanvasText>(UIText, CanvasText("Welc0me to H0L0WAR.EXE...", ALIGN_LEFT));
	coordinator.AddComponent<EntityState>(UIText, EntityState());
	++count;
	}
}
