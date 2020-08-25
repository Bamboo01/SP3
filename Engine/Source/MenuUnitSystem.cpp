#include "MenuUnitSystem.h"

void MenuUnitSystem::Setup()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<Transform>());
	signature.set(coordinator.GetComponentType<EntityState>());
	signature.set(coordinator.GetComponentType<MenuUnit>());
	signature.set(coordinator.GetComponentType<RenderData>());
	coordinator.SetSystemSignature<MenuUnitSystem>(signature);
}

void MenuUnitSystem::Init()
{
}

void MenuUnitSystem::Update(float dt)
{
	for (const auto& entity : m_Entities)
	{
		auto& transform = coordinator.GetComponent<Transform>(entity);
		transform.position += 3.f * dt * transform.AxisZ;
	}
}
