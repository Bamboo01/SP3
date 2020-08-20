#include "Shader.h"
#pragma once

class TextShader : public Shader
{
private:
	enum TEXTSHADER_UNIFORMS
	{
		U_TEXT_COLOR,
		U_TEXT_FONT,
		U_TEXT_MODELMATRIX,
		U_TOTAL
	};
	unsigned TextShader_Uniforms[U_TOTAL];
public:
	TextShader() : Shader("Shader//text.vs", "Shader//text.fs")
	{

	}

	virtual void InitShader()
	{
		UseShader();
		TextShader_Uniforms[U_TEXT_COLOR] = getUniformLocation("TextColor");
		TextShader_Uniforms[U_TEXT_FONT] = getUniformLocation("Font");
		TextShader_Uniforms[U_TEXT_MODELMATRIX] = getUniformLocation("ModelMatrix");
	}

	virtual void UpdateShader(Material* material)
	{

	}

	void UpdateShader(glm::mat4 modelmatrix)
	{
		setMat4(TextShader_Uniforms[U_TEXT_MODELMATRIX], modelmatrix);
	}

	void UpdateShaderTexture(unsigned textureID)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
		setInt(TextShader_Uniforms[U_TEXT_FONT], 0);
	}

	void UpdateShaderColor(glm::vec3 color)
	{
		setVec3(TextShader_Uniforms[U_TEXT_COLOR], color);
	}
};