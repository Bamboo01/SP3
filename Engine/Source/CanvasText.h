#include <string>
#pragma once

struct CanvasText
{
	std::string Text;

	CanvasText()
	{
		Text = "";
	}

	CanvasText(std::string text)
	{
		Text = text;
	}
};