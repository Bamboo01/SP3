#pragma once
#include "System.h"
#include "Transform.h"
#include "RayCasting.h"
#include "Coordinator.h"
#include "Application.h"
#include "LoadHmap.h"

extern Coordinator coordinator;

#pragma once
class RayCastingSystem : public System
{
public:
    virtual void Setup();
    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();

private:
    glm::vec3 calculateMouseRay();
    glm::vec2 getNormalizedDeviceCoords(double mousex, double mousey);
    glm::vec3 toWorldCoords(glm::vec4 clipCoords);
};