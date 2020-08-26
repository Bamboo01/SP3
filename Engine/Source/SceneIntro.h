#include "Scene.h"
#include "TransformSystem.h"
#include "CameraSystem.h"
#include "RenderSystem.h"
#include "CanvasImageSystem.h"
#include "CanvasTextSystem.h"
#include "CameraControllerSystem.h"
#include "GridControllerSystem.h"
#include "EntityStateSystem.h"
#include "TerrainSystem.h"
#include "Tag.h"
#include "CanvasImageUpdateSystem.h"
#include "UnitSystem.h"
#include "RayCastingSystem.h"
#include "ColliderSystem.h"
#include "GUITextSystem.h"
#include "ParticleSystem.h"
#include "ObjectPoolSystem.h"
#include "ControllerSystem.h"
#include "QuadTreeSystem.h"
#include "IntroTextSystem.h"

// Includes for ImGui
#include "../Dependencies/ImGui/imgui.h"
#include "../Dependencies/ImGui/imgui_impl_glfw.h"
#include "../Dependencies/ImGui/imgui_impl_opengl3.h"

#pragma once

#pragma once
class SceneIntro : public Scene
{
	virtual void Init();
	virtual void EarlyUpdate(double dt);
	virtual void Update(double dt);
	virtual void LateUpdate(double dt);

	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();


	virtual void Exit();
	virtual Scene* Clone() { return new SceneIntro(*this); }

	Entity testHandler; // An entity handler to control entities
	std::vector<Entity> activeEntityList; // A vector containing a list of active entities

	/*Systems of the scene*/
	std::shared_ptr<TransformSystem> transformsystem;
	std::shared_ptr<CameraSystem> camerasystem;
	std::shared_ptr<RenderSystem> rendersystem;
	std::shared_ptr<CanvasImageSystem> canvasimagesystem;
	std::shared_ptr<CanvasTextSystem> canvastextsystem;
	std::shared_ptr<CameraControllerSystem> cameracontrollersystem;
	std::shared_ptr<EntityStateSystem> entitystatesystem;
	std::shared_ptr<TerrainSystem> terrainsystem;
	std::shared_ptr<CanvasImageUpdateSystem> canvasimageupdatesystem;
	std::shared_ptr<UnitSystem> unitsystem;
	std::shared_ptr<RayCastingSystem> raycastingsystem;
	std::shared_ptr<ColliderSystem> collidersystem;
	std::shared_ptr<GridControllerSystem> gridcontrollersystem;
	std::shared_ptr<GUITextSystem> guitextsystem;
	std::shared_ptr<ParticleSystem> particlesystem;
	std::shared_ptr<ObjectPoolSystem> objectpoolsystem;
	std::shared_ptr<ControllerSystem> controllersystem;
	std::shared_ptr<QuadTreeSystem> quadtreesystem;
	std::shared_ptr<IntroTextSystem> introtextsystem;
};

