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
		controller.normalunitcost = controller.normalunitlevel * 50;
		controller.rangeunitcost = controller.rangeunitlevel * 100;
		controller.tankunitcost = controller.tankunitlevel * 150;
		controller.normalunitcost2 = controller.normalunitlevel * 40;
		controller.rangeunitcost2 = controller.rangeunitlevel * 80;
		controller.tankunitcost2 = controller.tankunitlevel * 110;
		controller.levelupnormalcost = controller.normalunitlevel * 30;
		controller.leveluprangecost = controller.rangeunitlevel * 130;
		controller.leveluptankcost = controller.tankunitlevel * 200;
		controller.levelupnormalcost2 = controller.normalunitlevel * 70;
		controller.leveluprangecost2 = controller.rangeunitlevel * 160;
		controller.leveluptankcost2 = controller.tankunitlevel * 230;
	}
}
