#include "System.h"
#include "Unit.h"
#include "Transform.h"
#include "Coordinator.h"

extern Coordinator coordinator;

#pragma once
class UnitSystem : public System
{
public:
    virtual void Setup();
    virtual void Init();
    virtual void Update();
};
