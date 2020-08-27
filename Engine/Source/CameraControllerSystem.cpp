#include "CameraControllerSystem.h"
#include "gtc/constants.hpp"
#include "Application.h"
#include "SoundController.h"

void CameraControllerSystem::Update(float dt)
{
    for (auto const& entity : m_Entities)
    {
        auto& camera = coordinator.GetComponent<Camera>(entity);

        if (camera.type == CAMERA_MAIN)
        {
            CSoundController::GetInstance()->SetListenerPosition(camera.position.x, camera.position.y, camera.position.z);
            CSoundController::GetInstance()->SetListenerDirection(0, 0, 1);

            if (glm::length(camera.position - camera.target) > 100.f && Application::mouse_scroll_y > 0)
            {
                glm::vec3 view = glm::normalize(camera.target - camera.position) * (float)Application::mouse_scroll_y * 3.f;
                camera.position += view * dt * 100.f;
            }
            if (glm::length(camera.position - camera.target) < 300.f && Application::mouse_scroll_y < 0)
            {
                glm::vec3 view = glm::normalize(camera.target - camera.position) * (float)Application::mouse_scroll_y * 3.f;
                camera.position += view * dt * 100.f;
            }

            if (Application::mouse_current_x < 50)
            {
                //Camera Move to the Left
                if (camera.position.x < 200)
                {
                    camera.position += camera.right * 100.f * dt;
                    camera.target += camera.right * 100.f * dt;
                }
            }
            if (Application::mouse_current_x > Application::GetWindowWidth() - 50)
            {
                //Camera move to the right
                if (camera.position.x > -200)
                {
                    camera.position -= camera.right * 100.f * dt;
                    camera.target -= camera.right * 100.f * dt;
                }
            }
            if (Application::mouse_current_y < 50)
            {
                //Camera move down
                if (camera.position.z < 200)
                {
                    glm::vec3 dir = camera.up;
                    dir.y = 0;
                    camera.position += dir * 0.5f * (float)dt;
                    camera.target += dir * 0.5f * (float)dt;
                }
            }
            if (Application::mouse_current_y > Application::GetWindowHeight() - 50)
            {
                //Camera move up
                if (camera.position.z > -300)
                {
                    glm::vec3 dir = camera.up;
                    dir.y = 0;
                    camera.position -= dir * 0.5f * (float)dt;
                    camera.target -= dir * 0.5f * (float)dt;
                }
            }

            if (!scrollUsed && Application::IsMousePressed(2)) // Middle Scroll
            {

                // auto& camera = coordinator.GetComponent<Camera>(entity);
                if (distanceTraveled.x != 0)
                {
                    /*for (auto const& entity : m_Entities)
                    {*/
                    //  auto& camera = coordinator.GetComponent<Camera>(entity);
                   /*   glm::vec3 view = glm::normalize(camera.target - camera.position);
                      glm::vec3 right = glm::cross(view, camera.up);
                      right.y = 0;
                      right = glm::normalize(right);
                      camera.position += right * 0.05f * distanceTraveled.x * (float)dt;*/
                      //  }
                    camera.position += camera.right * 1.f * dt * distanceTraveled.x;
                }
                if (distanceTraveled.y != 0)
                {
                    /* for (auto const& entity : m_Entities)
                     {*/
                     //     auto& camera = coordinator.GetComponent<Camera>(entity);
                         /* glm::vec3 view = glm::normalize(camera.target - camera.position);
                          glm::vec3 right = glm::cross(view, camera.up);
                          right.y = 0;
                          right = glm::normalize(right);
                          camera.position += right * 0.05f * distanceTraveled.y * (float)dt;*/
                    camera.position += camera.right * 1.f * dt * distanceTraveled.y;

                    // }
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
                    //  auto& camera = coordinator.GetComponent<Camera>(entity);
                    glm::vec3 view = glm::normalize(camera.target - camera.position);
                    glm::vec3 right = glm::cross(view, camera.up);
                    right.y = 0;
                    right = glm::normalize(right);
                    camera.position += right * distanceTraveled.x * 0.05f * (float)dt;
                }
                if (distanceTraveled.y != 0)
                {
                    // auto& camera = coordinator.GetComponent<Camera>(entity);
                    glm::vec3 view = glm::normalize(camera.target - camera.position);
                    glm::vec3 right = glm::cross(view, camera.up);
                    right.y = 0;
                    right = glm::normalize(right);
                    camera.position += right * distanceTraveled.y * 0.05f * (float)dt;
                }
            }
            else if (scrollUsed && !Application::IsMousePressed(2))
            {
                scrollUsed = false;
                distanceTraveled = glm::vec3(0, 0, 0);
            }
            //MINIMAP BOX
            glm::mat4 model(1.0);
            if (0.2 * camera.position.x > -50 && 0.2 * camera.position.x < 50 && 0.25 * camera.position.z > -50 && 0.25 * camera.position.z < 50)
            {
                model = glm::translate(model, glm::vec3(0.2 * camera.position.x, 300, 0.25*camera.position.z));
            }
            else if (0.2 * camera.position.x > -50 && 0.2 * camera.position.x < 50 && 0.25 * camera.position.z < 50)
            {
                model = glm::translate(model, glm::vec3(0.2 * camera.position.x, 300, -50));
            }
            else if (0.2 * camera.position.x > -50 && 0.2 * camera.position.x < 50 && 0.25 * camera.position.z > -50)
            {
                model = glm::translate(model, glm::vec3(0.2 * camera.position.x, 300, 50));
            }
            else if (0.2 * camera.position.x > -50&& 0.25 * camera.position.z > -50 && 0.25 * camera.position.z < 50)
            {
                model = glm::translate(model, glm::vec3(50, 300, 0.25 * camera.position.z));
            }
            else if (0.2 * camera.position.x < 50 && 0.25 * camera.position.z > -50 && 0.25 * camera.position.z < 50)
            {
                model = glm::translate(model, glm::vec3(-50, 300, 0.25 * camera.position.z));
            }
            else if (0.2 * camera.position.x < 50 && 0.25 * camera.position.z > -50)
            {
                model = glm::translate(model, glm::vec3(-50, 300, 50));
            }
            else if (0.2 * camera.position.x < 50 && 0.25 * camera.position.z < 50)
            {
                model = glm::translate(model, glm::vec3(-50, 300, -50));
            }
            else if (0.2 * camera.position.x > -50 && 0.25 * camera.position.z  > -50)
            {
                model = glm::translate(model, glm::vec3(50, 300, 50));
            }
            else if (0.2 * camera.position.x < 50 && 0.25 * camera.position.z < 50)
            {
                model = glm::translate(model, glm::vec3(-50, 300, -50));
            }
            model = glm::rotate(model, glm::radians(-90.f), glm::vec3(1, 0, 0));
            model = glm::scale(model, glm::vec3(18, 18, 0));
           
            renderer.getMesh(GEO_MINIMAPBOX)->DynamicTransformMatrices.push_back(model);

        }
    }
}

void CameraControllerSystem::Setup()
{
    Signature signature;
    signature.set(coordinator.GetComponentType<Camera>());
    signature.set(coordinator.GetComponentType<CameraController>());
    signature.set(coordinator.GetComponentType<EntityState>());
    coordinator.SetSystemSignature<CameraControllerSystem>(signature);
}


