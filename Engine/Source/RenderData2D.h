#include "Mesh.h"
#pragma once

struct RenderData2D
{
	Mesh* mesh = nullptr;

	RenderData2D()
	{
		this->mesh = nullptr;
	}

	RenderData2D(Mesh* mesh)
	{
		this->mesh = mesh;
	}
};