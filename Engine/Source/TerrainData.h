#include <string>
#include "Mesh.h"
#include <vector>
#pragma once

struct TerrainData
{
	GEO_TYPE terrain;
	std::vector<unsigned char> heightmap;

	TerrainData()
	{
		
	}

	TerrainData(GEO_TYPE t)
	{
		terrain = t;
	}
};
