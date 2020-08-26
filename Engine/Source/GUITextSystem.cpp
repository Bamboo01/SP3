#include "GUITextSystem.h"

void GUITextSystem::Setup()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<Transform>());
	signature.set(coordinator.GetComponentType<GUIText>());
	signature.set(coordinator.GetComponentType<EntityState>());
	coordinator.SetSystemSignature<GUITextSystem>(signature);
}

void GUITextSystem::Init(std::set<Entity>* controllerentitylist)
{
	LabUIopen = false;
	UnitUIopen = false;
	BuildingUIopen = false;

	this->controllerentitylist = controllerentitylist;

	for (auto const& entity : m_Entities)
	{
		auto& transform = coordinator.GetComponent<Transform>(entity);
		auto& text = coordinator.GetComponent<CanvasText>(entity);
		auto& textstate = coordinator.GetComponent<GUIText>(entity);
		auto& entitystate = coordinator.GetComponent<EntityState>(entity);

		if (textstate.texttype != GUIText::RESOURCES1 && textstate.texttype != GUIText::RESOURCES2)
		{
			entitystate.active = false;
		}
		ReferenceEntity.push_back(entity);
	}
}

void GUITextSystem::Update(double dt)
{
	for (auto const& textentity : m_Entities)
	{
		auto& guitype = coordinator.GetComponent<GUIText>(textentity);
		auto& text = coordinator.GetComponent<CanvasText>(textentity);

		for (auto const& controller : *controllerentitylist)
		{
			auto& control = coordinator.GetComponent<Controller>(controller);
			if (control.controllertype == Controller::PLAYER)
			{
				if (guitype.texttype == GUIText::RESOURCES1)
					text.Text = "Resources1: " + std::to_string(control.resource1).substr(0, std::to_string(control.resource1).find('.'));
				else if (guitype.texttype == GUIText::RESOURCES2)
					text.Text = "Resources2: " + std::to_string(control.resource2).substr(0, std::to_string(control.resource2).find('.'));
			}
		}

	}

	if (selectedunitList.size() == 1)
	{
		for (auto const& selectunit : selectedunitList)
		{
			auto& unitentitystate = coordinator.GetComponent<EntityState>(selectunit);
			auto& unit = coordinator.GetComponent<Unit>(selectunit);
			
			for (auto const& guitext : ReferenceEntity)
			{
				auto& guientitystate = coordinator.GetComponent<EntityState>(guitext);
				auto& guitype = coordinator.GetComponent<GUIText>(guitext);
				auto& text = coordinator.GetComponent<CanvasText>(guitext);

				if (guitype.texttype == GUIText::NAME || guitype.texttype == GUIText::LEVEL || guitype.texttype == GUIText::HEALTH || guitype.texttype == GUIText::DAMAGE || guitype.texttype == GUIText::DEFENSE || guitype.texttype == GUIText::ATKSPD)
				{
					guientitystate.active = true;

					if (guitype.texttype == GUIText::NAME)
						text.Text = "Name: " + unit.name;
					else if (guitype.texttype == GUIText::LEVEL)
						text.Text = "Level: " + std::to_string(unit.level);
					else if (guitype.texttype == GUIText::HEALTH)
						text.Text = "HP: " + std::to_string(unit.health).substr(0, std::to_string(unit.health).find('.'));
					else if (guitype.texttype == GUIText::DAMAGE)
						text.Text = "ATK: " + std::to_string(unit.damage).substr(0, std::to_string(unit.damage).find('.'));
					else if (guitype.texttype == GUIText::DEFENSE)
						text.Text = "DEF: " + std::to_string(unit.defense).substr(0, std::to_string(unit.defense).find('.'));
					else if (guitype.texttype == GUIText::ATKSPD)
						text.Text = "ATKSPD: " + std::to_string(unit.attackSpeed).substr(0, std::to_string(unit.attackSpeed).find('.') + 2);
				}

				if (unit.unitType == Unit::GENERATOR1 || unit.unitType == Unit::GENERATOR2)
				{
					if (guitype.texttype == GUIText::GENERATORBUTTON)
						guientitystate.active = true;
					else if (guitype.texttype == GUIText::GENERATEDRESOURCES)
					{
						guientitystate.active = true;
						text.Text = std::to_string(unit.resourcesgenerated).substr(0, std::to_string(unit.resourcesgenerated).find('.'));
						if (unit.unitType == Unit::GENERATOR1)
							text.color = glm::vec3(0.5, 0, 1);
						else if (unit.unitType == Unit::GENERATOR2)
							text.color = glm::vec3(0, 1, 0);
					}
						
				}
				for (auto const& control : *controllerentitylist)
				{
					auto& controller = coordinator.GetComponent<Controller>(control);

					if (controller.controllertype == Controller::PLAYER)
					{
						if (unit.unitType == Unit::LAB)
						{
							if (guitype.texttype == GUIText::LABBUTTON)
								guientitystate.active = true;
							for (auto const& unitguitext : ReferenceEntity)
							{
								auto& unitguientitystate = coordinator.GetComponent<EntityState>(unitguitext);
								auto& unitguitype = coordinator.GetComponent<GUIText>(unitguitext);
								auto& unittext = coordinator.GetComponent<CanvasText>(unitguitext);
								if (guitype.texttype == GUIText::UNITBUTTON && LabUIopen)
								{
									guientitystate.active = true;
									if (unitguitype.texttype == GUIText::NORMALUNITCOST)
									{
										unitguientitystate = true;
										unittext.Text = std::to_string(controller.levelupnormalcost).substr(0, std::to_string(controller.levelupnormalcost).find('.'));
									}
									else if (unitguitype.texttype == GUIText::RANGEUNITCOST)
									{
										unitguientitystate = true;
										unittext.Text = std::to_string(controller.leveluprangecost).substr(0, std::to_string(controller.leveluprangecost).find('.'));
									}
									else if (unitguitype.texttype == GUIText::TANKUNITCOST)
									{
										unitguientitystate = true;
										unittext.Text = std::to_string(controller.leveluptankcost).substr(0, std::to_string(controller.leveluptankcost).find('.'));
									}
									else if (unitguitype.texttype == GUIText::NORMALUNITLEVEL)
									{
										unitguientitystate = true;
										unittext.Text = "Lvl " + std::to_string(controller.normalunitlevel);
									}
									else if (unitguitype.texttype == GUIText::RANGEUNITLEVEL)
									{
										unitguientitystate = true;
										unittext.Text = "Lvl " + std::to_string(controller.rangeunitlevel);
									}
									else if (unitguitype.texttype == GUIText::TANKUNITLEVEL)
									{
										unitguientitystate = true;
										unittext.Text = "Lvl " + std::to_string(controller.tankunitlevel);
									}
									if (controller.normalunitlevel > 3)
									{
										if (unitguitype.texttype == GUIText::NORMALUNITCOST2)
										{
											unitguientitystate = true;
											unittext.Text = std::to_string(controller.levelupnormalcost2).substr(0, std::to_string(controller.levelupnormalcost2).find('.'));
										}
									}
									if (controller.rangeunitlevel > 3)
									{
										if (unitguitype.texttype == GUIText::RANGEUNITCOST2)
										{
											unitguientitystate = true;
											unittext.Text = std::to_string(controller.leveluprangecost2).substr(0, std::to_string(controller.leveluprangecost2).find('.'));
										}
									}
									if (controller.tankunitlevel > 3)
									{
										if (unitguitype.texttype == GUIText::TANKUNITCOST2)
										{
											unitguientitystate = true;
											unittext.Text = std::to_string(controller.leveluptankcost2).substr(0, std::to_string(controller.leveluptankcost2).find('.'));
										}
									}
								}
								else if (guitype.texttype == GUIText::UNITBUTTON && !LabUIopen)
								{
									guientitystate.active = false;
									if (unitguitype.texttype == GUIText::NORMALUNITCOST)
										unitguientitystate = false;
									else if (unitguitype.texttype == GUIText::RANGEUNITCOST)
										unitguientitystate = false;
									else if (unitguitype.texttype == GUIText::TANKUNITCOST)
										unitguientitystate = false;
									else if (unitguitype.texttype == GUIText::NORMALUNITCOST2)
										unitguientitystate = false;
									else if (unitguitype.texttype == GUIText::RANGEUNITCOST2)
										unitguientitystate = false;
									else if (unitguitype.texttype == GUIText::TANKUNITCOST2)
										unitguientitystate = false;
									else if (unitguitype.texttype == GUIText::NORMALUNITLEVEL)
										unitguientitystate = false;
									else if (unitguitype.texttype == GUIText::RANGEUNITLEVEL)
										unitguientitystate = false;
									else if (unitguitype.texttype == GUIText::TANKUNITLEVEL)
										unitguientitystate = false;
								}
							}
						}
						else if (unit.unitType == Unit::NEXUS)
						{
							if (guitype.texttype == GUIText::NEXUSBUTTON)
								guientitystate.active = true;
							for (auto const& unitguitext : ReferenceEntity)
							{
								auto& unitguientitystate = coordinator.GetComponent<EntityState>(unitguitext);
								auto& unitguitype = coordinator.GetComponent<GUIText>(unitguitext);
								auto& unittext = coordinator.GetComponent<CanvasText>(unitguitext);
								if (guitype.texttype == GUIText::UNITBUTTON && UnitUIopen)
								{
									guientitystate.active = true;
									if (unitguitype.texttype == GUIText::NORMALUNITCOST)
									{
										unitguientitystate = true;
										unittext.Text = std::to_string(controller.normalunitcost).substr(0, std::to_string(controller.normalunitcost).find('.'));
									}
									else if (unitguitype.texttype == GUIText::RANGEUNITCOST)
									{
										unitguientitystate = true;
										unittext.Text = std::to_string(controller.rangeunitcost).substr(0, std::to_string(controller.rangeunitcost).find('.'));
									}
									else if (unitguitype.texttype == GUIText::TANKUNITCOST)
									{
										unitguientitystate = true;
										unittext.Text = std::to_string(controller.tankunitcost).substr(0, std::to_string(controller.tankunitcost).find('.'));
									}
									else if (unitguitype.texttype == GUIText::NORMALUNITLEVEL)
									{
										unitguientitystate = true;
										unittext.Text = "Lvl " + std::to_string(controller.normalunitlevel);
									}
									else if (unitguitype.texttype == GUIText::RANGEUNITLEVEL)
									{
										unitguientitystate = true;
										unittext.Text = "Lvl " + std::to_string(controller.rangeunitlevel);
									}
									else if (unitguitype.texttype == GUIText::TANKUNITLEVEL)
									{
										unitguientitystate = true;
										unittext.Text = "Lvl " + std::to_string(controller.tankunitlevel);
									}
								}
								else if (guitype.texttype == GUIText::UNITBUTTON && !UnitUIopen)
								{
									guientitystate.active = false;
									if (unitguitype.texttype == GUIText::NORMALUNITCOST)
										unitguientitystate = false;
									else if (unitguitype.texttype == GUIText::RANGEUNITCOST)
										unitguientitystate = false;
									else if (unitguitype.texttype == GUIText::TANKUNITCOST)
										unitguientitystate = false;
									else if (unitguitype.texttype == GUIText::NORMALUNITLEVEL)
										unitguientitystate = false;
									else if (unitguitype.texttype == GUIText::RANGEUNITLEVEL)
										unitguientitystate = false;
									else if (unitguitype.texttype == GUIText::TANKUNITLEVEL)
										unitguientitystate = false;
								}
								else if (guitype.texttype == GUIText::BUILDINGBUTTON && BuildingUIopen)
								{
									guientitystate.active = true;
									if (unitguitype.texttype == GUIText::TOWERCOST)
									{
										unitguientitystate = true;
										unittext.Text = std::to_string(controller.towercost).substr(0, std::to_string(controller.towercost).find('.'));
									}
									else if (unitguitype.texttype == GUIText::WALLCOST)
									{
										unitguientitystate = true;
										unittext.Text = std::to_string(controller.wallcost).substr(0, std::to_string(controller.wallcost).find('.'));
									}
									else if (unitguitype.texttype == GUIText::GENERATOR1COST)
									{
										unitguientitystate = true;
										unittext.Text = std::to_string(controller.generator1cost).substr(0, std::to_string(controller.generator1cost).find('.'));
									}
									else if (unitguitype.texttype == GUIText::GENERATOR2COST)
									{
										unitguientitystate = true;
										unittext.Text = std::to_string(controller.generator2cost).substr(0, std::to_string(controller.generator2cost).find('.'));
									}
								}
								else if (guitype.texttype == GUIText::BUILDINGBUTTON && !BuildingUIopen)
								{
									guientitystate.active = false;
									if (unitguitype.texttype == GUIText::TOWERCOST)
										unitguientitystate = false;
									else if (unitguitype.texttype == GUIText::WALLCOST)
										unitguientitystate = false;
									else if (unitguitype.texttype == GUIText::GENERATOR1COST)
										unitguientitystate = false;
									else if (unitguitype.texttype == GUIText::GENERATOR2COST)
										unitguientitystate = false;
								}
							}
						}

					}
				}

			}
		}
	}
	// If no selected units, set state to inactive
	else if (selectedunitList.size() == 0)
	{
		
		for (auto const& guitext : m_Entities)
		{
			auto& guientitystate = coordinator.GetComponent<EntityState>(guitext);
			auto& textstate = coordinator.GetComponent<GUIText>(guitext);

			if (textstate.texttype != GUIText::RESOURCES1 && textstate.texttype != GUIText::RESOURCES2)
			{
				guientitystate.active = false;
			}
		}
	}
}

void GUITextSystem::Render()
{
}

void GUITextSystem::SetSelectedUnitList(std::vector<Entity> selectedunitList)
{
	this->selectedunitList = selectedunitList;
}

void GUITextSystem::SetUIopen(bool LabUIopen, bool UnitUIopen, bool BuildingUIopen)
{
	this->LabUIopen = LabUIopen;
	this->UnitUIopen = UnitUIopen;
	this->BuildingUIopen = BuildingUIopen;
}
