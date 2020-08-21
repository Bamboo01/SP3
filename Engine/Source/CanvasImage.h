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
};