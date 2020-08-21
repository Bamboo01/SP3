#include "CanvasImageSystem.h"

void CanvasImageSystem::Setup()
{
    Signature signature;
    signature.set(coordinator.GetComponentType<CanvasImage>());
    signature.set(coordinator.GetComponentType<Transform>());
    coordinator.SetSystemSignature<CanvasImageSystem>(signature);
}

void CanvasImageSystem::Init()
{
    for (auto const& entity : m_Entities)
    {
        auto& canvasimage = coordinator.GetComponent<CanvasImage>(entity);
        if (canvasimage.ImagePath != "")
        {
            canvasimage.TextureID = LoadTGA(canvasimage.ImagePath.c_str());
        }
    }
}

void CanvasImageSystem::Render()
{
    for (auto const& entity : m_Entities)
    {
        auto& transform = coordinator.GetComponent<Transform>(entity);
        auto& canvasimage = coordinator.GetComponent<CanvasImage>(entity);
        if (canvasimage.TextureID == unsigned(-1))
        {
            continue;
        }
        glm::mat4 model(1.f);
        glm::vec3 rot = glm::radians(transform.rotation);
        model = glm::translate(model, transform.position);
        model = glm::rotate(model, rot.x, glm::vec3(1, 0, 0));
        model = glm::rotate(model, rot.y, glm::vec3(0, 1, 0));
        model = glm::rotate(model, rot.z, glm::vec3(0, 0, 1));
        model = glm::scale(model, transform.scale);
        renderer.CanvasImage.push_back(std::make_pair(model, canvasimage.TextureID));
    }
}