#pragma once
#include "Mtx44.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "Camera.h"

struct RayCasting
{
	glm::vec3 Ray;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	glm::vec3 RayEndPos;
	glm::vec3 rightClick;

	RayCasting() {}

	void Init(Camera& cam)
	{
		this->projectionMatrix = cam.getProjectionMatrix();
		this->viewMatrix = cam.getViewMatrix();
		RayEndPos = glm::vec3(cam.position.x, cam.position.y, cam.position.z);
	}

};