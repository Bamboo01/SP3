#include "System.h"
#include "Coordinator.h"
#include "Transform.h"
#include "Camera.h"

extern Coordinator coordinator;
#pragma once

class MenuCameraSystem : public System
{
public:
	void Setup();
	void Init();
	void Update(float dt);
};
