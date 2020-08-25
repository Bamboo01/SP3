#include "Mesh.h"
#include "MeshBuilder.h"
#include <assert.h>

#pragma once

enum GEO_TYPE
{
	GEO_AXES,
	GEO_CUBE,
	GEO_GUIQUAD,
	GEO_GRIDCUBE,
	GEO_GRID,
	GEO_TERRAIN,
	GEO_TESTPARTICLE_CYLINDRICAL,
	GEO_TESTPARTICLE_SPHERICAL,

	GEO_MENU_NEXUS,
	GEO_CODEPARTICLE,
	GEO_MENU_UNIT1,
	GEO_MENU_UNIT2,
	GEO_MENU_UNIT3,

	NUM_MESH
};

class MeshManager
{
public:

	MeshManager();
	~MeshManager();
	Mesh* meshList[NUM_MESH];
	std::unordered_map<Mesh*, SpriteAnimation> animList;
	std::unordered_map <Mesh*, std::vector<unsigned char>> m_terrainList;
	Mesh* CreateTerrain(GEO_TYPE type, const char* path);
	void Update(float dt);
};

