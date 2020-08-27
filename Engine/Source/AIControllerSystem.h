#include "AIController.h"
#include "System.h"
#include "Coordinator.h"

extern Coordinator coordinator;
#pragma once

class AIControllerSystem : public System
{
public:
	void Setup();
	void Init();
	void Update(float dt);
};
