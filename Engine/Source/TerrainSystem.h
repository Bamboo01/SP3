#include "System.h"
#include "Coordinator.h"
#include "Renderer.h"
#include "RenderData.h"
#include "Transform.h"
#include "TerrainData.h" 

#pragma once

extern Coordinator coordinator;
extern Renderer renderer;

class TerrainSystem : public System
{
public:
    virtual void Setup();
    virtual void Init();
};