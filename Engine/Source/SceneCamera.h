#include "Scene.h"
#include "TransformSystem.h"
#include "CameraSystem.h"
#include "RenderSystem.h"
#include "EntityStateSystem.h"

// Includes for ImGui
#include "../Dependencies/ImGui/imgui.h"
#include "../Dependencies/ImGui/imgui_impl_glfw.h"
#include "../Dependencies/ImGui/imgui_impl_opengl3.h"

#pragma once

#pragma once
class SceneCamera: public Scene
{
	virtual void Init();
	virtual void EarlyUpdate(double dt);
	virtual void Update(double dt);
	virtual void LateUpdate(double dt);

	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();


	virtual void Exit();
	virtual Scene* Clone() { return new SceneCamera(*this); }

	Entity testHandler; // An entity handler to control entities
	std::vector<Entity> activeEntityList; // A vector containing a list of active entities

	/*Systems of the scene*/
	std::shared_ptr<TransformSystem> transformsystem;
	std::shared_ptr<CameraSystem> camerasystem;
	std::shared_ptr<RenderSystem> rendersystem;
	std::shared_ptr<EntityStateSystem> entitystatesystem;
};

