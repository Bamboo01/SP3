#include "Light.h"
#include <glm.hpp>
#include "GL\glew.h"
#include <queue>
#include <map>
#include <iostream>
#include "Shader.h"
#include "Camera.h"

#define MAX_LIGHTS 32

#pragma once
class LightingManager
{
protected:
	std::map <unsigned, Light> lights;
	std::queue<unsigned> availableLightIDs;
	int numLights;
	unsigned LightUBO;
public:
	LightingManager();
	~LightingManager();
	unsigned getNewLightID();
	void returnLightByID(unsigned ID);
	Light& getLightByID(unsigned ID);
	void InitLights(std::vector<Shader*> shaders);
	void BufferLights(Camera camera);
};