#include "CameraControllerSystem.h"

void CameraControllerSystem::Update(float dt)
{
    if (Application::mouse_current_x < 50)
    {
        //Camera Move to the Left
        for (auto const& entity : m_Entities)
        {
            auto& camera = coordinator.GetComponent<Camera>(entity);
            glm::vec3 view = glm::normalize(camera.target - camera.position);
            glm::vec3 right = glm::cross(view, camera.up);
            right.y = 0;
            right = glm::normalize(right);
            camera.position -= right * 1.f * (float)dt;
            camera.target -= right * 1.f * (float)dt;
        }
    }
    if (Application::mouse_current_x > Application::GetWindowWidth() - 50)
    {
        //Camera move to the right
        for (auto const& entity : m_Entities)
        {
            auto& camera = coordinator.GetComponent<Camera>(entity);
            glm::vec3 view = glm::normalize(camera.target - camera.position);
            glm::vec3 right = glm::cross(view, camera.up);
            right.y = 0;
            right = glm::normalize(right);
            camera.position += right * 1.f * (float)dt;
            camera.target += right * 1.f * (float)dt;
        }
    }
    if (Application::mouse_current_y < 50)
    {
        for (auto const& entity : m_Entities)
        {
            //Camera move Down
            auto& camera = coordinator.GetComponent<Camera>(entity);
           
            camera.position += camera.up * 1.f * (float)dt;
            camera.target += camera.up * 1.f * (float)dt;
        }

    }
    if (Application::mouse_current_y > Application::GetWindowHeight() - 50)
    {
        //Camera move up
        for (auto const& entity : m_Entities)
        {
            auto& camera = coordinator.GetComponent<Camera>(entity);
        
            camera.position -= camera.up * 1.f * (float)dt;
            camera.target -= camera.up * 1.f * (float)dt;
        }
    }

    if (!scrollUsed && Application::IsMousePressed(2)) // Middle Scroll
    {
        StartPos.x = Application::mouse_current_x;
        StartPos.y = Application::mouse_current_y;
        scrollUsed = true;
    }
    else if (scrollUsed && Application::IsMousePressed(2)) // Middle Scroll
    {
        //Rotation
        distanceTraveled.x = Application::mouse_current_x - StartPos.x /*- distanceTraveled.x*/;
        distanceTraveled.y = Application::mouse_current_y - StartPos.y /*- distanceTraveled.y*/;
        for (auto const& entity : m_Entities)
        {
            auto& camera = coordinator.GetComponent<Camera>(entity);
            if (distanceTraveled.x != 0)
            {
                for (auto const& entity : m_Entities)
                {
                    auto& camera = coordinator.GetComponent<Camera>(entity);
                    glm::vec3 view = glm::normalize(camera.target - camera.position);
                    glm::vec3 right = glm::cross(view, camera.up);
                    right.y = 0;
                    right = glm::normalize(right);
                    camera.position += right * 0.2f * distanceTraveled.x * (float)dt;
                }
            }
            if (distanceTraveled.y != 0)
            {
                for (auto const& entity : m_Entities)
                {
                    auto& camera = coordinator.GetComponent<Camera>(entity);
                    glm::vec3 view = glm::normalize(camera.target - camera.position);
                    glm::vec3 right = glm::cross(view, camera.up);
                    right.y = 0;
                    right = glm::normalize(right);
                    camera.position += right * 0.2f * distanceTraveled.y * (float)dt;
                }
            }
        }

    }
    else if (scrollUsed && !Application::IsMousePressed(2))
    {
        scrollUsed = false;
        distanceTraveled = glm::vec3(0, 0, 0);
    }


    if (Application::mouse_scroll_y > 0)
    {
        for (auto const& entity : m_Entities)
        {

            auto& camera = coordinator.GetComponent<Camera>(entity);
            if (fZoom < 25)
            {
                fZoom += Application::mouse_scroll_y;
                glm::vec3 view = glm::normalize(camera.target - camera.position);
                glm::vec3 right = glm::cross(view, camera.up);
                view = (float)Application::mouse_scroll_y * 3.f * glm::normalize(view);
                right = glm::normalize(right);
                camera.position += view;
            }
        }
    }

    if (Application::mouse_scroll_y < 0)
    {

        for (auto const& entity : m_Entities)
        {

            auto& camera = coordinator.GetComponent<Camera>(entity);
            if (fZoom > 0)
            {
                fZoom += Application::mouse_scroll_y;
                glm::vec3 view = glm::normalize(camera.target - camera.position);
                view = (float) Application::mouse_scroll_y * 3.f * glm::normalize(view);
                glm::vec3 right = glm::cross(view, camera.up);
                right = glm::normalize(right);
                camera.position += view;
            }
        }
    }

}

void CameraControllerSystem::Setup()
{
    Signature signature;
    signature.set(coordinator.GetComponentType<Camera>());
    signature.set(coordinator.GetComponentType<CameraController>());
    coordinator.SetSystemSignature<CameraControllerSystem>(signature);
}
	

