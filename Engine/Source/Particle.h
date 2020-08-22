#include <glm.hpp>

#pragma once

struct Particle
{
	float timer;
	glm::vec3 Position;
	glm::vec3 Scale;
	glm::vec3 Velocity;
	glm::vec3 Rotation;
};
