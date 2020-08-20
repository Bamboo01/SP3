#include "Shader.h"
#include "glm.hpp"

#pragma once

class ScreenQuadShader : public Shader
{
private:
	enum SCREENQUADSHADER_UNIFORMS
	{
		U_TRANSFORM_MATRIX,
		U_TEXTURE,
		U_TOTAL
	};
public:
	unsigned ScreenQuadShaderUniforms[U_TOTAL];

	ScreenQuadShader(const char* vertex_file_path, const char* fragment_file_path) : Shader(vertex_file_path, fragment_file_path)
	{

	}

	virtual void InitShader()
	{
		UseShader();
		ScreenQuadShaderUniforms[U_TRANSFORM_MATRIX] = getUniformLocation("model");
		ScreenQuadShaderUniforms[U_TEXTURE] = getUniformLocation("screenTexture");
		//I am sad
	}

	virtual void UpdateShader(Material* material = nullptr)
	{
		
	}

	void UpdateShader(glm::mat4 modelmatrix)
	{
		setMat4(ScreenQuadShaderUniforms[U_TRANSFORM_MATRIX], modelmatrix);
	}

	void UpdateShaderTexture(unsigned textureID)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
		setInt(ScreenQuadShaderUniforms[U_TEXTURE], 0);
	}
};
