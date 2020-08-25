#include "CanvasTextSystem.h"

void CanvasTextSystem::Setup()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<CanvasText>());
	signature.set(coordinator.GetComponentType<Transform>());
	signature.set(coordinator.GetComponentType<EntityState>());
	coordinator.SetSystemSignature<CanvasTextSystem>(signature);
}

void CanvasTextSystem::Render()
{
	for (auto const& entity : m_Entities)
	{
		auto& transform = coordinator.GetComponent<Transform>(entity);
		auto& canvastext = coordinator.GetComponent<CanvasText>(entity);
		glm::mat4 model(1.f);
		glm::vec3 rot = glm::radians(transform.rotation);
		model = glm::translate(model, transform.position);
		model = glm::rotate(model, rot.x, glm::vec3(1, 0, 0));
		model = glm::rotate(model, rot.y, glm::vec3(0, 1, 0));
		model = glm::rotate(model, rot.z, glm::vec3(0, 0, 1));

		model = glm::scale(model, transform.scale + glm::vec3(canvastext.size));

		if (canvastext.Alignment == TEXT_ALIGNMENT::ALIGN_CENTER)
		{
			float length = ((float)canvastext.Text.size() - 1.5f) * 0.5f;
			model = glm::translate(model, -glm::vec3(length, 0, 0));
		}
		else if (canvastext.Alignment == TEXT_ALIGNMENT::ALIGN_RIGHT)
		{
			float length = ((float)canvastext.Text.size() - 1.5f);
			model = glm::translate(model, -glm::vec3(length, 0, 0));
		}

		renderer.CanvasText.push_back(std::make_tuple(model, canvastext.Text, canvastext.color));
	}
}
