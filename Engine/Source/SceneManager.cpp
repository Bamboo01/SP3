#include "SceneManager.h"
#include "SceneTest.h"
#include "SceneIntro.h"
#include "SceneCombat.h"
#include "SceneMenu.h"
#include "SceneCredit.h"
#include "SceneCamera.h"

SceneManager::SceneManager()
{
	sceneList[SCENE_TEST] = new SceneTest;
	sceneList[SCENE_COMBAT] = new SceneCombat;
	sceneList[SCENE_MENU] = new SceneMenu;
	sceneList[SCENE_INTRO] = new SceneIntro;
	sceneList[SCENE_CREDIT] = new SceneCredit;
	sceneList[SCENE_CAMERA] = new SceneCamera;
	scene = nullptr;
	swap = false;
}


void SceneManager::Init(Scene** s)
{
	scene = s;
}


void SceneManager::ChangeScene(SCENE_TYPE scenetype)
{
	swap = true;
	currentScene = scenetype;
}

void SceneManager::Update()
{
	if (swap == true)
	{
		if (*scene)
		{
			(*scene)->Exit();
			delete* scene;
			*scene = nullptr;
		}
		*scene = sceneList[currentScene]->Clone();
		(*scene)->Init();
		(*scene)->EarlyUpdate(0);
		(*scene)->Update(0);
		(*scene)->LateUpdate(0);
		swap = false;
	}
}

SceneManager* SceneManager::getInstance()
{
	if (!instance)
	{
		instance = new SceneManager;
	}
	return instance;
}

SceneManager::~SceneManager()
{
	for (auto s : sceneList)
	{
		delete s;
	}
}