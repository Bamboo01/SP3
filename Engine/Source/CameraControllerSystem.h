#include "Camera.h"
#include "CameraController.h"
#include "Coordinator.h"
#include "Application.h"

extern Coordinator coordinator;

class CameraControllerSystem : public System
{
private:
	glm::vec3 distanceTraveled;
	glm::vec3 StartPos;
	bool scrollUsed;
	Vector3 RotationChange;
	float fZoom = 0;

public:
	virtual void Update(float dt);
	virtual void Setup();

};