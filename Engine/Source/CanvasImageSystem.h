#include "Transform.h"
#include "CanvasImage.h"
#include "System.h"
#include "Coordinator.h"
#include "Renderer.h"


extern Coordinator coordinator;
extern Renderer renderer;

#pragma once
class CanvasImageSystem : public System
{
private:

public:
    void Setup();
    void Init();
    void Render();
    void Exit();
};