#pragma once
#include "Light.h"

struct LightSource
{
	//Handler to light in the lighting manager
	unsigned lightID;
	Light light;
};
