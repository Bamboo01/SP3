#include "GUITextSystem.h"

void GUITextSystem::Setup()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<Transform>());
	signature.set(coordinator.GetComponentType<GUIText>());
	signature.set(coordinator.GetComponentType<EntityState>());
	coordinator.SetSystemSignature<GUITextSystem>(signature);
}

void GUITextSystem::Init()
{
	LabUIopen = false;
	UnitUIopen = false;
	BuildingUIopen = false;

	for (auto const& entity : m_Entities)
	{
		auto& transform = coordinator.GetComponent<Transform>(entity);
		auto& text = coordinator.GetComponent<CanvasText>(entity);
		auto& textstate = coordinator.GetComponent<GUIText>(entity);
		auto& entitystate = coordinator.GetComponent<EntityState>(entity);

		if (textstate.texttype != GUIText::RESOURCES)
		{
			entitystate.active = false;
		}
		ReferenceEntity.push_back(entity);
	}
}

void GUITextSystem::Update(double dt)
{
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

				if (unit.unitType == Unit::GENERATOR)
				{
					if (guitype.texttype == GUIText::GENERATORBUTTON)
						guientitystate.active = true;
				}
				else if (unit.unitType == Unit::LAB)
				{
					if (guitype.texttype == GUIText::LABBUTTON)
						guientitystate.active = true;
					else if (guitype.texttype == GUIText::UNITBUTTON && LabUIopen)
						guientitystate.active = true;
					else if (guitype.texttype == GUIText::UNITBUTTON && !LabUIopen)
						guientitystate.active = false;
				}
				else if (unit.unitType == Unit::NEXUS)
				{
					if (guitype.texttype == GUIText::NEXUSBUTTON)
						guientitystate.active = true;
					else if (guitype.texttype == GUIText::UNITBUTTON && UnitUIopen)
						guientitystate.active = true;
					else if (guitype.texttype == GUIText::UNITBUTTON && !UnitUIopen)
						guientitystate.active = false;
					else if (guitype.texttype == GUIText::BUILDINGBUTTON && BuildingUIopen)
						guientitystate.active = true;
					else if (guitype.texttype == GUIText::BUILDINGBUTTON && !BuildingUIopen)
						guientitystate.active = false;

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

			if (textstate.texttype != GUIText::RESOURCES)
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
