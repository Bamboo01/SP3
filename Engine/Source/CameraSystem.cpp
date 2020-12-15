#include "CameraSystem.h"

#include "Application.h"

void CameraSystem::Setup()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<Camera>());
	signature.set(coordinator.GetComponentType<EntityState>());
	coordinator.SetSystemSignature<CameraSystem>(signature);
}

void CameraSystem::Init()
{
	for (auto const& entity : m_Entities)
	{
		auto& camera = coordinator.GetComponent<Camera>(entity);
		camera.target = glm::vec3(0, 0, 50);
		
		camera.FBO = new FrameBufferObject;
		camera.FBO->Init(camera.viewWidth, camera.viewHeight);
		FBOList.push_back(camera.FBO);

		if (
			camera.fragment_file_path.size() > 0 &&
			camera.vertex_file_path.size() > 0
			)
		{
			camera.PostProcessingShader = new Shader(camera.vertex_file_path.c_str(), camera.fragment_file_path.c_str());
			shaderList.push_back(camera.PostProcessingShader);
		}
	}
}

void CameraSystem::Update(float dt)
{
    for (auto const& entity : m_Entities)
    {
        auto& camera = coordinator.GetComponent<Camera>(entity);
        glm::mat4 rot(1.f);
        glm::vec3 rotation = glm::radians(camera.rotation);

        rot = glm::rotate(rot, rotation.x, glm::vec3(1, 0, 0));
        rot = glm::rotate(rot, rotation.y, glm::vec3(0, 1, 0));
        rot = glm::rotate(rot, rotation.z, glm::vec3(0, 0, 1));

        camera.right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), camera.target - camera.position));
        camera.up = glm::cross(camera.target - camera.position, camera.right);
        

        if (camera.mode == CAMERA_MODE::MODE_ORTHOGRAPHIC)
        {
			camera.ViewMatrix = glm::mat4(1.0f);
            camera.ProjectionMatrix = glm::ortho((float)camera.viewWidth * -0.5f, (float)camera.viewWidth * 0.5f, (float)camera.viewHeight * -0.5f, (float)camera.viewHeight * 0.5f, -1000.f, 1000.f);
        }
        else
        {
			camera.ViewMatrix = glm::lookAt(camera.position, camera.target, camera.up);
            camera.ProjectionMatrix = glm::perspective(camera.FOV, (float)(camera.viewWidth / camera.viewHeight), 0.1f, 1000.f);
        }
    }
}

void CameraSystem::Render()
{
	for (auto const& entity : m_Entities)
	{
		auto& camera = coordinator.GetComponent<Camera>(entity);
		bool useShader = (camera.PostProcessingShader);
		renderer.Render(camera, useShader);
	}
	renderer.RenderScreenQuad();
}

void CameraSystem::Exit()
{
	for (auto i : FBOList)
	{
		if (i)
		{
			i->~FrameBufferObject();
		}
	}

	for (auto i : shaderList)
	{
		if (i)
		{
			i->~Shader();
		}
	}
}
