#include <glm.hpp>
#include <vector>
#include <algorithm>
#include <memory>
#include "GridControllerSystem.h"
#include "Controller.h"

#pragma once

struct Event
{
	float severity;
	glm::vec3 position;

	Event(glm::vec3 pos, float s)
	{
		position = pos;
		severity = s;
	}
};

struct AIController : public Controller
{
	float PlayerAggression;
	float AIAggression;
	float TotalAggression; //Lower is more aggressive, Higher is more defensive!

	float AIAggroTimer;
	float PlayerAggroTimer;
	float ProcessEventsTimer;
	float ProcessTacticsTimer;

	std::vector<Event> eventlist;
	std::vector<Entity> unitlist;

	std::shared_ptr<GridControllerSystem> gridcontrollersystem;

	AIController()
	{

	}

	AIController(std::shared_ptr<GridControllerSystem> gcs, ControllerType controllertype, glm::vec3 nexusposition) : Controller(controllertype, nexusposition)
	{
		PlayerAggression = 0.f;
		AIAggression = 0.f;
		TotalAggression = 0.f;

		AIAggroTimer = 0.f;
		PlayerAggroTimer = 0.f;
		ProcessEventsTimer = 0.f;
		ProcessTacticsTimer = 0.f;
		gridcontrollersystem = gcs;
	}

	void sortEventSeverity()
	{
		//First, merge the severity of events that are close to each other
		for (auto event1 = eventlist.begin(); event1 < eventlist.end();)
		{
			for (auto event2 = event1; event2 < eventlist.end();)
			{
				if(event2 == event1)
				{
					continue;
				}
				if (glm::length(event1->position - event2->position) < 10.f)
				{
					event1->severity += event2->severity;
					event2 = eventlist.erase(event2);
				}
				else
				{
					++event2;
				}
			}
		}
		//Next, sort the list of events from highest to lowest
		std::sort(eventlist.begin(), eventlist.end(), [](const Event& x, const Event& y) { return x.severity > y.severity; });
	}

	void updateUnitList(std::vector<Entity> a)
	{
		unitlist.clear();
		unitlist.shrink_to_fit();
		for (auto e : a)
		{
			unitlist.push_back(e);
		}
	}

	void LogEvent(glm::vec3 position, float severity)
	{
		PlayerAggression += severity / 1.0f;
		eventlist.push_back(Event(position, severity));
	}
};
