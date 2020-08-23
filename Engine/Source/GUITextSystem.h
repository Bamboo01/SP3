#pragma once
#include "Transform.h"
#include "EntityState.h"
#include "GUIText.h"
#include "CanvasText.h"
#include "System.h"
#include "Coordinator.h"
#include "Unit.h"

extern Coordinator coordinator;

class GUITextSystem : public System
{
private:

public:
    virtual void Setup();
    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();

    void SetSelectedUnitList(std::vector<Entity> selectedunitList);

    void SetUIopen(bool LabUIopen, bool UnitUIopen, bool BuildingUIopen);

private:

    std::vector<Entity> ReferenceEntity;

    std::vector<Entity> selectedunitList;

    bool LabUIopen;
    bool UnitUIopen;
    bool BuildingUIopen;
};
