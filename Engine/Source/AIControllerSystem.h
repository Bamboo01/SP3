#include "AIController.h"
#include "System.h"
#include "Coordinator.h"
#include "UnitSystem.h"

extern Coordinator coordinator;
#pragma once

class AIControllerSystem : public System
{
public:
	void Setup();
	void Init();
	void Update(float dt);

	void SetUnitSystem(std::shared_ptr<UnitSystem> system);

private:

	std::shared_ptr<UnitSystem> unitsystem;
};
