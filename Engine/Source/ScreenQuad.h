#include "Mesh.h"
#include "MeshBuilder.h"
#include "Shader.h"
#include "ScreenQuadShader.h"
#pragma once
class ScreenQuad : public Mesh
{
public:
	ScreenQuadShader* defaultScreenShader;
	unsigned screenTexture;
	virtual void Init();
	ScreenQuad();
	~ScreenQuad();
};

