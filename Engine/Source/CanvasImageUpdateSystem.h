#include "Transform.h"
#include "CanvasImageUpdate.h"
#include "EntityState.h"
#include "CanvasImage.h"
#include "System.h"
#include "Coordinator.h"
#include "Renderer.h"
#include "Unit.h"

extern Coordinator coordinator;
extern Renderer renderer;

class CanvasImageUpdateSystem : public System
{
private:

public:
    virtual void Setup();
    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();

    void SetSelectedUnitList(std::vector<Entity> selectedunitList);

    bool CursorinGUI;

    bool LabUIopen;
    bool UnitUIopen;
    bool BuildingUIopen;

private:

    bool CollideWithCanvas(float x, float y, float xscale, float yscale);

    double timer;
    double clickdelay;
    bool renderonce;
    int renderamount;

    std::vector<Entity> ReferenceEntity;

    std::vector<Entity> selectedunitList;
};