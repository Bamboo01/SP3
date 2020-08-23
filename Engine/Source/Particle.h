#include "glm.hpp"

#pragma once

struct Particle
{
	float lifetime;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::vec3 velocity;
	glm::vec3 angularvelocity;

	Particle()
	{
		lifetime = 0;
	}
};
