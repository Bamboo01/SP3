#include "ParticleSystemParameters.h"
#include "System.h"

#pragma once
class ParticleSystem : public System
{
private:
public:
	virtual void Setup();w
	virtual void Init();
	virtual void Update(float dt);
	virtual void Render();
};

