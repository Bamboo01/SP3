#pragma once
#include "System.h"
#include "Coordinator.h"
#include "glm.hpp"
#include "Transform.h"
#include "CanvasText.h"
#include "SoundController.h"
#include "Application.h"

extern Coordinator coordinator;

class CreditScrollSystem :
	public System
{
private:
	double timer;
	int count;
	CSoundController* cSoundController;
public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void ScrollUpdate();
};

