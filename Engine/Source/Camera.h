#ifndef CAMERA_H
#define CAMERA_H

#include "Shader.h"
#include "FBO.h"
#include "glm.hpp"

enum CAMERA_TYPE
{
	CAMERA_MAIN,
	CAMERA_NORMAL,
	CAMERA_MINIMAP,
	NUM_TYPES
};

enum CAMERA_MODE
{
	MODE_ORTHOGRAPHIC,
	MODE_PERSPECTIVE
};

class Camera
{
private:
	std::vector<unsigned*> targetTexture;
	
public:

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 target;
	glm::vec3 up;
	glm::vec3 right;
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	int viewWidth;
	int viewHeight;
	float FOV;

	std::string vertex_file_path;
	std::string fragment_file_path;

	CAMERA_TYPE type;
	CAMERA_MODE mode;

	//These have to be intialised inside the camera system!!!
	Shader* PostProcessingShader;
	FrameBufferObject* FBO;

	Camera(
		const glm::vec3& pos,
		const glm::vec3& rotation,
		unsigned width, unsigned height,
		float FOV,
		CAMERA_TYPE type,
		CAMERA_MODE mode,
		std::string vspath = "", std::string fspath = ""
	);
	Camera();
	~Camera();

	void UpdateAssignedTextures();
	void assignTargetTexture(unsigned* target);
	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewMatrix();
};

#endif