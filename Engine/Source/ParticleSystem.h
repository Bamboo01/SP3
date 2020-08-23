#include "ParticleSystemParameters.h"
#include "System.h"
#include "Transform.h"
#include "Coordinator.h"
#include "Renderer.h"
#include <gtc/random.hpp>

extern Coordinator coordinator;
extern Renderer renderer;

#pragma once
class ParticleSystem : public System
{
private:
public:
	virtual void Setup();
	virtual void Init();
	virtual void Update(float dt);
	virtual void Render();
};

