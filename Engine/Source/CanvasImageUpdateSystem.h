#include "Transform.h"
#include "CanvasImageUpdate.h"
#include "CanvasImage.h"
#include "System.h"
#include "Coordinator.h"
#include "Renderer.h"
#include "UnitSystem.h"

extern Coordinator coordinator;
extern Renderer renderer;

#pragma once
class CanvasImageUpdateSystem : public System
{
private:

public:
	virtual void Setup();
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();

	void SetUnitSystem(std::shared_ptr<UnitSystem> unitsystem);

private:

	bool CollideWithCanvas(float x, float y, float xscale, float yscale);

	double timer;
	double clickdelay;

	std::shared_ptr<UnitSystem> unitsystem;
};

