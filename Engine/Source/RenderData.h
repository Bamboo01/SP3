#include "Mesh.h"
#include "Material.h"
#include "Renderer.h"

extern Renderer renderer;
#pragma once

struct RenderData
{
	Mesh* mesh = nullptr;
	Material* material = nullptr;
	bool enableLight;

	RenderData()
	{
		this->mesh = nullptr;
		enableLight = false;
	}

	RenderData(Mesh* mesh, bool light)
	{
		this->mesh = mesh;
		enableLight = light;
	}
};