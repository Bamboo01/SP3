#include "ControllerSystem.h"

void ControllerSystem::Setup()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<Controller>());
	signature.set(coordinator.GetComponentType<EntityState>());
	coordinator.SetSystemSignature<ControllerSystem>(signature);
}

void ControllerSystem::Init(std::set<Entity>* colliderentitylist)
{
	this->colliderentitylist = colliderentitylist;
}

void ControllerSystem::Update(double dt)
{
	for (auto const& control : m_Entities)
	{
		auto& controller = coordinator.GetComponent<Controller>(control);
		// Update unit cost
		controller.normalunitcost = controller.normalunitlevel * 40;
		controller.rangeunitcost = controller.rangeunitlevel * 60;
		controller.tankunitcost = controller.tankunitlevel * 90;
		controller.normalunitcost2 = controller.normalunitlevel * 30;
		controller.rangeunitcost2 = controller.rangeunitlevel * 50;
		controller.tankunitcost2 = controller.tankunitlevel * 80;
		controller.levelupnormalcost = controller.normalunitlevel * 30;
		controller.leveluprangecost = controller.rangeunitlevel * 70;
		controller.leveluptankcost = controller.tankunitlevel * 100;
		controller.levelupnormalcost2 = controller.normalunitlevel * 40;
		controller.leveluprangecost2 = controller.rangeunitlevel * 100;
		controller.leveluptankcost2 = controller.tankunitlevel * 150;
	}
}
