#include "CanvasImageUpdateSystem.h"
#include "Application.h"

void CanvasImageUpdateSystem::Setup()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<CanvasImage>());
	signature.set(coordinator.GetComponentType<Transform>());
	signature.set(coordinator.GetComponentType<CanvasImageUpdate>());
	signature.set(coordinator.GetComponentType<EntityState>());
	coordinator.SetSystemSignature<CanvasImageUpdateSystem>(signature);
}

void CanvasImageUpdateSystem::Init()
{
	timer = 0;
	clickdelay = 0;
	CursorinGUI = false;
	LabUIopen = false;
	UnitUIopen = false;
	BuildingUIopen = false;
	renderonce = false;
	renderamount = 0;

	for (auto const& entity : m_Entities)
	{
		auto& transform = coordinator.GetComponent<Transform>(entity);
		auto& canvas = coordinator.GetComponent<CanvasImage>(entity);
		auto& canvasupdate = coordinator.GetComponent<CanvasImageUpdate>(entity);
		auto& entitystate = coordinator.GetComponent<EntityState>(entity);

		if (canvasupdate.popuptype == CanvasImageUpdate::POPUP)
		{
			entitystate.active = false;
		}
		ReferenceEntity.push_back(entity);
	}
}

void CanvasImageUpdateSystem::Update(double dt)
{
	timer += dt;

	for (auto const& entity : ReferenceEntity)
	{
		auto& transform = coordinator.GetComponent<Transform>(entity);
		auto& canvas = coordinator.GetComponent<CanvasImage>(entity);
		auto& canvasupdate = coordinator.GetComponent<CanvasImageUpdate>(entity);
		auto& entitystate = coordinator.GetComponent<EntityState>(entity);

		// Check for clicking on clickable quad (Buttons)
		if (canvasupdate.clicktype == CanvasImageUpdate::CLICKABLE && Application::IsMousePressed(0) && CollideWithCanvas(transform.position.x, transform.position.y, transform.scale.x, transform.scale.y) && entitystate.active == true && clickdelay <= timer)
		{
			clickdelay = timer + 0.3;
			if (canvasupdate.buttontype == CanvasImageUpdate::GENERATORBUTTON)
			{
				// When click, collect resources
				std::cout << "Generator Click!" << std::endl;
			}
			else if (canvasupdate.buttontype == CanvasImageUpdate::LABBUTTON || canvasupdate.buttontype == CanvasImageUpdate::NEXUSCREATEUNITBUTTON || canvasupdate.buttontype == CanvasImageUpdate::NEXUSCREATEBUILDINGBUTTON)
			{
				std::cout << "Lab/Nexus Click!" << std::endl;
				for (auto const& entity2 : ReferenceEntity)
				{
					auto& canvasupdate2 = coordinator.GetComponent<CanvasImageUpdate>(entity2);
					auto& entitystate2 = coordinator.GetComponent<EntityState>(entity2);

					// If lab button was clicked, open lab UI
					if (canvasupdate.buttontype == CanvasImageUpdate::LABBUTTON)
					{
						if (canvasupdate2.uniquetype == CanvasImageUpdate::LABUI && entitystate2.active == false)
						{
							LabUIopen = true;
							entitystate2.active = true;

							// If lab UI is open, set unit buttons active to true
							for (auto const& entity3 : ReferenceEntity)
							{
								auto& canvasupdate3 = coordinator.GetComponent<CanvasImageUpdate>(entity3);
								auto& entitystate3 = coordinator.GetComponent<EntityState>(entity3);
								if (canvasupdate3.buttontype == CanvasImageUpdate::LABNORMALUNIT || canvasupdate3.buttontype == CanvasImageUpdate::LABTANKUNIT || canvasupdate3.buttontype == CanvasImageUpdate::LABRANGEUNIT)
								{
									entitystate3.active = true;
								}
							}
						}

						// When click again, close lab UI
						else if (canvasupdate2.uniquetype == CanvasImageUpdate::LABUI && entitystate2.active == true)
						{
							LabUIopen = false;
							entitystate2.active = false;
							// If lab UI is close, set unit buttons active to false
							for (auto const& entity3 : ReferenceEntity)
							{
								auto& canvasupdate3 = coordinator.GetComponent<CanvasImageUpdate>(entity3);
								auto& entitystate3 = coordinator.GetComponent<EntityState>(entity3);
								if (canvasupdate3.buttontype == CanvasImageUpdate::LABNORMALUNIT || canvasupdate3.buttontype == CanvasImageUpdate::LABTANKUNIT || canvasupdate3.buttontype == CanvasImageUpdate::LABRANGEUNIT)
								{
									entitystate3.active = false;
								}
							}
						}
					}
					// If nexus create unit button was clicked, open create UI (Same as lab UI, but different button)
					if (canvasupdate.buttontype == CanvasImageUpdate::NEXUSCREATEUNITBUTTON)
					{
						// Do a check if nexus create building is open, if it is, close it before opening nexus create unit
						for (auto const& entity3 : ReferenceEntity)
						{
							BuildingUIopen = false;
							auto& canvasupdate3 = coordinator.GetComponent<CanvasImageUpdate>(entity3);
							auto& entitystate3 = coordinator.GetComponent<EntityState>(entity3);
							if (canvasupdate3.buttontype == CanvasImageUpdate::NEXUSBUILDING || canvasupdate3.buttontype == CanvasImageUpdate::NEXUSWALL || canvasupdate3.uniquetype == CanvasImageUpdate::NEXUSBUILDINGUI)
							{
								entitystate3.active = false;
							}
						}

						if (canvasupdate2.uniquetype == CanvasImageUpdate::NEXUSUNITUI && entitystate2.active == false)
						{
							UnitUIopen = true;
							entitystate2.active = true;

							// If nexus create UI is open, set unit buttons active to true
							for (auto const& entity3 : ReferenceEntity)
							{
								auto& canvasupdate3 = coordinator.GetComponent<CanvasImageUpdate>(entity3);
								auto& entitystate3 = coordinator.GetComponent<EntityState>(entity3);
								if (canvasupdate3.buttontype == CanvasImageUpdate::NEXUSNORMALUNIT || canvasupdate3.buttontype == CanvasImageUpdate::NEXUSTANKUNIT || canvasupdate3.buttontype == CanvasImageUpdate::NEXUSRANGEUNIT)
								{
									entitystate3.active = true;
								}
							}
						}

						// When click again, close nexus create unit UI
						else if (canvasupdate2.uniquetype == CanvasImageUpdate::NEXUSUNITUI && entitystate2.active == true)
						{
							UnitUIopen = false;
							entitystate2.active = false;
							// If nexus create unit UI is close, set unit buttons active to false
							for (auto const& entity3 : ReferenceEntity)
							{
								auto& canvasupdate3 = coordinator.GetComponent<CanvasImageUpdate>(entity3);
								auto& entitystate3 = coordinator.GetComponent<EntityState>(entity3);
								if (canvasupdate3.buttontype == CanvasImageUpdate::NEXUSNORMALUNIT || canvasupdate3.buttontype == CanvasImageUpdate::NEXUSTANKUNIT || canvasupdate3.buttontype == CanvasImageUpdate::NEXUSRANGEUNIT)
								{
									entitystate3.active = false;
								}
							}
						}
					}
					// If nexus create building button was clicked, open create UI (Same as lab UI, but different button)
					else if (canvasupdate.buttontype == CanvasImageUpdate::NEXUSCREATEBUILDINGBUTTON)
					{
						// Do a check if nexus create unit is open, if it is, close it before opening nexus create building
						for (auto const& entity3 : ReferenceEntity)
						{
							UnitUIopen = false;
							auto& canvasupdate3 = coordinator.GetComponent<CanvasImageUpdate>(entity3);
							auto& entitystate3 = coordinator.GetComponent<EntityState>(entity3);
							if (canvasupdate3.buttontype == CanvasImageUpdate::NEXUSNORMALUNIT || canvasupdate3.buttontype == CanvasImageUpdate::NEXUSTANKUNIT || canvasupdate3.buttontype == CanvasImageUpdate::NEXUSRANGEUNIT || canvasupdate3.uniquetype == CanvasImageUpdate::NEXUSUNITUI)
							{
								entitystate3.active = false;
							}
						}

						if (canvasupdate2.uniquetype == CanvasImageUpdate::NEXUSBUILDINGUI && entitystate2.active == false)
						{
							BuildingUIopen = true;
							entitystate2.active = true;

							// If nexus create UI is open, set unit buttons active to true
							for (auto const& entity3 : ReferenceEntity)
							{
								auto& canvasupdate3 = coordinator.GetComponent<CanvasImageUpdate>(entity3);
								auto& entitystate3 = coordinator.GetComponent<EntityState>(entity3);
								if (canvasupdate3.buttontype == CanvasImageUpdate::NEXUSBUILDING || canvasupdate3.buttontype == CanvasImageUpdate::NEXUSWALL)
								{
									entitystate3.active = true;
								}
							}
						}

						// When click again, close nexus create building UI
						else if (canvasupdate2.uniquetype == CanvasImageUpdate::NEXUSBUILDINGUI && entitystate2.active == true)
						{
							BuildingUIopen = false;
							entitystate2.active = false;
							// If nexus create UI is close, set unit buttons active to false
							for (auto const& entity3 : ReferenceEntity)
							{
								auto& canvasupdate3 = coordinator.GetComponent<CanvasImageUpdate>(entity3);
								auto& entitystate3 = coordinator.GetComponent<EntityState>(entity3);
								if (canvasupdate3.buttontype == CanvasImageUpdate::NEXUSBUILDING || canvasupdate3.buttontype == CanvasImageUpdate::NEXUSWALL)
								{
									entitystate3.active = false;
								}
							}
						}
					}
				}
			}
			// Lab unit button clicks to level up unit
			else if (canvasupdate.buttontype == CanvasImageUpdate::LABNORMALUNIT)
			{
				// Add code to Level up normal unit (Check whether is there enough resources)
				std::cout << "Normal unit leveled up" << std::endl;
			}
			else if (canvasupdate.buttontype == CanvasImageUpdate::LABTANKUNIT)
			{
				// Add code to Level up tank unit (Check whether is there enough resources)
				std::cout << "Tank unit leveled up" << std::endl;
			}
			else if (canvasupdate.buttontype == CanvasImageUpdate::LABRANGEUNIT)
			{
				// Add code to Level up range unit (Check whether is there enough resources)
				std::cout << "Range unit leveled up" << std::endl;
			}
			// Nexus unit button clicks to create unit
			else if (canvasupdate.buttontype == CanvasImageUpdate::NEXUSNORMALUNIT)
			{
				// Add code to spawn normal unit (Check whether is there enough resources)
				std::cout << "Normal unit created" << std::endl;
			}
			else if (canvasupdate.buttontype == CanvasImageUpdate::NEXUSTANKUNIT)
			{
				// Add code to spawn tank unit (Check whether is there enough resources)
				std::cout << "Tank unit created" << std::endl;
			}
			else if (canvasupdate.buttontype == CanvasImageUpdate::NEXUSRANGEUNIT)
			{
				// Add code to spawn range unit (Check whether is there enough resources)
				std::cout << "Range unit created" << std::endl;
			}
			else if (canvasupdate.buttontype == CanvasImageUpdate::NEXUSBUILDING)
			{
				// Add code to spawn building (Check whether is there enough resources)
				std::cout << "Tower created" << std::endl;
			}
			else if (canvasupdate.buttontype == CanvasImageUpdate::NEXUSWALL)
			{
				// Add code to spawn wall (Check whether is there enough resources)
				std::cout << "Wall created" << std::endl;
			}
		}

		// This will be done by looping through the vector of selected unit,
		// If there is only 1 unit, check the type of the unit, then render in whatever quad(button) is needed for that unit info
		if (selectedunitList.size() == 1)
		{
			for (auto entity2 : selectedunitList)
			{
				auto& unit = coordinator.GetComponent<Unit>(entity2);

				// If selected unit is a generator, render in popup button
				if (unit.unitType == Unit::GENERATOR)
				{
					if (canvasupdate.buttontype == CanvasImageUpdate::GENERATORBUTTON)
					{
						entitystate.active = true;
					}
				}
				// If selected unit is a lab, render in popup button
				else if (unit.unitType == Unit::LAB)
				{
					if (canvasupdate.buttontype == CanvasImageUpdate::LABBUTTON)
					{
						entitystate.active = true;
					}
				}
				// If selected unit is a nexus, render in popup button
				else if (unit.unitType == Unit::NEXUS)
				{
					if (canvasupdate.buttontype == CanvasImageUpdate::NEXUSCREATEUNITBUTTON || canvasupdate.buttontype == CanvasImageUpdate::NEXUSCREATEBUILDINGBUTTON)
					{
						entitystate.active = true;
					}
				}
			}
		}
		else if (selectedunitList.size() > 1)
		{
			for (auto entity2 : selectedunitList)
			{
				auto& unit = coordinator.GetComponent<Unit>(entity2);
				if (canvasupdate.uniquetype == CanvasImageUpdate::PICUI && !entitystate.active && !renderonce)
				{
					renderamount++;
					entitystate.active = true;
					// Add code here to change the texture based on the unit type
				}
			}
			if (renderamount == selectedunitList.size())
				renderonce = true;
		}
		// If no unit is selected, make all pop up GUI active to false
		else
		{
			LabUIopen = false;
			UnitUIopen = false;
			BuildingUIopen = false;
			renderonce = false;
			renderamount = 0;
			if (canvasupdate.popuptype == CanvasImageUpdate::POPUP)
			{
				entitystate.active = false;
			}
		}
	}

	for (auto const& entity : ReferenceEntity)
	{
		auto& transform = coordinator.GetComponent<Transform>(entity);
		auto& entitystate = coordinator.GetComponent<EntityState>(entity);

		// Check for whether is the mouse in the GUI, if it is, player can't interact with the map
		if (CollideWithCanvas(transform.position.x, transform.position.y, transform.scale.x, transform.scale.y) && entitystate.active)
		{
			CursorinGUI = true;
			break;
		}
		else
		{
			CursorinGUI = false;
		}
	}
}

void CanvasImageUpdateSystem::Render()
{
}

void CanvasImageUpdateSystem::SetSelectedUnitList(std::vector<Entity> selectedunitList)
{
	this->selectedunitList = selectedunitList;
}

bool CanvasImageUpdateSystem::CollideWithCanvas(float x, float y, float xscale, float yscale)
{
	float bottomleftx, bottomlefty, toprightx, toprighty;

	float offsetx = Application::GetWindowWidth() - Application::GetWindowHeight();
	float offsety = Application::GetWindowHeight() - Application::GetWindowWidth();

	if (Application::GetWindowWidth() > Application::GetWindowHeight())
		offsety = 0;
	else if (Application::GetWindowWidth() < Application::GetWindowHeight())
		offsetx = 0;

	float newx = ((x + 1) / 2) * (Application::GetWindowWidth() - offsetx);
	float newy = ((y + 1) / 2) * (Application::GetWindowHeight() + offsety);
	float newxscale = (xscale) * (Application::GetWindowWidth() - offsetx);
	float newyscale = (yscale) * (Application::GetWindowHeight() + offsety);

	bottomleftx = newx - newxscale * 0.5 + (offsetx * 0.5);
	bottomlefty = (Application::GetWindowHeight() - newy) - newyscale * 0.5 - (offsety * 0.5);
	toprightx = newx + newxscale * 0.5 + (offsetx * 0.5);
	toprighty = (Application::GetWindowHeight() - newy) + newyscale * 0.5 - (offsety * 0.5);


	double mousex, mousey;
	Application::GetCursorPos(&mousex, &mousey);
	if (mousex > bottomleftx && mousex < toprightx && mousey > bottomlefty && mousey < toprighty)
		return true;
	return false;
}
