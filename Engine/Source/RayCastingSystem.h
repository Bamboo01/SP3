#pragma once
#include "System.h"
#include "Transform.h"
#include "RayCasting.h"
#include "Coordinator.h"
#include "Collider.h"
#include "RenderData.h"
#include "TerrainData.h"
#include "Unit.h"
#include "QuadTreeSystem.h"
#include "UnitSystem.h"
#include "Controller.h"
#include "Renderer.h"
extern Renderer renderer;
extern Coordinator coordinator;

#pragma once
class RayCastingSystem : public System
{
public:
    
    virtual void Setup();
    virtual void Init(std::set<Entity>* colliderentitylist, std::set<Entity>* controllerentitylist);
    virtual void Update(double dt);
    virtual void Render();

    bool raycollisioncheck(Entity ray, Entity obj);
    bool rayplanecheck(glm::vec3 rPos, glm::vec3 axis, Transform object, Collider collider);
    void callRayCollision();
    
    void unitSelection();

    void SetTerrainEntities(std::set<Entity> terrain);

    void GetCursorInGUI(bool cursoringui);
    
    std::vector<int> Gridcost;

    std::vector<Entity> selectedunitlist;

    glm::vec3 calculateMouseRay();
    glm::vec2 cursorOnHeightMapPosition;

    void SetUnitSystem(std::shared_ptr<UnitSystem> system);
    void SetQuadTreeSystem(std::shared_ptr<QuadTreeSystem> system);

    int selectedbuilding; // 0 = None, 1 = tower, 2 = wall, 3 = gen1, 4 = gen2
    double buildingclickdelay;

private:
    glm::vec2 getNormalizedDeviceCoords(double mousex, double mousey);
    glm::vec3 toWorldCoords(glm::vec4 clipCoords);

    std::set<Entity> TerrainEntities;

    std::set<Entity> *colliderentitylist;
    std::set<Entity>* controllerentitylist;

    glm::vec3 firstposclick;
    glm::vec3 secondposclick;

    bool CursorInGUI;

    float maxX, minX;
    float maxZ, minZ;

    int unitlimit;

    double timer;

    std::shared_ptr<QuadTreeSystem> quadTreeSystem;
    std::shared_ptr<UnitSystem> unitsystem;
};