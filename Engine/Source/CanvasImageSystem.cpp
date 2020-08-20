#include "CanvasImageSystem.h"
#include "Application.h"

void CanvasImageSystem::Setup()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<CanvasImage>());
	signature.set(coordinator.GetComponentType<Transform>());
	coordinator.SetSystemSignature<CanvasImageSystem>(signature);
}

void CanvasImageSystem::Init()
{
	timer = 0;
	clickdelay = 0;

	for (auto const& entity : m_Entities)
	{
		auto& canvasimage = coordinator.GetComponent<CanvasImage>(entity);
		canvasimage.TextureID = LoadTGA(canvasimage.ImagePath.c_str());
	}
}

void CanvasImageSystem::Update(double dt)
{
	timer += dt;
	
	for (auto const& entity : m_Entities)
	{
		auto& transform = coordinator.GetComponent<Transform>(entity);
		auto& canvas = coordinator.GetComponent<CanvasImage>(entity);

		// Check for clicking on clickable quad (Buttons)
		if (canvas.clicktype == CanvasImage::CLICKABLE && Application::IsMousePressed(VK_LBUTTON) && CollideWithCanvas(transform.position.x, transform.position.y, transform.scale.x, transform.scale.y) && canvas.active == true && clickdelay <= timer)
		{
			clickdelay = timer + 0.3;
			if (canvas.buttontype == CanvasImage::GENERATORBUTTON)
			{
				// When click, collect resources
				std::cout << "Generator Click!" << std::endl;
			}
			else if (canvas.buttontype == CanvasImage::LABBUTTON || canvas.buttontype == CanvasImage::NEXUSCREATEUNITBUTTON || canvas.buttontype == CanvasImage::NEXUSCREATEBUILDINGBUTTON)
			{
				std::cout << "Lab/Nexus Click!" << std::endl;
				for (auto const& entity2 : m_Entities)
				{
					auto& canvas2 = coordinator.GetComponent<CanvasImage>(entity2);

					// If lab button was clicked, open lab UI
					if (canvas.buttontype == CanvasImage::LABBUTTON)
					{
						if (canvas2.uniquetype == CanvasImage::LABUI && canvas2.active == false)
						{
							canvas2.active = true;

							// If lab UI is open, set unit buttons active to true
							for (auto const& entity3 : m_Entities)
							{
								auto& canvas3 = coordinator.GetComponent<CanvasImage>(entity3);
								if (canvas3.buttontype == CanvasImage::LABNORMALUNIT || canvas3.buttontype == CanvasImage::LABTANKUNIT || canvas3.buttontype == CanvasImage::LABRANGEUNIT)
								{
									canvas3.active = true;
								}
							}
						}

						// When click again, close lab UI
						else if (canvas2.uniquetype == CanvasImage::LABUI && canvas2.active == true)
						{
							canvas2.active = false;
							// If lab UI is close, set unit buttons active to false
							for (auto const& entity3 : m_Entities)
							{
								auto& canvas3 = coordinator.GetComponent<CanvasImage>(entity3);
								if (canvas3.buttontype == CanvasImage::LABNORMALUNIT || canvas3.buttontype == CanvasImage::LABTANKUNIT || canvas3.buttontype == CanvasImage::LABRANGEUNIT)
								{
									canvas3.active = false;
								}
							}
						}
					}
					// If nexus create unit button was clicked, open create UI (Same as lab UI, but different button)
					if (canvas.buttontype == CanvasImage::NEXUSCREATEUNITBUTTON)
					{
						// Do a check if nexus create building is open, if it is, close it before opening nexus create unit
						for (auto const& entity3 : m_Entities)
						{
							auto& canvas3 = coordinator.GetComponent<CanvasImage>(entity3);
							if (canvas3.buttontype == CanvasImage::NEXUSBUILDING || canvas3.buttontype == CanvasImage::NEXUSWALL || canvas3.uniquetype == CanvasImage::NEXUSBUILDINGUI)
							{
								canvas3.active = false;
							}
						}

						if (canvas2.uniquetype == CanvasImage::NEXUSUNITUI && canvas2.active == false)
						{
							canvas2.active = true;

							// If nexus create UI is open, set unit buttons active to true
							for (auto const& entity3 : m_Entities)
							{
								auto& canvas3 = coordinator.GetComponent<CanvasImage>(entity3);
								if (canvas3.buttontype == CanvasImage::NEXUSNORMALUNIT || canvas3.buttontype == CanvasImage::NEXUSTANKUNIT || canvas3.buttontype == CanvasImage::NEXUSRANGEUNIT)
								{
									canvas3.active = true;
								}
							}
						}

						// When click again, close nexus create unit UI
						else if (canvas2.uniquetype == CanvasImage::NEXUSUNITUI && canvas2.active == true)
						{
							canvas2.active = false;
							// If nexus create unit UI is close, set unit buttons active to false
							for (auto const& entity3 : m_Entities)
							{
								auto& canvas3 = coordinator.GetComponent<CanvasImage>(entity3);
								if (canvas3.buttontype == CanvasImage::NEXUSNORMALUNIT || canvas3.buttontype == CanvasImage::NEXUSTANKUNIT || canvas3.buttontype == CanvasImage::NEXUSRANGEUNIT)
								{
									canvas3.active = false;
								}
							}
						}
					}
					// If nexus create building button was clicked, open create UI (Same as lab UI, but different button)
					else if (canvas.buttontype == CanvasImage::NEXUSCREATEBUILDINGBUTTON)
					{
						// Do a check if nexus create unit is open, if it is, close it before opening nexus create building
						for (auto const& entity3 : m_Entities)
						{
							auto& canvas3 = coordinator.GetComponent<CanvasImage>(entity3);
							if (canvas3.buttontype == CanvasImage::NEXUSNORMALUNIT || canvas3.buttontype == CanvasImage::NEXUSTANKUNIT || canvas3.buttontype == CanvasImage::NEXUSRANGEUNIT || canvas3.uniquetype == CanvasImage::NEXUSUNITUI)
							{
								canvas3.active = false;
							}
						}

						if (canvas2.uniquetype == CanvasImage::NEXUSBUILDINGUI && canvas2.active == false)
						{
							canvas2.active = true;

							// If nexus create UI is open, set unit buttons active to true
							for (auto const& entity3 : m_Entities)
							{
								auto& canvas3 = coordinator.GetComponent<CanvasImage>(entity3);
								if (canvas3.buttontype == CanvasImage::NEXUSBUILDING || canvas3.buttontype == CanvasImage::NEXUSWALL)
								{
									canvas3.active = true;
								}
							}
						}

						// When click again, close nexus create building UI
						else if (canvas2.uniquetype == CanvasImage::NEXUSBUILDINGUI && canvas2.active == true)
						{
							canvas2.active = false;
							// If nexus create UI is close, set unit buttons active to false
							for (auto const& entity3 : m_Entities)
							{
								auto& canvas3 = coordinator.GetComponent<CanvasImage>(entity3);
								if (canvas3.buttontype == CanvasImage::NEXUSBUILDING || canvas3.buttontype == CanvasImage::NEXUSWALL)
								{
									canvas3.active = false;
								}
							}
						}
					}
				}
			}
			// Lab unit button clicks to level up unit
			else if (canvas.buttontype == CanvasImage::LABNORMALUNIT)
			{
				// Add code to Level up normal unit (Check whether is there enough resources)
				std::cout << "Normal unit leveled up" << std::endl;
			}
			else if (canvas.buttontype == CanvasImage::LABTANKUNIT)
			{
				// Add code to Level up tank unit (Check whether is there enough resources)
				std::cout << "Tank unit leveled up" << std::endl;
			}
			else if (canvas.buttontype == CanvasImage::LABRANGEUNIT)
			{
				// Add code to Level up range unit (Check whether is there enough resources)
				std::cout << "Range unit leveled up" << std::endl;
			}
			// Nexus unit button clicks to create unit
			else if (canvas.buttontype == CanvasImage::NEXUSNORMALUNIT)
			{
				// Add code to spawn normal unit (Check whether is there enough resources)
				std::cout << "Normal unit created" << std::endl;
			}
			else if (canvas.buttontype == CanvasImage::NEXUSTANKUNIT)
			{
				// Add code to spawn tank unit (Check whether is there enough resources)
				std::cout << "Tank unit created" << std::endl;
			}
			else if (canvas.buttontype == CanvasImage::NEXUSRANGEUNIT)
			{
				// Add code to spawn range unit (Check whether is there enough resources)
				std::cout << "Range unit created" << std::endl;
			}
			else if (canvas.buttontype == CanvasImage::NEXUSBUILDING)
			{
				// Add code to spawn building (Check whether is there enough resources)
				std::cout << "Tower created" << std::endl;
			}
			else if (canvas.buttontype == CanvasImage::NEXUSWALL)
			{
				// Add code to spawn wall (Check whether is there enough resources)
				std::cout << "Wall created" << std::endl;
			}
		}

		// This will be done by looping through the vector of selected unit,
		// If there is only 1 unit, check the type of the unit, then render in whatever quad(button) is needed for that unit info
		if (true)
		{
			std::set<Entity> entityset1 = unitsystem->m_Entities;

			for (auto entity2 : entityset1)
			{
				auto& unit = coordinator.GetComponent<Unit>(entity2);

				// If selected unit is a generator, render in popup button
				if (unit.unittype == Unit::GENERATOR)
				{
					if (canvas.buttontype == CanvasImage::GENERATORBUTTON)
					{
						canvas.active = true;
					}
				}
				// If selected unit is a lab, render in popup button
				else if (unit.unittype == Unit::LAB)
				{
					if (canvas.buttontype == CanvasImage::LABBUTTON)
					{
						canvas.active = true;
					}
				}
				// If selected unit is a nexus, render in popup button
				else if (unit.unittype == Unit::NEXUS)
				{
					if (canvas.buttontype == CanvasImage::NEXUSCREATEUNITBUTTON || canvas.buttontype == CanvasImage::NEXUSCREATEBUILDINGBUTTON)
					{
						canvas.active = true;
					}
				}
			}
		}
		// If no unit is selected, make all pop up GUI active to false
		else
		{
			if (canvas.popuptype == CanvasImage::POPUP)
			{
				canvas.active = false;
			}
		}
	}
}

void CanvasImageSystem::Render()
{
	for (auto const& entity : m_Entities)
	{
		auto& transform = coordinator.GetComponent<Transform>(entity);
		auto& canvasimage = coordinator.GetComponent<CanvasImage>(entity);
		if (canvasimage.active == true)
		{
			glm::mat4 model(1.f);
			glm::vec3 rot = glm::radians(transform.rotation);
			model = glm::translate(model, transform.position);
			model = glm::rotate(model, rot.x, glm::vec3(1, 0, 0));
			model = glm::rotate(model, rot.y, glm::vec3(0, 1, 0));
			model = glm::rotate(model, rot.z, glm::vec3(0, 0, 1));
			model = glm::scale(model, transform.scale);
			renderer.CanvasImage.push_back(std::make_pair(model, canvasimage.TextureID));
		}
	}
}

void CanvasImageSystem::SetUnitSystem(std::shared_ptr<UnitSystem> unitsystem)
{
	this->unitsystem = unitsystem;
}

bool CanvasImageSystem::CollideWithCanvas(float x, float y, float xscale, float yscale)
{
	float bottomleftx, bottomlefty, toprightx, toprighty;

	float offsetx = Application::GetWindowWidth() - Application::GetWindowHeight();
	float offsety = Application::GetWindowHeight() - Application::GetWindowWidth();

	if (Application::GetWindowWidth() > Application::GetWindowHeight())
		offsety = 0;
	else if (Application::GetWindowWidth() < Application::GetWindowHeight())
		offsetx = 0;

	std::cout << offsety << std::endl;

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
	//std::cout << "mousex: " << mousex << std::endl;
	if (mousex > bottomleftx && mousex < toprightx && mousey > bottomlefty && mousey < toprighty)
		return true;
	return false;
}
