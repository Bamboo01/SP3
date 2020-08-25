#include "System.h"
#include "Coordinator.h"
#include <vector>
#include "Entity.h"
#include "Coordinator.h"
#include "Transform.h"
#include "RenderData.h"
#include "MenuUnit.h"

extern Coordinator coordinator;
#pragma once

class MenuUnitSystem : public System
{
public:
	void Setup();
	void Init();
	void Update(float dt);
};