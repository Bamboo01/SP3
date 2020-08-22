#include <glm.hpp>
#include "Mesh.h"
#include "Particle.h"
#include <list>
#include <queue>

#pragma once
struct ParticleSystemParameters
{
	Mesh* mesh;

	float particleLifetime;
	float Timer;
	float Gravity;

	bool billboard;
	bool spawnParticles;
	int spawnRate;

	glm::vec3 velMin;
	glm::vec3 velMax;

	glm::vec3 startScale;
	glm::vec3 endScale;

	glm::vec3 startRotate;
	glm::vec3 endRotate;

	glm::vec3 spawnArea;

	std::vector<Particle>ParticleList;
	std::queue<Particle>ParticleQueue;

	ParticleSystemParameters()
	{

	}

	ParticleSystemParameters(
		Mesh* mesh,
		float particlelifetime,
		float timer,
		int spawnrate,
		glm::vec3 velmin,
		glm::vec3 velmax,

		glm::vec3 startscale,
		glm::vec3 endscale,

		glm::vec3 startrotate,
		glm::vec3 endrotate,

		glm::vec3 spawnarea,
		bool billboard = true,
		float gravity = 0.f,
		bool spawnparticles = true
	)
	{
		this->mesh = mesh;
		particleLifetime = particlelifetime;
		Timer = 0;
		Gravity = gravity;
		velMin = velmin;
		velMax = velmax;
		startScale = startscale;
		endScale = endscale;
		startRotate = startrotate;
		endRotate = endrotate;
		spawnArea = spawnarea;
		this->billboard = billboard;
		spawnParticles = spawnparticles;
		spawnRate = spawnrate;
	}
};

