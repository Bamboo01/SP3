#include "Scene.h"
#include "TransformSystem.h"
#include "CameraSystem.h"
#include "RenderSystem.h"
#include "CanvasImageSystem.h"
#include "CanvasImageUpdateSystem.h"
#include "UnitSystem.h"
#include "RayCastingSystem.h"
#include "ColliderSystem.h"

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
	std::shared_ptr<CanvasImageUpdateSystem> canvasimageupdatesystem;
	std::shared_ptr<UnitSystem> unitsystem;
	std::shared_ptr<RayCastingSystem> raycastingsystem;
	std::shared_ptr<ColliderSystem> collidersystem;
};

