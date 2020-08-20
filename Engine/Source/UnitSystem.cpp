#include "UnitSystem.h"
#include <iostream>
#include "Application.h"

void UnitSystem::Setup()
{
    Signature signature;
    signature.set(coordinator.GetComponentType<Transform>());
    signature.set(coordinator.GetComponentType<Unit>());
    coordinator.SetSystemSignature<UnitSystem>(signature);
}

void UnitSystem::Init()
{
    for (auto const& entity : m_Entities)
    {
        auto& unit = coordinator.GetComponent<Unit>(entity);
        auto& transform = coordinator.GetComponent<Transform>(entity);

        glm::mat4 mrot(1.f);

        glm::vec3 rotation = glm::radians(transform.rotation);

        mrot = glm::mat4(1.f);
        mrot = glm::rotate(mrot, rotation.x, glm::vec3(1, 0, 0));
        mrot = glm::rotate(mrot, rotation.y, glm::vec3(0, 1, 0));
        mrot = glm::rotate(mrot, rotation.z, glm::vec3(0, 0, 1));

        transform.AxisX = glm::vec3(mrot * glm::vec4(1, 0, 0, 0.f));
        transform.AxisY = glm::vec3(mrot * glm::vec4(0, 1, 0, 0.f));
        transform.AxisZ = glm::vec3(mrot * glm::vec4(0, 0, 1, 0.f));
    }
}

void UnitSystem::Update()
{
    for (auto const& entity : m_Entities)
    {
        auto& unit = coordinator.GetComponent<Unit>(entity);
        Signature sig = coordinator.GetEntitySignature(entity);
        if (Application::IsKeyPressed('Q'))
        {
            unit.Level++;
        }
    }
}
