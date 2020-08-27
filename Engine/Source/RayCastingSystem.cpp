#include "RayCastingSystem.h"
#include <iostream>
#include "Application.h"
#include "GridControllerSystem.h"
#include "PlacingShader.h"

void RayCastingSystem::Setup()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<Camera>());
	signature.set(coordinator.GetComponentType<RayCasting>());
	signature.set(coordinator.GetComponentType<EntityState>());
	coordinator.SetSystemSignature<RayCastingSystem>(signature);
}

void RayCastingSystem::Init(std::set<Entity>* colliderentitylist, std::set<Entity>* controllerentitylist, Entity camera)
{

    unitlimit = 10;
    buildingclickdelay = 0;
    timer = 0;
    createonce = false;
	this->colliderentitylist = colliderentitylist;
    this->controllerentitylist = controllerentitylist;
    cSoundController = CSoundController::GetInstance();
    this->camera = camera;

	for (auto const& entity : m_Entities)
	{
		auto& camera = coordinator.GetComponent<Camera>(entity);
		auto& ray = coordinator.GetComponent<RayCasting>(entity);
		ray.Init(camera);
	}
}

void RayCastingSystem::Update(double dt)
{
    timer += dt;

	for (auto const& entity : m_Entities)
	{
		auto& camera = coordinator.GetComponent<Camera>(entity);
		auto& ray = coordinator.GetComponent<RayCasting>(entity);
		if (camera.type == CAMERA_TYPE::CAMERA_MAIN)
		{
			ray.viewMatrix = camera.getViewMatrix();
			ray.RayEndPos = glm::vec3(camera.position.x, camera.position.y, camera.position.z);
			ray.Ray = calculateMouseRay();
		}

        callRayCollision();
	}
}

void RayCastingSystem::Render()
{
}

bool RayCastingSystem::raycollisioncheck(Entity ray, Entity obj)
{
	auto& RayTransform = coordinator.GetComponent<Transform>(ray);
	auto& Ray = coordinator.GetComponent<RayCasting>(ray);
	auto& ObjectTransform = coordinator.GetComponent<Transform>(obj);
	auto& ObjectCollider = coordinator.GetComponent<Collider>(obj);

    glm::vec3 rayendpos = Ray.RayEndPos;
    rayendpos.y = ObjectTransform.position.y;
    glm::vec3 relativePos = ObjectTransform.position - rayendpos;

	bool collided = !(rayplanecheck(relativePos, ObjectTransform.AxisX, ObjectTransform, ObjectCollider) ||
		rayplanecheck(relativePos, ObjectTransform.AxisY, ObjectTransform, ObjectCollider) ||
		rayplanecheck(relativePos, ObjectTransform.AxisZ, ObjectTransform, ObjectCollider));


	if (!collided)
		return collided;

	return collided;
	return false;
}

bool RayCastingSystem::rayplanecheck(glm::vec3 rPos, glm::vec3 axis, Transform object, Collider collider)
{
	return (fabs(glm::dot(rPos, axis))) >
		(fabs(glm::dot(object.AxisX * glm::vec3(0.5, 0.5, 0.5) * collider.scale.x, axis)) +
			fabs(glm::dot(object.AxisY * glm::vec3(0.5, 0.5, 0.5) * collider.scale.y, axis)) +
			fabs(glm::dot(object.AxisZ * glm::vec3(0.5, 0.5, 0.5) * collider.scale.z, axis)));
}

void RayCastingSystem::callRayCollision()
{
    // Ray collision 

    std::set<Entity> entityset1 = m_Entities;
    std::set<Entity> entityset2 = *colliderentitylist;

    for (auto const& entity : entityset1)
    {
        auto& ray = coordinator.GetComponent<RayCasting>(entity);
        auto& camera = coordinator.GetComponent<Camera>(entity);

        std::vector<Entity> entitiesInQuadVector;

        for (int i = 0; i < 500; ++i)
        {
            // If ray overlapped with terrain y
            for (auto const& terrainmap : TerrainEntities)
            {
                auto& terrain = coordinator.GetComponent<TerrainData>(terrainmap);

                // Check if ray is within the terrain
                if (ray.RayEndPos.x > quadTreeSystem->root->topBoundary.x && ray.RayEndPos.x < quadTreeSystem->root->bottomBoundary.x && ray.RayEndPos.z < quadTreeSystem->root->topBoundary.y && ray.RayEndPos.z > quadTreeSystem->root->bottomBoundary.y)
                {
                    if (fabs(ray.RayEndPos.y - terrain.ReadHeightMap(ray.RayEndPos.x, ray.RayEndPos.z)) < 2.f)
                    {
                        cursorOnHeightMapPosition = glm::vec2(ray.RayEndPos.x, ray.RayEndPos.z);

                        if (CursorInGUI == false)
                        {
                            if (Application::IsMousePressed(1))
                            {
                                ray.rightClick = ray.RayEndPos;
                            }
                            static bool bLButtonState = false;
                            if (Application::IsMousePressed(0) && !bLButtonState)
                            {
                                unitlimit = 10;
                                minX = 0;
                                maxX = 0;
                                minZ = 0;
                                maxZ = 0;
                                selectedunitlist.clear();
                                ray.selectedunits.clear();
                                bLButtonState = true;
                                firstposclick = ray.RayEndPos;
                            }
                            else if (bLButtonState && !Application::IsMousePressed(0))
                            {
                                bLButtonState = false;
                                secondposclick = ray.RayEndPos;

                                // Calculating BottomLeft and TopRight
                                std::vector <std::vector<int>> Gridcost;
                                Gridcost.resize(20);
                                for (auto& vec : Gridcost)
                                {
                                    vec.resize(20);
                                }

                                Gridcost[0][0];

                                if (firstposclick.x < secondposclick.x)
                                {
                                    minX = firstposclick.x;
                                    maxX = secondposclick.x;
                                }
                                else if (firstposclick.x > secondposclick.x)
                                {
                                    minX = secondposclick.x;
                                    maxX = firstposclick.x;
                                }
                                if (firstposclick.z < secondposclick.z)
                                {
                                    minZ = firstposclick.z;
                                    maxZ = secondposclick.z;
                                }
                                else if (firstposclick.z > secondposclick.z)
                                {
                                    minZ = secondposclick.z;
                                    maxZ = firstposclick.z;
                                }
                                unitSelection();
                                ray.selectedunits = selectedunitlist;
                            }
                            PlaceBuilding(terrain, ray.RayEndPos);

                            i = 10000;
                            break;
                        }
                    }
                }
            }

            ray.RayEndPos += ray.Ray * 3.f;
        }

        //if (
        //    fabs(ray.RayEndPos.x) > quadTreeSystem->rootHalfWidth ||
        //    fabs(ray.RayEndPos.z) > quadTreeSystem->rootHalfHeight
        //    )
        //{
        //    return;
        //}

        //if (quadTreeSystem->GetNearbyEntityQuad(ray.RayEndPos)->quadType == QUAD_TYPE::ROOT)
        //{
        //    entitiesInQuadVector = quadTreeSystem->GetEntityInQuad(quadTreeSystem->GetNearbyEntityQuad(ray.RayEndPos));
        //}
        //else
        //{
        //    entitiesInQuadVector = quadTreeSystem->GetEntityInQuad(quadTreeSystem->GetNearbyEntityQuad(ray.RayEndPos)->parent);
        //}

        //if (entitiesInQuadVector.size() <= 1)
        //    continue;

        //for (int j = 0; j < entitiesInQuadVector.size(); j++)
        //{
        //    Entity tmp = entitiesInQuadVector[j];

        //    if (tmp == entity)
        //        continue;

        //    auto& ObjectTransform = coordinator.GetComponent<Transform>(tmp);
        //    auto& ObjectEntityState = coordinator.GetComponent<EntityState>(tmp);
        //    if (raycollisioncheck(entity, tmp) && ObjectEntityState.active)
        //    {
        //        //std::cout << "Ray collided with object!" << std::endl;
        //        break;
        //    }

        //}
    }
}

void RayCastingSystem::unitSelection()
{
    // Unit Selection Check
    if (minX != 0 && maxX != 0 && minZ != 0 && maxZ != 0)
    {
        std::set<Entity> entityset2 = *colliderentitylist;

        for (auto const& entity2 : entityset2)
        {
            auto& transform = coordinator.GetComponent<Transform>(entity2);
            auto& entitystate = coordinator.GetComponent<EntityState>(entity2);
            auto& unit = coordinator.GetComponent<Unit>(entity2);

            if (unitlimit == 0)
            {
                unitlimit = 10;
                break;
            }
            if (unit.unitType != Unit::PROJECTILE && unit.unitType != Unit::MELEE_PROJECTILE)
            {
                if (transform.position.x > minX && transform.position.x < maxX && transform.position.z > minZ && transform.position.z < maxZ && entitystate.active && unit.unitFaction == Unit::PLAYER)
                {
                    unitlimit--;
                    selectedunitlist.push_back(entity2);
                }
            }
        }
    }
}

void RayCastingSystem::PlaceBuilding(TerrainData terrain, glm::vec3 rayendpos)
{
    auto& cameratransform = coordinator.GetComponent<Camera>(camera);
    for (auto const& control : *controllerentitylist)
    {
        auto& controller = coordinator.GetComponent<Controller>(control);
        if (controller.controllertype == Controller::PLAYER)
        {
            float distance = glm::length(rayendpos - controller.nexusposition);
            if (distance < controller.buildrange)
            {
                //std::cout << "In Range!" << std::endl;
                if (selectedbuilding == 1)
                {
                    if (createonce == true)
                    {
                        newUnit = unitsystem->CreateUnit(Unit::TOWER, Unit::PLAYER, 1, Transform(glm::vec3(rayendpos.x, 20 + terrain.ReadHeightMap(rayendpos.x, rayendpos.z), rayendpos.z), glm::vec3(2, 2, 2), glm::vec3(0, 0, 0), TRANSFORM_TYPE::DYNAMIC_TRANSFORM));
                        createonce = false;
                    }
                    auto& renderdata = coordinator.GetComponent<RenderData>(newUnit);
                    auto& transform = coordinator.GetComponent<Transform>(newUnit);
                    auto& collider = coordinator.GetComponent<Collider>(newUnit);

                    collider.mass = 1;
                    renderdata.mesh = renderer.getMesh(GEO_INRANGE_TOWER_PLAYER);
                    static_cast<PlacingShader*>(renderer.getShader(renderer.getMaterial(GEO_INRANGE_TOWER_PLAYER)))->UpdateBool(true);
                    glm::vec3 rollBackPos = transform.position;
                    transform.position = glm::vec3(rayendpos.x, 20 + terrain.ReadHeightMap(rayendpos.x, rayendpos.z), rayendpos.z);

                    if (Application::IsMousePressed(0) && buildingclickdelay < timer)
                    {
                        cSoundController->SetSoundSourcePosition(25, rayendpos.x, rayendpos.y, rayendpos.z);
                        cSoundController->PlaySoundByID(25);

                        std::cout << "Tower Placed!" << std::endl;
                        renderdata.mesh = renderer.getMesh(GEO_UNIT_TOWER_PLAYER);
                        selectedbuilding = 0;
                        collider.mass = -1;
                        transform.position = rollBackPos;
                    }
                }
                else if (selectedbuilding == 2)
                {
                    if (createonce == true)
                    {
                        newUnit = unitsystem->CreateUnit(Unit::WALL, Unit::PLAYER, 1, Transform(glm::vec3(rayendpos.x, 20 + terrain.ReadHeightMap(rayendpos.x, rayendpos.z), rayendpos.z), glm::vec3(2, 2, 2), glm::vec3(0, 0, 0), TRANSFORM_TYPE::DYNAMIC_TRANSFORM));
                        createonce = false;
                    }
                    auto& renderdata = coordinator.GetComponent<RenderData>(newUnit);
                    auto& transform = coordinator.GetComponent<Transform>(newUnit);
                    auto& collider = coordinator.GetComponent<Collider>(newUnit);

                    collider.mass = 1;
                    renderdata.mesh = renderer.getMesh(GEO_INRANGE_WALL_PLAYER);
                    static_cast<PlacingShader*>(renderer.getShader(renderer.getMaterial(GEO_INRANGE_WALL_PLAYER)))->UpdateBool(true);
                    glm::vec3 rollBackPos = transform.position;
                    transform.position = glm::vec3(rayendpos.x, 20 + terrain.ReadHeightMap(rayendpos.x, rayendpos.z), rayendpos.z);

                    if (Application::IsMousePressed(0) && buildingclickdelay < timer)
                    {
                        cSoundController->SetSoundSourcePosition(25, rayendpos.x, rayendpos.y, rayendpos.z);
                        cSoundController->PlaySoundByID(25);

                        std::cout << "Wall Placed!" << std::endl;
                        collider.mass = -1;
                        renderdata.mesh = renderer.getMesh(GEO_UNIT_WALL_PLAYER);
                        selectedbuilding = 0;
                        transform.position = rollBackPos;
                    }
                }
                else if (selectedbuilding == 3)
                {
                    if (createonce == true)
                    {
                        newUnit = unitsystem->CreateUnit(Unit::GENERATOR1, Unit::PLAYER, 1, Transform(glm::vec3(rayendpos.x, 20 + terrain.ReadHeightMap(rayendpos.x, rayendpos.z), rayendpos.z), glm::vec3(2, 2, 2), glm::vec3(0, 0, 0), TRANSFORM_TYPE::DYNAMIC_TRANSFORM));
                        createonce = false;
                    }
                    auto& renderdata = coordinator.GetComponent<RenderData>(newUnit);
                    auto& transform = coordinator.GetComponent<Transform>(newUnit);
                    auto& collider = coordinator.GetComponent<Collider>(newUnit);

                    collider.mass = 1;
                    renderdata.mesh = renderer.getMesh(GEO_INRANGE_GENERATOR1_PLAYER);
                    static_cast<PlacingShader*>(renderer.getShader(renderer.getMaterial(GEO_INRANGE_GENERATOR1_PLAYER)))->UpdateBool(true);
                    glm::vec3 rollBackPos = transform.position;
                    transform.position = glm::vec3(rayendpos.x, 20 + terrain.ReadHeightMap(rayendpos.x, rayendpos.z), rayendpos.z);
                    if (Application::IsMousePressed(0) && buildingclickdelay < timer)
                    {
                        cSoundController->SetSoundSourcePosition(25, rayendpos.x, rayendpos.y + 80, rayendpos.z);
                        cSoundController->PlaySoundByID(25);
                        std::cout << "Gen1 Placed!" << std::endl;
                        renderdata.mesh = renderer.getMesh(GEO_UNIT_GENERATOR1_PLAYER);
                        selectedbuilding = 0;
                        collidersystem->isBuildingPlaced = true;
                        collider.mass = -1;
                        transform.position = rollBackPos;
                    }
                }
                else if (selectedbuilding == 4)
                {
                    if (createonce == true)
                    {
                        newUnit = unitsystem->CreateUnit(Unit::GENERATOR2, Unit::PLAYER, 1, Transform(glm::vec3(rayendpos.x, 20 + terrain.ReadHeightMap(rayendpos.x, rayendpos.z), rayendpos.z), glm::vec3(2, 2, 2), glm::vec3(0, 0, 0), TRANSFORM_TYPE::DYNAMIC_TRANSFORM));
                        createonce = false;
                    }
                    auto& renderdata = coordinator.GetComponent<RenderData>(newUnit);
                    auto& transform = coordinator.GetComponent<Transform>(newUnit);
                    auto& collider = coordinator.GetComponent<Collider>(newUnit);

                    collider.mass = 1;
                    renderdata.mesh = renderer.getMesh(GEO_INRANGE_GENERATOR2_PLAYER);
                    static_cast<PlacingShader*>(renderer.getShader(renderer.getMaterial(GEO_INRANGE_GENERATOR2_PLAYER)))->UpdateBool(true);
                    glm::vec3 rollBackPos = transform.position;
                    transform.position = glm::vec3(rayendpos.x, 20 + terrain.ReadHeightMap(rayendpos.x, rayendpos.z), rayendpos.z);

                    if (Application::IsMousePressed(0) && buildingclickdelay < timer)
                    {
                        cSoundController->SetSoundSourcePosition(25, rayendpos.x, rayendpos.y + 80, rayendpos.z);
                        cSoundController->PlaySoundByID(25);
                        std::cout << "Gen2 Placed!" << std::endl;
                        renderdata.mesh = renderer.getMesh(GEO_UNIT_GENERATOR2_PLAYER);
                        collider.mass = -1;
                        collidersystem->isBuildingPlaced = true;
                        selectedbuilding = 0;
                        transform.position = rollBackPos;
                    }
                }
            }
            else
            {
                //std::cout << "Out of Range! " << std::endl;
                if (selectedbuilding == 1)
                {
                    auto& renderdata = coordinator.GetComponent<RenderData>(newUnit);
                    auto& transform = coordinator.GetComponent<Transform>(newUnit);

                    renderdata.mesh = renderer.getMesh(GEO_INRANGE_TOWER_PLAYER);
                    static_cast<PlacingShader*>(renderer.getShader(renderer.getMaterial(GEO_INRANGE_TOWER_PLAYER)))->UpdateBool(false);
                    transform.position = glm::vec3(rayendpos.x, 20 + terrain.ReadHeightMap(rayendpos.x, rayendpos.z), rayendpos.z);
                }
                else if (selectedbuilding == 2)
                {
                    auto& renderdata = coordinator.GetComponent<RenderData>(newUnit);
                    auto& transform = coordinator.GetComponent<Transform>(newUnit);

                    renderdata.mesh = renderer.getMesh(GEO_INRANGE_WALL_PLAYER);
                    static_cast<PlacingShader*>(renderer.getShader(renderer.getMaterial(GEO_INRANGE_WALL_PLAYER)))->UpdateBool(false);
                    transform.position = glm::vec3(rayendpos.x, 20 + terrain.ReadHeightMap(rayendpos.x, rayendpos.z), rayendpos.z);
                }
                else if (selectedbuilding == 3)
                {
                    auto& renderdata = coordinator.GetComponent<RenderData>(newUnit);
                    auto& transform = coordinator.GetComponent<Transform>(newUnit);

                    renderdata.mesh = renderer.getMesh(GEO_INRANGE_GENERATOR1_PLAYER);
                    static_cast<PlacingShader*>(renderer.getShader(renderer.getMaterial(GEO_INRANGE_GENERATOR1_PLAYER)))->UpdateBool(false);
                    transform.position = glm::vec3(rayendpos.x, 20 + terrain.ReadHeightMap(rayendpos.x, rayendpos.z), rayendpos.z);
                }
                else if (selectedbuilding == 4)
                {
                    auto& renderdata = coordinator.GetComponent<RenderData>(newUnit);
                    auto& transform = coordinator.GetComponent<Transform>(newUnit);

                    renderdata.mesh = renderer.getMesh(GEO_INRANGE_GENERATOR1_PLAYER);
                    static_cast<PlacingShader*>(renderer.getShader(renderer.getMaterial(GEO_INRANGE_GENERATOR2_PLAYER)))->UpdateBool(false);
                    transform.position = glm::vec3(rayendpos.x, 20 + terrain.ReadHeightMap(rayendpos.x, rayendpos.z), rayendpos.z);
                }
            }
        }
    }
}

void RayCastingSystem::SetTerrainEntities(std::set<Entity> terrain)
{
    TerrainEntities = terrain;
}

void RayCastingSystem::GetCursorInGUI(bool cursoringui)
{
    CursorInGUI = cursoringui;
}

glm::vec3 RayCastingSystem::calculateMouseRay()
{
	double mousex, mousey;
	Application::GetCursorPos(&mousex, &mousey);
	glm::vec2 normalizedCoords = getNormalizedDeviceCoords(mousex, mousey);
	glm::vec4 clipCoords = glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.f, 1.f);
	glm::vec3 worldCoords = toWorldCoords(clipCoords);

	glm::vec3 dir = glm::normalize(worldCoords);
	return dir;
}

void RayCastingSystem::SetUnitSystem(std::shared_ptr<UnitSystem> system)
{
    unitsystem = system;
}

void RayCastingSystem::SetQuadTreeSystem(std::shared_ptr<QuadTreeSystem> system)
{
    quadTreeSystem = system;
}

void RayCastingSystem::SetColliderSystem(std::shared_ptr<ColliderSystem> system)
{
    collidersystem = system;
}

glm::vec2 RayCastingSystem::getNormalizedDeviceCoords(double mousex, double mousey)
{
    float offsetx = Application::GetWindowWidth() - Application::GetWindowHeight();
    float offsety = Application::GetWindowHeight() - Application::GetWindowWidth();

    if (Application::GetWindowWidth() > Application::GetWindowHeight())
        offsety = 0;
    else if (Application::GetWindowWidth() < Application::GetWindowHeight())
        offsetx = 0;

    double x = (2 * (mousex - (offsetx / 2))) / (Application::GetWindowWidth() - offsetx) - 1;
    double y = (2 * (mousey - (offsety / 2))) / (Application::GetWindowHeight() - offsety) - 1;
	return glm::vec2(x, -y);
}

glm::vec3 RayCastingSystem::toWorldCoords(glm::vec4 clipCoords)
{
	for (auto const& entity : m_Entities)
	{
		auto& ray = coordinator.GetComponent<RayCasting>(entity);
		glm::vec4 eyeCoord(glm::inverse(ray.projectionMatrix) * clipCoords);
		eyeCoord = glm::vec4(eyeCoord.x, eyeCoord.y, -1.f, 0);

		return glm::vec3(glm::inverse(ray.viewMatrix) * eyeCoord);
	}
}
