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

#pragma once
class SceneTest : public Scene
{
public:
	virtual void Init();
	virtual void EarlyUpdate(double dt);
	virtual void Update(double dt);
	virtual void LateUpdate(double dt);

	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();

	virtual void Exit();
	virtual Scene* Clone() { return new SceneTest(*this); }

	/*Systems of the scene*/
	std::shared_ptr<TransformSystem> transformsystem;
	std::shared_ptr<CameraSystem> camerasystem;
	std::shared_ptr<RenderSystem> rendersystem;
	std::shared_ptr<CanvasImageSystem> canvasimagesystem;
	std::shared_ptr<CanvasTextSystem> canvastextsystem;
	std::shared_ptr<CameraControllerSystem> cameracontrollersystem;
	std::shared_ptr<GridControllerSytem> gridcontrollersystem;
	std::shared_ptr<EntityStateSystem> entitystatesystem;
	std::shared_ptr<TerrainSystem> terrainsystem;
};

