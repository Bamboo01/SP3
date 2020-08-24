#include "Transform.h"
#include "CanvasImageUpdate.h"
#include "EntityState.h"
#include "CanvasImage.h"
#include "System.h"
#include "Coordinator.h"
#include "Renderer.h"
#include "Unit.h"
#include "Controller.h"

extern Coordinator coordinator;
extern Renderer renderer;

class CanvasImageUpdateSystem : public System
{
private:

public:
    ~CanvasImageUpdateSystem();
    virtual void Setup();
    virtual void Init(std::set<Entity>* controllerentity);
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
    int increment;

    std::vector<Entity> ReferenceEntity;

    std::vector<Entity> selectedunitList;

    std::set<Entity> *controllerentity;

    unsigned nexustexture;
    unsigned labtexture;
    unsigned generator1texture;
    unsigned generator2texture;
    unsigned towertexture;
    unsigned walltexture;
    unsigned normalunittexture;
    unsigned rangeunittexture;
    unsigned tankunittexture;
};