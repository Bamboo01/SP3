#include "ParticleSystem.h"

void ParticleSystem::Setup()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<ParticleSystemParameters>());
	signature.set(coordinator.GetComponentType<Transform>());
	signature.set(coordinator.GetComponentType<EntityState>());
	coordinator.SetSystemSignature<ParticleSystem>(signature);
}

void ParticleSystem::Init()
{
	for (auto const& entity : m_Entities)
	{
		auto& particlesystemparameters = coordinator.GetComponent<ParticleSystemParameters>(entity);
		int queuesize = 2 * std::ceil((float)particlesystemparameters.spawnRate* (float)particlesystemparameters.spawnAmount* (float)particlesystemparameters.particle_lifespan);
		for (int i = 0; i < queuesize; i++)
		{
			particlesystemparameters.ParticleQueue.push(Particle());
		}
	}
}

void ParticleSystem::Update(float dt)
{
	for (auto const& entity : m_Entities)
	{
		for (auto const& entity : m_Entities)
		{
			auto& transform = coordinator.GetComponent<Transform>(entity);
			auto& particlesystemparameters = coordinator.GetComponent<ParticleSystemParameters>(entity);
			particlesystemparameters.timer += dt;

			//Check if particle is ready to be spawned
			if (particlesystemparameters.timer > 1.f / (float)particlesystemparameters.spawnRate && particlesystemparameters.spawnParticles)
			{
				for (int i = 0; i < particlesystemparameters.spawnAmount; i++)
				{
					auto& particle = particlesystemparameters.ParticleQueue.front();
					particlesystemparameters.ParticleQueue.pop();

					particle.position = transform.position + glm::linearRand(-0.5f * particlesystemparameters.spawnArea, 0.5f * particlesystemparameters.spawnArea);
					particle.scale = glm::linearRand(particlesystemparameters.min_startScale, particlesystemparameters.max_startScale);
					particle.angularvelocity = glm::linearRand(particlesystemparameters.min_startAngularVelocity, particlesystemparameters.max_startAngularVelocity);
					particle.velocity = glm::linearRand(particlesystemparameters.min_startVelocity, particlesystemparameters.max_startVelocity);
					particle.rotation = glm::linearRand(particlesystemparameters.min_startRotation, particlesystemparameters.max_startRotation);
					particle.lifetime = 0.f;

					particlesystemparameters.ActiveParticleList.push_back(particle);

					particlesystemparameters.timer = 0.f;
				}
			}


			//Update all particles
			for (auto it = particlesystemparameters.ActiveParticleList.begin(); it != particlesystemparameters.ActiveParticleList.end();)
			{
				auto& particle = *it;

				if (particle.lifetime > particlesystemparameters.particle_lifespan || particle.scale.x <= 0 || particle.scale.y <= 0 || particle.scale.z <= 0)
				{
					particle.lifetime = 0;
					particlesystemparameters.ParticleQueue.push(*it);
					it = particlesystemparameters.ActiveParticleList.erase(it);
				}
				else
				{
					particle.lifetime += dt;
					particle.velocity += particlesystemparameters.velocityDecay;
					particle.angularvelocity += particlesystemparameters.angularvelocityDecay;

					particle.position += particle.velocity * dt;
					particle.rotation += particle.angularvelocity * dt;
					particle.scale += particlesystemparameters.scaleDecay * dt;
					++it;
				}
			}
		}
	}
}

void ParticleSystem::Render()
{
	for (auto const& entity : m_Entities)
	{
		auto& particlesystemparameters = coordinator.GetComponent<ParticleSystemParameters>(entity);
		for (auto& particle : particlesystemparameters.ActiveParticleList)
		{
			//Billboarding done inside Shader!!! Be sure to load a mesh that has a billboarding shader!
			//This is so that for every camera, particles face them and aren't limited to just the main camera!
			glm::mat4 modelmat(1.f);
			glm::vec3 rot = glm::radians(particle.rotation);
			modelmat = glm::translate(modelmat, particle.position);
			modelmat = glm::rotate(modelmat, rot.x, glm::vec3(1, 0, 0));
			modelmat = glm::rotate(modelmat, rot.y, glm::vec3(0, 1, 0));
			modelmat = glm::rotate(modelmat, rot.z, glm::vec3(0, 0, 1));
			modelmat = glm::scale(modelmat, particle.scale);
			particlesystemparameters.particle_mesh->DynamicTransformMatrices.push_back(modelmat);
		}
	}
}
