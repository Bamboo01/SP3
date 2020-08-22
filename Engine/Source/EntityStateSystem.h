#include "EntityState.h"
#include "System.h"
#include "Coordinator.h"
#pragma once

extern Coordinator coordinator;

class EntityStateSystem : public System
{
private:
    std::vector<Entity> InactiveEntities;
public:
    virtual void Setup();
    virtual void Init();
    virtual void Update(float dt);
};