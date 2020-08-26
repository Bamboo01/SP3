#include "MenuNexusSystem.h"
#include "MenuUnit.h"
#include "gtc/random.hpp"

void MenuNexusSystem::Setup()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<ParticleSystemParameters>());
	signature.set(coordinator.GetComponentType<Transform>());
	signature.set(coordinator.GetComponentType<EntityState>());
	signature.set(coordinator.GetComponentType<MenuNexus>());
	signature.set(coordinator.GetComponentType<RenderData>());
	coordinator.SetSystemSignature<MenuNexusSystem>(signature);
}

void MenuNexusSystem::Init()
{
	for (int i = 0; i < 100; i++)
	{
		Entity unit = coordinator.CreateEntity();
		UnitQueue.push_back(unit);
		int unittype = glm::linearRand(0, 2);
		RenderData rd;
		switch (unittype)
		{
		case 0:
			rd = RenderData(renderer.getMesh(GEO_MENU_UNIT1), false);
			break;
		case 1:
			rd = RenderData(renderer.getMesh(GEO_MENU_UNIT2), false);
			break;
		case 2:
			rd = RenderData(renderer.getMesh(GEO_MENU_UNIT3), false);
			break;
		default:
			rd = RenderData(renderer.getMesh(GEO_MENU_UNIT1), false);
			break;
		}
		coordinator.AddComponent<RenderData>(unit, rd);
		coordinator.AddComponent<Transform>(unit, Transform());
		coordinator.AddComponent<EntityState>(unit, EntityState());
		coordinator.AddComponent<MenuUnit>(unit, MenuUnit());
		coordinator.GetComponent<EntityState>(unit).active = false;
	}
}

void MenuNexusSystem::Update(float dt)
{
	for (const auto& entity : m_Entities)
	{
		auto& menunexus = coordinator.GetComponent<MenuNexus>(entity);
		menunexus.timer += dt;

		if (menunexus.timer >= menunexus.nextBuildTime)
		{
			menunexus.timer = 0.f;
			menunexus.nextBuildTime = glm::linearRand(2.f, 7.f);

			Entity nextUnit = UnitQueue.back();
			UnitQueue.pop_back();
			ActiveUnits.push_back(nextUnit);
			coordinator.GetComponent<EntityState>(nextUnit).active = true;

			auto& nextunittransform = coordinator.GetComponent<Transform>(nextUnit);
			auto& transform = coordinator.GetComponent<Transform>(entity);
			nextunittransform = transform;
		}

		for (auto unitentity = ActiveUnits.begin(); unitentity < ActiveUnits.end();)
		{
			auto& transform = coordinator.GetComponent<Transform>(entity);
			auto& unittransform = coordinator.GetComponent<Transform>(*unitentity);

			if (glm::length(transform.position - unittransform.position) > 100.f)
			{
				coordinator.GetComponent<EntityState>(*unitentity).active = false;
				coordinator.GetComponent<Transform>(*unitentity).position = transform.position;
				unitentity = ActiveUnits.erase(unitentity);
				UnitQueue.push_back(*unitentity);
				std::cout << "despawn! " << UnitQueue.size() << std::endl;
			}
			else
			{
				++unitentity;
			}
		}
	}
}
