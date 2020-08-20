#include "Shader.h"
#pragma once

class UIShader : public Shader
{
private:
	enum UISHADER_UNIFORMS
	{
		U_MODELMATRIX,
		U_TOTAL
	};
	unsigned UIShader_Uniforms[U_TOTAL];
public:
	virtual void InitShader()
	{
		UIShader_Uniforms[U_MODELMATRIX] = getUniformLocation("ModelMatrix");
	}

	virtual void UpdateShader(Material* material)
	{

	}
};