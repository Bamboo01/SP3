#include "CameraControllerSystem.h"
#include "gtc/constants.hpp"

void CameraControllerSystem::Update(float dt)
{
    for (auto const& entity : m_Entities)
    {
        auto& camera = coordinator.GetComponent<Camera>(entity);
        glm::vec3 view = glm::normalize(camera.target - camera.position) * (float)Application::mouse_scroll_y * 3.f;
        camera.position += view * dt * 500.f;
        
        if (Application::mouse_current_x < 50)
        {
            //Camera Move to the Left
            auto& camera = coordinator.GetComponent<Camera>(entity);
            glm::vec3 view = glm::normalize(camera.target - camera.position);
            glm::vec3 right = glm::cross(view, camera.up);
            right.y = 0;
            right = glm::normalize(right);
            camera.position -= right * 500.f * (float)dt;
            camera.target-= right * 500.f * (float)dt;
        }
        if (Application::mouse_current_x > Application::GetWindowWidth() - 50)
        {
            //Camera move to the right
            auto& camera = coordinator.GetComponent<Camera>(entity);
            glm::vec3 view = glm::normalize(camera.target - camera.position);
            glm::vec3 right = glm::cross(view, camera.up);
            right.y = 0;
            right = glm::normalize(right);
            camera.position += right * 500.f * (float)dt;
            camera.target += right * 500.f * (float)dt;
        }
        if (Application::mouse_current_y < 50)
        {
            //Camera move down
            glm::vec3 dir = camera.up;
            dir.y = 0;
            camera.position += dir * 500.f * (float)dt;
            camera.target += dir * 500.f * (float)dt;
        }
        if (Application::mouse_current_y > Application::GetWindowHeight() - 50)
        {
            //Camera move up
            glm::vec3 dir = camera.up;
            dir.y = 0;
            camera.position -= dir * 500.f * (float)dt;
            camera.target -= dir * 500.f * (float)dt;
        }

        if (!scrollUsed && Application::IsMousePressed(2)) // Middle Scroll
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
                    camera.position += right * 0.05f * distanceTraveled.x * (float)dt;
                    //camera.position += camera.up * 1.f * distanceTraveled.x * (float)dt;
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
                    camera.position += right * 0.05f * distanceTraveled.y * (float)dt;
                  //  camera.position += camera.up * 1.f * distanceTraveled.y * (float)dt;
                }
            }

            StartPos.x = Application::mouse_current_x;
            StartPos.y = Application::mouse_current_y;
            scrollUsed = true;

        }
        else if (scrollUsed && Application::IsMousePressed(2)) // Middle Scroll
        {
            //Rotation
            distanceTraveled.x = Application::mouse_current_x - StartPos.x /*- distanceTraveled.x*/;
            distanceTraveled.y = Application::mouse_current_y - StartPos.y /*- distanceTraveled.y*/;
            if (distanceTraveled.x != 0)
            {
                auto& camera = coordinator.GetComponent<Camera>(entity);
                glm::vec3 view = glm::normalize(camera.target - camera.position);
                glm::vec3 right = glm::cross(view, camera.up);
                right.z = 0;
                right = glm::normalize(right);
                camera.position += right * distanceTraveled.x * 0.2f * (float)dt;
            }
            if (distanceTraveled.y != 0)
            {
                auto& camera = coordinator.GetComponent<Camera>(entity);
                glm::vec3 view = glm::normalize(camera.target - camera.position);
                glm::vec3 right = glm::cross(view, camera.up);
                right.z = 0;
                right = glm::normalize(right);
                camera.position += right * distanceTraveled.y  * 0.2f* (float)dt;
            }
        }
        else if (scrollUsed && !Application::IsMousePressed(2))
        {
            scrollUsed = false;
            distanceTraveled = glm::vec3(0, 0, 0);
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
	

