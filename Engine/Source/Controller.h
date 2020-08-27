#pragma once

#include "glm.hpp"

struct Controller
{
	float resource1;
	float resource2;

	int normalunitlevel;
	int rangeunitlevel;
	int tankunitlevel;

	float normalunitcost;
	float rangeunitcost;
	float tankunitcost;
	float normalunitcost2;
	float rangeunitcost2;
	float tankunitcost2;
	float towercost;
	float wallcost;
	float generator1cost;
	float generator2cost;

	float levelupnormalcost;
	float leveluprangecost;
	float leveluptankcost;
	float levelupnormalcost2;
	float leveluprangecost2;
	float leveluptankcost2;

	float buildrange;
	glm::vec3 nexusposition;

	enum ControllerType
	{
		DEFAULT,
		PLAYER,
		ENEMY,
	};

	ControllerType controllertype;

	Controller() 
	{
		resource1 = 200;
		resource2 = 0;
		normalunitlevel = 1;
		rangeunitlevel = 1;
		tankunitlevel = 1;
		normalunitcost = normalunitlevel * 50;
		rangeunitcost = rangeunitlevel * 100;
		tankunitcost = tankunitlevel * 150;
		normalunitcost2 = normalunitlevel * 40;
		rangeunitcost2 = rangeunitlevel * 80;
		tankunitcost2 = tankunitlevel * 110;
		towercost = 250;
		wallcost = 30;
		generator1cost = 160;
		generator2cost = 160;
		levelupnormalcost = normalunitlevel * 30;
		leveluprangecost = rangeunitlevel * 130;
		leveluptankcost = tankunitlevel * 200;
		levelupnormalcost2 = normalunitlevel * 70;
		leveluprangecost2 = rangeunitlevel * 160;
		leveluptankcost2 = tankunitlevel * 230;
		buildrange = 200;
		nexusposition = glm::vec3(0, 0, 0);
		controllertype = DEFAULT;
	}

	Controller(ControllerType controllertype, glm::vec3 nexusposition)
	{
		this->controllertype = controllertype;
		this->nexusposition = nexusposition;
		resource1 = 1000;
		resource2 = 0;
		normalunitlevel = 1;
		rangeunitlevel = 1;
		tankunitlevel = 1;
		normalunitcost = normalunitlevel * 50;
		rangeunitcost = rangeunitlevel * 100;
		tankunitcost = tankunitlevel * 150;
		normalunitcost2 = normalunitlevel * 40;
		rangeunitcost2 = rangeunitlevel * 80;
		tankunitcost2 = tankunitlevel * 110;
		towercost = 250;
		wallcost = 30;
		generator1cost = 160;
		generator2cost = 160;
		levelupnormalcost = normalunitlevel * 30;
		leveluprangecost = rangeunitlevel * 130;
		leveluptankcost = tankunitlevel * 200;
		levelupnormalcost2 = normalunitlevel * 70;
		leveluprangecost2 = rangeunitlevel * 160;
		leveluptankcost2 = tankunitlevel * 230;
		buildrange = 200;
	}

};