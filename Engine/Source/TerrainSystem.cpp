#include "TerrainSystem.h"

void TerrainSystem::Setup()
{
    Signature signature;
    signature.set(coordinator.GetComponentType<RenderData>());
    signature.set(coordinator.GetComponentType<TerrainData>());
    signature.set(coordinator.GetComponentType<Transform>());
    signature.set(coordinator.GetComponentType<EntityState>());
    coordinator.SetSystemSignature<TerrainSystem>(signature);
}

void TerrainSystem::Init()
{
    for (auto const& entity : m_Entities)
    {
        auto& transform = coordinator.GetComponent<Transform>(entity);
        auto& terrain = coordinator.GetComponent<TerrainData>(entity);
        terrain.heightmap = renderer.getHeightMap(renderer.getMesh(terrain.terrain));
        terrain.transform = transform;
    }
}
