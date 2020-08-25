#include "Camera.h"
#include "CameraController.h"
#include "EntityState.h"
#include "Coordinator.h"

#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H


extern Coordinator coordinator;

class CameraControllerSystem : public System
{
private:
	glm::vec3 distanceTraveled;
	glm::vec3 StartPos;
	bool scrollUsed;
	float fZoom = 0;

public:
	virtual void Update(float dt);
	virtual void Setup();

};

#endif