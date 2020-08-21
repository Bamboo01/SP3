#pragma once
#include "Mtx44.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "Camera.h"
#include <vector>

struct RayCasting
{
	glm::vec3 Ray;
	Camera camera;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	glm::vec3 RayStartPos;
	glm::vec3 RayEndPos;
	//std::vector<unsigned char> m_heightMap;

	RayCasting() {}

	RayCasting(Camera cam /*std::vector<unsigned char>& heightMap*/)
	{
		this->camera = cam;
		this->projectionMatrix = cam.getProjectionMatrix();
		this->viewMatrix = cam.getViewMatrix();
		RayStartPos = glm::vec3(cam.position.x, cam.position.y, cam.position.z);
		RayEndPos = glm::vec3(cam.position.x, cam.position.y, cam.position.z);
		//	this->m_heightMap = heightMap;
	}


	void Init(Camera cam /*std::vector<unsigned char>& heightMap*/)
	{
		this->projectionMatrix = cam.getProjectionMatrix();
		this->viewMatrix = cam.getViewMatrix();
		RayStartPos = glm::vec3(cam.position.x, cam.position.y, cam.position.z);
		RayEndPos = glm::vec3(cam.position.x, cam.position.y, cam.position.z);
		//	this->m_heightMap = heightMap;
	}

};