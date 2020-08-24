#include "System.h"
#include "Coordinator.h"
#include "LightSource.h"
#include "Transform.h"
#include "Renderer.h"

#pragma once

extern Coordinator coordinator;
extern Renderer renderer;

class LightingSystem : public System
{
private:
public:
	void Setup();
	void Init();
	void Update(float dt);
};
