#include <glm.hpp>
#include <gtc/random.hpp>
#pragma once


struct MenuNexus
{
	float timer;
	float nextBuildTime;

	MenuNexus()
	{
		timer = 0;
		nextBuildTime = nextBuildTime = glm::linearRand(2.f, 7.f);
	}
};
