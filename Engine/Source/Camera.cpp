#include "Camera.h"
#include <gtc/matrix_transform.hpp>

Camera::Camera(
	const glm::vec3& pos,
	const glm::vec3& rotation,
	unsigned width, unsigned height,
	float FOV,
	CAMERA_TYPE type,
	CAMERA_MODE mode,
	std::string vspath, std::string fspath
)
{
	this->position = pos;
	this->rotation = rotation;
	this->FOV = FOV;
	this->viewWidth = width;
	this->viewHeight = height;
	this->mode = mode;
	this->type = type;

	glm::mat4 rot(1.f);
	glm::vec3 rotvec = glm::radians(rotation);
	rot = glm::rotate(rot, rotvec.x, glm::vec3(1, 0, 0));
	rot = glm::rotate(rot, rotvec.y, glm::vec3(0, 1, 0));
	rot = glm::rotate(rot, rotvec.z, glm::vec3(0, 0, 1));

	this->target = this->position + glm::vec3((rot * glm::vec4(0, 0, 1, 0)));
	this->up = rot * glm::vec4(0, 1, 0, 0);
	this->right = glm::cross((this->target - this->position), this->up);
	this->ViewMatrix = glm::lookAt(this->position, this->target, this->up);

	if (this->mode == CAMERA_MODE::MODE_ORTHOGRAPHIC)
	{
		ProjectionMatrix = glm::ortho(0, viewWidth, 0, viewHeight);
	}
	else
	{
		ProjectionMatrix = glm::perspective(FOV, ((float)viewWidth / (float)viewHeight), 0.1f, 1000.f);
	}

	vertex_file_path = vspath;
	fragment_file_path = fspath;

	FBO = nullptr;
	PostProcessingShader = nullptr;
}

Camera::Camera()
{

}

Camera::~Camera()
{

}

void Camera::UpdateAssignedTextures()
{
	for (auto a : targetTexture)
	{
		if (a)
		{
			*a = FBO->GetFrame();
		}
	}
}

void Camera::assignTargetTexture(unsigned* target)
{
	targetTexture.push_back(target);
}

glm::mat4 Camera::getProjectionMatrix()
{
	return ProjectionMatrix;
}

glm::mat4 Camera::getViewMatrix()
{
	return ViewMatrix;
}
