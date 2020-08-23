#include <string>
#include "Mesh.h"
#include <vector>
#include "Transform.h"
#include "MeshManager.h"

#pragma once

struct TerrainData
{
    GEO_TYPE terrain;
    std::vector<unsigned char> heightmap;
    Transform transform;

    TerrainData()
    {

    }

    TerrainData(GEO_TYPE t)
    {
        terrain = t;
    }

    float ReadHeightMap(float x, float z)
    {
        x += transform.position.x;
        z += transform.position.z;
        x / transform.scale.x;
        z / transform.scale.z;

        if (x < -0.5f || x > 0.5f || z < -0.5f || z > 0.5f)
            return 0;
        if (heightmap.size() == 0)
            return 0;

        unsigned terrainSize = (unsigned)sqrt((double)heightmap.size());

        unsigned zCoord = (unsigned)((z + 0.5f) * terrainSize);
        unsigned xCoord = (unsigned)((x + 0.5f) * terrainSize);

        return (((float)heightmap[zCoord * terrainSize + xCoord] / 256.f) * transform.scale.y) + transform.position.y;
    }
};
