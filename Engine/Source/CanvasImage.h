#include "GL/glew.h"
#include <string>
#pragma once

struct CanvasImage
{
	std::string ImagePath;
	unsigned TextureID;

	bool active;

	enum ClickType
	{
		START,
		CLICKABLE,
		NONCLICKABLE,
		END
	};

	enum ButtonType
	{
		START2 = 0,
		GENERATORBUTTON,
		LABBUTTON,
		LABNORMALUNIT,
		LABTANKUNIT,
		LABRANGEUNIT,
		NEXUSCREATEUNITBUTTON,
		NEXUSCREATEBUILDINGBUTTON,
		NEXUSNORMALUNIT,
		NEXUSTANKUNIT,
		NEXUSRANGEUNIT,
		NEXUSBUILDING,
		NEXUSWALL,
		END2
	};

	enum PopUpType
	{
		START3,
		POPUP,
		NONPOPUP,
		END3
	};

	enum UniqueUI
	{
		START4,
		LABUI,
		NEXUSUNITUI,
		NEXUSBUILDINGUI
	};

	ClickType clicktype;
	ButtonType buttontype;
	PopUpType popuptype;
	UniqueUI uniquetype;

	CanvasImage()
	{
		ImagePath = "";
		TextureID = -1;
		clicktype = START;
		buttontype = START2;
		popuptype = START3;
		uniquetype = START4;
		active = false;
	}

	CanvasImage(std::string path, ClickType clicktype, ButtonType buttontype, PopUpType popuptype, UniqueUI uniquetype, bool active)
	{
		ImagePath = path;
		TextureID = -1;
		this->clicktype = clicktype;
		this->buttontype = buttontype;
		this->popuptype = popuptype;
		this->uniquetype = uniquetype;
		this->active = active;
	}

	~CanvasImage()
	{
		if (TextureID != unsigned(-1))
		{
			glDeleteTextures(1, &TextureID);
		}
	}
};