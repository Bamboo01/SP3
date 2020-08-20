#include "GL/glew.h"
#include <string>
#pragma once

struct CanvasImage
{
	std::string ImagePath;
	unsigned TextureID;

	CanvasImage()
	{
		ImagePath = "";
		TextureID = -1;
	}

	CanvasImage(std::string path)
	{
		ImagePath = path;
		TextureID = -1;
	}

	~CanvasImage()
	{
		if (TextureID != unsigned(-1))
		{
			glDeleteTextures(1, &TextureID);
		}
	}
};