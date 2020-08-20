#include "CanvasText.h"
#include "System.h"
#include "Transform.h"
#include "CanvasText.h"
#include "Coordinator.h"
#include "Renderer.h"

extern Coordinator coordinator;
extern Renderer renderer;

#pragma once
class CanvasTextSystem : public System
{
private:

public:
	virtual void Setup();
	virtual void Render();
};

