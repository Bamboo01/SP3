#pragma once
#include "Controller.h"
#include "System.h"
#include "Coordinator.h"
#include "Unit.h"

extern Coordinator coordinator;

#pragma once
class ControllerSystem : public System
{
public:
    virtual void Setup();
    virtual void Init(std::set<Entity>* colliderentitylist);
    virtual void Update(double dt);

private:

    std::set<Entity>* colliderentitylist;

};