#include <string>
#include <glm.hpp>
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
	glm::vec3 color;

	CanvasText()
	{
		Text = "";
		Alignment = ALIGN_CENTER;
		size = 0.1f;
		color = glm::vec3(1, 1, 1);
	}

	CanvasText(std::string text, TEXT_ALIGNMENT alignment = ALIGN_CENTER, glm::vec3 c = glm::vec3(1.f, 1.f, 1.f), float s = 0.1)
	{
		Text = text;
		Alignment = alignment;
		size = s;
		color = c;
	}
};