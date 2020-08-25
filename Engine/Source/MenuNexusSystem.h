#include "System.h"
#include <vector>
#include "Entity.h"
#include "Coordinator.h"
#include "Transform.h"
#include "ParticleSystemParameters.h"
#include "RenderData.h"
#include "MenuNexus.h"

extern Coordinator coordinator;
#pragma once

class MenuNexusSystem : public System
{
public:
	float timer;
	std::vector<Entity> UnitQueue;
	std::vector<Entity> ActiveUnits;
	void Setup();
	void Init();
	void Update(float dt);
};