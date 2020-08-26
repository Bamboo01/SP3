#include "Coordinator.h"
#include "glm.hpp"
#include "Transform.h"
#include "CanvasText.h"
extern Coordinator coordinator;

class IntroTextSystem : public System
{
private:
	double timer;
	int count;
public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void ScrollUpdate();
	
};