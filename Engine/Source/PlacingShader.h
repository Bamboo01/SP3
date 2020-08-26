#include "Shader.h"
#include "glm.hpp"

#pragma once

class PlacingShader : public Shader
{
private:
	enum PLACINGSHADER_UNIFORMS
	{
		U_IF_IN_RANGE,
		U_TOTAL
	};

public:
	unsigned PlacingShaderUniforms[U_TOTAL];

	PlacingShader(const char* vertex_file_path, const char* fragment_file_path) : Shader(vertex_file_path, fragment_file_path)
	{

	}

	virtual void InitShader()
	{
		UseShader();
		Shader::InitShader();
		PlacingShaderUniforms[U_IF_IN_RANGE] = getUniformLocation("inrange");
	}

	virtual void UpdateShader(Material* material = nullptr)
	{
		Shader::UpdateShader(material);
	}

	void UpdateBool(bool a)
	{
		UseShader();
		setBool(PlacingShaderUniforms[U_IF_IN_RANGE], a);
	}

};