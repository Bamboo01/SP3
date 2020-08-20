#include <string>
#pragma once

enum TEXT_ALIGNMENT
{
	ALIGN_LEFT,
	ALIGN_RIGHT,
	ALIGN_CENTER
};

struct CanvasText
{

	std::string Text;
	TEXT_ALIGNMENT Alignment;
	float size;

	CanvasText()
	{
		Text = "";
		Alignment = ALIGN_CENTER;
		size = 0.1f;
	}

	CanvasText(std::string text, TEXT_ALIGNMENT alignment = ALIGN_CENTER, float s = 0.1f)
	{
		Text = text;
		Alignment = alignment;
		size = s;
	}
};