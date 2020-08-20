#include "ScreenQuad.h"
#include <GL/glew.h>

void ScreenQuad::Init()
{
	Mesh::Init();
	defaultScreenShader->UseShader();
	defaultScreenShader->InitShader();
}

ScreenQuad::ScreenQuad() : Mesh("ScreenQuad")
{
	/*
	This is Mr Toh level coding but I legit need a screen quad set up LOL
	*/
	float length = 2.f;
	Color color = Color(1, 1, 1);
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	v.pos.Set(-0.5f * length, -0.5f * length, 0);
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0);
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(1.0f, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, 0);
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(1.0f, 1.0f);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0);
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(0, 1.0f);
	vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(3);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(0);

	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	this->indexSize = index_buffer_data.size();
	this->mode = Mesh::DRAW_TRIANGLES;

	defaultScreenShader = new ScreenQuadShader("Shader//screenquad.vs", "Shader//screenquad.fs");
}

ScreenQuad::~ScreenQuad()
{
	delete defaultScreenShader;
}
