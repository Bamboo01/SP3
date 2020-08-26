#include "CanvasImageUpdateSystem.h"
#include "Application.h"

CanvasImageUpdateSystem::~CanvasImageUpdateSystem()
{
	glDeleteTextures(1, &nexustexture);
	glDeleteTextures(1, &labtexture);
	glDeleteTextures(1, &generator1texture);
	glDeleteTextures(1, &generator2texture);
	glDeleteTextures(1, &towertexture);
	glDeleteTextures(1, &walltexture);
	glDeleteTextures(1, &normalunittexture);
	glDeleteTextures(1, &rangeunittexture);
	glDeleteTextures(1, &tankunittexture);
}

void CanvasImageUpdateSystem::Setup()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<CanvasImage>());
	signature.set(coordinator.GetComponentType<Transform>());
	signature.set(coordinator.GetComponentType<CanvasImageUpdate>());
	signature.set(coordinator.GetComponentType<EntityState>());
	coordinator.SetSystemSignature<CanvasImageUpdateSystem>(signature);
}

void CanvasImageUpdateSystem::Init(std::set<Entity>* controllerentity)
{
	timer = 0;
	clickdelay = 0;
	CursorinGUI = false;
	LabUIopen = false;
	UnitUIopen = false;
	BuildingUIopen = false;
	renderonce = false;
	renderamount = 0;
	increment = 0;
	selectedbuilding = 0;
	buildingclickdelay = 0;
	createonce = false;
	this->controllerentity = controllerentity;

	nexustexture = LoadTGA("Images//nexus.tga");
	labtexture = LoadTGA("Images//lab.tga");
	generator1texture = LoadTGA("Images//generator1.tga");
	generator2texture = LoadTGA("Images//generator2.tga");
	towertexture = LoadTGA("Images//tower.tga");
	walltexture = LoadTGA("Images//wall.tga");
	normalunittexture = LoadTGA("Images//normal.tga");
	rangeunittexture = LoadTGA("Images//range.tga");
	tankunittexture = LoadTGA("Images//tank.tga");

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
			clickdelay = timer + 0.2;
			if (canvasupdate.buttontype == CanvasImageUpdate::LABBUTTON || canvasupdate.buttontype == CanvasImageUpdate::NEXUSCREATEUNITBUTTON || canvasupdate.buttontype == CanvasImageUpdate::NEXUSCREATEBUILDINGBUTTON)
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
							if (canvasupdate3.buttontype == CanvasImageUpdate::NEXUSBUILDING || canvasupdate3.buttontype == CanvasImageUpdate::NEXUSWALL || canvasupdate3.uniquetype == CanvasImageUpdate::NEXUSBUILDINGUI || canvasupdate3.buttontype == CanvasImageUpdate::NEXUSGENERATOR1 || canvasupdate3.buttontype == CanvasImageUpdate::NEXUSGENERATOR2)
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
								if (canvasupdate3.buttontype == CanvasImageUpdate::NEXUSBUILDING || canvasupdate3.buttontype == CanvasImageUpdate::NEXUSWALL || canvasupdate3.buttontype == CanvasImageUpdate::NEXUSGENERATOR1 || canvasupdate3.buttontype == CanvasImageUpdate::NEXUSGENERATOR2)
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
								if (canvasupdate3.buttontype == CanvasImageUpdate::NEXUSBUILDING || canvasupdate3.buttontype == CanvasImageUpdate::NEXUSWALL || canvasupdate3.buttontype == CanvasImageUpdate::NEXUSGENERATOR1 || canvasupdate3.buttontype == CanvasImageUpdate::NEXUSGENERATOR2)
								{
									entitystate3.active = false;
								}
							}
						}
					}
				}
			}

			for (auto const& control : *controllerentity)
			{
				auto& controller = coordinator.GetComponent<Controller>(control);
				if (controller.controllertype == Controller::PLAYER)
				{
					for (auto entity2 : selectedunitList)
					{
						auto& unit = coordinator.GetComponent<Unit>(entity2);
						if (canvasupdate.buttontype == CanvasImageUpdate::GENERATOR1BUTTON && unit.unitType == Unit::GENERATOR1 && unit.resourcesgenerated != 0)
						{
							// When click, collect resources
							controller.resource1 += unit.resourcesgenerated;
							unit.resourcesgenerated = 0;
						}
						else if (canvasupdate.buttontype == CanvasImageUpdate::GENERATOR2BUTTON && unit.unitType == Unit::GENERATOR2 && unit.resourcesgenerated != 0)
						{
							// When click, collect resources
							controller.resource2 += unit.resourcesgenerated;
							unit.resourcesgenerated = 0;
						}
					}
					// Lab unit button clicks to level up unit
					if (canvasupdate.buttontype == CanvasImageUpdate::LABNORMALUNIT)
					{
						//Level up normal unit (Check whether is there enough resources)
						if (controller.normalunitlevel <= 3)
						{
							if (controller.resource1 >= controller.levelupnormalcost)
							{
								controller.normalunitlevel += 1;
								controller.resource1 -= controller.levelupnormalcost;
							}
						}
						else if (controller.normalunitlevel > 3)
						{
							if (controller.resource1 >= controller.levelupnormalcost && controller.resource2 >= controller.levelupnormalcost2)
							{
								controller.normalunitlevel += 1;
								controller.resource1 -= controller.levelupnormalcost;
								controller.resource2 -= controller.levelupnormalcost2;
							}
						}
					}
					else if (canvasupdate.buttontype == CanvasImageUpdate::LABTANKUNIT)
					{
						//Level up tank unit (Check whether is there enough resources)
						if (controller.tankunitlevel <= 3)
						{
							if (controller.resource1 >= controller.leveluptankcost)
							{
								controller.tankunitlevel += 1;
								controller.resource1 -= controller.leveluptankcost;
							}
						}
						else if (controller.tankunitlevel > 3)
						{
							if (controller.resource1 >= controller.leveluptankcost && controller.resource2 >= controller.leveluptankcost2)
							{
								controller.tankunitlevel += 1;
								controller.resource1 -= controller.leveluptankcost;
								controller.resource2 -= controller.leveluptankcost2;
							}
						}
					}
					else if (canvasupdate.buttontype == CanvasImageUpdate::LABRANGEUNIT)
					{
						//Level up normal unit (Check whether is there enough resources)
						if (controller.rangeunitlevel <= 3)
						{
							if (controller.resource1 >= controller.leveluprangecost)
							{
								controller.rangeunitlevel += 1;
								controller.resource1 -= controller.leveluprangecost;
							}
						}
						else if (controller.rangeunitlevel > 3)
						{
							if (controller.resource1 >= controller.leveluprangecost && controller.resource2 >= controller.leveluprangecost2)
							{
								controller.rangeunitlevel += 1;
								controller.resource1 -= controller.leveluprangecost;
								controller.resource2 -= controller.leveluprangecost2;
							}
						}
					}
					// Nexus unit button clicks to create unit
					else if (canvasupdate.buttontype == CanvasImageUpdate::NEXUSNORMALUNIT)
					{
						// Add code to spawn normal unit (Check whether is there enough resources)
						if (controller.resource1 >= controller.normalunitcost)
						{
							std::cout << "Normal unit created" << std::endl;
							controller.resource1 -= controller.normalunitcost;
							unitsystem->CreateUnit(Unit::NORMAL, Unit::PLAYER, controller.normalunitlevel, Transform(glm::vec3(130, 0, 150), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), DYNAMIC_TRANSFORM));
						}
					}
					else if (canvasupdate.buttontype == CanvasImageUpdate::NEXUSTANKUNIT)
					{
						// Add code to spawn tank unit (Check whether is there enough resources)
						if (controller.resource1 >= controller.tankunitcost)
						{
							std::cout << "Tank unit created" << std::endl;
							controller.resource1 -= controller.tankunitcost;
							unitsystem->CreateUnit(Unit::TANK, Unit::PLAYER, controller.tankunitlevel, Transform(glm::vec3(130, 0, 150), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), DYNAMIC_TRANSFORM));
						}
					}
					else if (canvasupdate.buttontype == CanvasImageUpdate::NEXUSRANGEUNIT)
					{
						if (controller.resource1 >= controller.rangeunitcost)
						{
							// Add code to spawn range unit (Check whether is there enough resources)
							std::cout << "Range unit created" << std::endl;
							controller.resource1 -= controller.rangeunitcost;
							unitsystem->CreateUnit(Unit::RANGE, Unit::PLAYER, controller.rangeunitlevel, Transform(glm::vec3(130, 0, 150), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), DYNAMIC_TRANSFORM));
						}
					}
					else if (canvasupdate.buttontype == CanvasImageUpdate::NEXUSBUILDING)
					{
						if (controller.resource1 >= controller.towercost)
						{
							// Add code to spawn building (Check whether is there enough resources)
							std::cout << "Tower created" << std::endl;
							controller.resource1 -= controller.towercost;
							selectedbuilding = 1;
							buildingclickdelay = timer + 0.4;
							createonce = true;
						}
					}
					else if (canvasupdate.buttontype == CanvasImageUpdate::NEXUSWALL)
					{
						if (controller.resource1 >= controller.wallcost)
						{
							// Add code to spawn wall (Check whether is there enough resources)
							std::cout << "Wall created" << std::endl;
							controller.resource1 -= controller.wallcost;
							selectedbuilding = 2;
							buildingclickdelay = timer + 0.4;
							createonce = true;
						}
					}
					else if (canvasupdate.buttontype == CanvasImageUpdate::NEXUSGENERATOR1)
					{
						if (controller.resource1 >= controller.generator1cost)
						{
							// Add code to spawn generator1 (Check whether is there enough resources)
							std::cout << "Generator1 created" << std::endl;
							controller.resource1 -= controller.generator1cost;
							selectedbuilding = 3;
							buildingclickdelay = timer + 0.4;
							createonce = true;
						}
					}
					else if (canvasupdate.buttontype == CanvasImageUpdate::NEXUSGENERATOR2)
					{
						if (controller.resource1 >= controller.generator2cost)
						{
							// Add code to spawn generator2 (Check whether is there enough resources)
							std::cout << "Generator2 created" << std::endl;
							controller.resource1 -= controller.generator2cost;
							selectedbuilding = 4;
							buildingclickdelay = timer + 0.4;
							createonce = true;
						}
					}
				}
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
				if (unit.unitType == Unit::GENERATOR1)
				{
					if (canvasupdate.buttontype == CanvasImageUpdate::GENERATOR1BUTTON)
					{
						entitystate.active = true;
					}
				}
				else if (unit.unitType == Unit::GENERATOR2)
				{
					if (canvasupdate.buttontype == CanvasImageUpdate::GENERATOR2BUTTON)
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
			if (increment < selectedunitList.size())
			{
				for (int i = 0 + increment; i < selectedunitList.size(); ++i)
				{
					Entity temp = selectedunitList[i];
					auto& unit = coordinator.GetComponent<Unit>(temp);
					if (canvasupdate.uniquetype == CanvasImageUpdate::PICUI && !entitystate.active && !renderonce)
					{
						renderamount++;
						entitystate.active = true;
						// Add code here to change the texture based on the unit type
						if (unit.unitType == Unit::NEXUS)
						{
							canvas.TextureID = nexustexture;
							++increment;
							break;
						}
						if (unit.unitType == Unit::LAB)
						{
							canvas.TextureID = labtexture;
							++increment;
							break;
						}
						if (unit.unitType == Unit::GENERATOR1)
						{
							canvas.TextureID = generator1texture;
							++increment;
							break;
						}
						if (unit.unitType == Unit::GENERATOR2)
						{
							canvas.TextureID = generator2texture;
							++increment;
							break;
						}
						if (unit.unitType == Unit::TOWER)
						{
							canvas.TextureID = towertexture;
							++increment;
							break;
						}
						if (unit.unitType == Unit::WALL)
						{
							canvas.TextureID = walltexture;
							++increment;
							break;
						}
						if (unit.unitType == Unit::NORMAL)
						{
							canvas.TextureID = normalunittexture;
							++increment;
							break;
						}
						if (unit.unitType == Unit::RANGE)
						{
							canvas.TextureID = rangeunittexture;
							++increment;
							break;
						}
						if (unit.unitType == Unit::TANK)
						{
							canvas.TextureID = tankunittexture;
							++increment;
							break;
						}
					}
				}
				if (renderamount == selectedunitList.size())
					renderonce = true;
			}
		}
		// If no unit is selected, make all pop up GUI active to false
		else
		{
			LabUIopen = false;
			UnitUIopen = false;
			BuildingUIopen = false;
			renderonce = false;
			renderamount = 0;
			increment = 0;
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

void CanvasImageUpdateSystem::SetUnitSystem(std::shared_ptr<UnitSystem> system)
{
	unitsystem = system;
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