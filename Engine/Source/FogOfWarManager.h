#include <glm.hpp>
#include "GL\glew.h"
#include <vector>
#include "Shader.h"

#define MAX_UNITS 1000
#pragma once

class FogOfWarManager
{
private:
	unsigned ManagerUBO;
	int numUnits;
public:
	std::vector<glm::vec4> positions;
	FogOfWarManager();
	~FogOfWarManager();
	void InitManager(std::vector<Shader*> shaders);
	void BufferManager();
};