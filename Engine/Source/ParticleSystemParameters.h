#include "Particle.h"
#include <list>
#include <queue>
#include "Mesh.h"

#pragma once

struct ParticleSystemParameters
{
	std::list<Particle> ActiveParticleList;
	std::queue<Particle> ParticleQueue;

	Mesh* particle_mesh;
	float particle_lifespan;

	int spawnRate;
	int spawnAmount;
	float timer;
	float particle_gravity;

	bool spawnParticles;

	glm::vec3 scaleDecay;
	glm::vec3 velocityDecay;
	glm::vec3 angularvelocityDecay;

	glm::vec3 min_startVelocity;
	glm::vec3 max_startVelocity;

	glm::vec3 min_startAngularVelocity;
	glm::vec3 max_startAngularVelocity;

	glm::vec3 min_startScale;
	glm::vec3 max_startScale;

	glm::vec3 min_startRotation;
	glm::vec3 max_startRotation;

	glm::vec3 spawnArea;

	ParticleSystemParameters()
	{

	}

	ParticleSystemParameters(
		Mesh* mesh, float lifespan,
		int spawnrate, int spawnamount,

		//Decay Values
		glm::vec3 scaledecay,
		glm::vec3 veldecay,
		glm::vec3 angveldecay,

		//Starting values
		glm::vec3 minstartvel, glm::vec3 maxstartvel,
		glm::vec3 minstartscale, glm::vec3 maxstartscale,
		glm::vec3 minstartangvel, glm::vec3 maxstartangvel,
		glm::vec3 minstartrot, glm::vec3 maxstartrot,

		glm::vec3 spawnarea = glm::vec3(0.f),
		bool spawnparticles = true,
		float gravity = 0
	)
	{
		particle_mesh = mesh;
		particle_lifespan = lifespan;

		spawnRate = spawnrate;
		spawnAmount = spawnamount;
		timer = 0.f;
		particle_gravity = gravity;
		spawnParticles = spawnparticles;

		spawnArea = spawnarea;

		scaleDecay = scaledecay;
		velocityDecay = veldecay;
		angularvelocityDecay = angveldecay;

		min_startVelocity = minstartvel;
		max_startVelocity = maxstartangvel;

		min_startScale = minstartscale;
		max_startScale = maxstartscale;

		min_startAngularVelocity = minstartangvel;
		max_startAngularVelocity = maxstartangvel;

		min_startRotation = minstartrot;
		max_startRotation = maxstartrot;
	}
};
