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

	GEO_UNIT_NORMAL_PLAYER,
	GEO_UNIT_TANK_PLAYER,
	GEO_UNIT_RANGE_PLAYER,
	GEO_UNIT_TOWER_PLAYER,
	GEO_UNIT_WALL_PLAYER,
	GEO_UNIT_NEXUS_PLAYER,
	GEO_UNIT_GENERATOR1_PLAYER,
	GEO_UNIT_GENERATOR2_PLAYER,
	GEO_LAB_PLAYER,
	GEO_PROJECTILE_PLAYER,

	GEO_UNIT_NORMAL_ENEMY,
	GEO_UNIT_TANK_ENEMY,
	GEO_UNIT_RANGE_ENEMY,
	GEO_UNIT_TOWER_ENEMY,
	GEO_UNIT_WALL_ENEMY,
	GEO_UNIT_NEXUS_ENEMY,
	GEO_UNIT_GENERATOR1_ENEMY,
	GEO_UNIT_GENERATOR2_ENEMY,
	GEO_LAB_ENEMY,
	GEO_PROJECTILE_ENEMY,

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

