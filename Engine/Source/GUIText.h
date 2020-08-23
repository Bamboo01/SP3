#pragma once

struct GUIText
{
	enum TypeOfText
	{
		START,
		NAME,
		LEVEL,
		HEALTH,
		DAMAGE,
		DEFENSE,
		ATKSPD,
		RESOURCES,
		GENERATORBUTTON,
		LABBUTTON,
		NEXUSBUTTON,
		UNITBUTTON,
		BUILDINGBUTTON
	};

	TypeOfText texttype;

	GUIText() {}

	GUIText(TypeOfText texttype)
	{
		this->texttype = texttype;
	}
};