#pragma once
#include "System.h"
#include "Transform.h"
#include "RayCasting.h"
#include "Coordinator.h"
#include "Collider.h"
#include "RenderData.h"
#include "TerrainData.h"

#include "Renderer.h"
extern Renderer renderer;
extern Coordinator coordinator;

#pragma once
class RayCastingSystem : public System
{
public:

    
    virtual void Setup();
    virtual void Init(std::set<Entity>* colliderentitylist);
    virtual void Update(double dt);
    virtual void Render();

 

    bool raycollisioncheck(Entity ray, Entity obj);
    bool rayplanecheck(glm::vec3 rPos, glm::vec3 axis, Transform object, Collider collider);
    void callRayCollision();
    
    void unitSelection();

    void SetTerrainEntities(std::set<Entity> terrain);

    void GetCursorInGUI(bool cursoringui);

    std::vector<Entity> selectedunitlist;

    glm::vec3 calculateMouseRay();

private:
    glm::vec2 getNormalizedDeviceCoords(double mousex, double mousey);
    glm::vec3 toWorldCoords(glm::vec4 clipCoords);

    std::set<Entity> TerrainEntities;

    std::set<Entity> *colliderentitylist;

    glm::vec3 firstposclick;
    glm::vec3 secondposclick;

  

    bool CursorInGUI;

    float maxX, minX;
    float maxZ, minZ;
};