#include "MeshManager.h"
#include "LoadTexture.h"
#include "LoadTGA.h"
#include "LoadHmap.h"
#include "Vertex.h"

MeshManager::MeshManager()
{
	bool isfilled = true;

	for (int i = 0; i < NUM_MESH; i++)
	{
		meshList[i] = NULL;
	}

	//Initialise your meshes here

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference");
	meshList[GEO_AXES]->Init();

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_CUBE]->Init(50000);
	meshList[GEO_GRID] = MeshBuilder::GenerateCube("grid", Color(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_GRID]->Init(5000);

	meshList[GEO_GUIQUAD] = MeshBuilder::GenerateQuad("cube", Color(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_GUIQUAD]->Init();

	meshList[GEO_MINIMAPBOX] = MeshBuilder::GenerateQuad("MiniMapBox", Color(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_MINIMAPBOX]->Init();

	meshList[GEO_GRIDCUBE] = MeshBuilder::GenerateCube("GridCube", Color(1, 1, 1), 1);
	meshList[GEO_GRIDCUBE]->Init();
	meshList[GEO_GRIDCUBE]->mode = Mesh::DRAW_LINES;

	meshList[GEO_TERRAIN] = CreateTerrain(GEO_TERRAIN, "Heightmaps//heightmap.raw");
	meshList[GEO_TERRAIN]->Init();

	meshList[GEO_TESTPARTICLE_CYLINDRICAL] = MeshBuilder::GenerateQuad("ParticleA", Color(1, 1, 1), 1);
	meshList[GEO_TESTPARTICLE_CYLINDRICAL]->Init(100000);

	meshList[GEO_TESTPARTICLE_SPHERICAL] = MeshBuilder::GenerateQuad("ParticleB", Color(1, 1, 1), 1);
	meshList[GEO_TESTPARTICLE_SPHERICAL]->Init(100000);

	meshList[GEO_MENU_NEXUS] = MeshBuilder::GenerateOBJ("MenuNexus", "OBJ//nexus.obj");
	meshList[GEO_MENU_NEXUS]->Init(10);

	meshList[GEO_CODEPARTICLE] = MeshBuilder::GenerateQuad("CodeParticle", Color(1, 1, 1), 1);
	meshList[GEO_CODEPARTICLE]->Init(50000);

	meshList[GEO_MENU_UNIT1] = MeshBuilder::GenerateOBJ("MenuUnit1", "OBJ//normalunit.obj");
	meshList[GEO_MENU_UNIT1]->Init(1000);

	meshList[GEO_MENU_UNIT2] = MeshBuilder::GenerateOBJ("MenuUnit2", "OBJ//rangeunit.obj");
	meshList[GEO_MENU_UNIT2]->Init(1000);

	meshList[GEO_MENU_UNIT3] = MeshBuilder::GenerateOBJ("MenuUnit3", "OBJ//tankunit.obj");
	meshList[GEO_MENU_UNIT3]->Init(1000);
	meshList[GEO_UNIT_NORMAL_PLAYER] = MeshBuilder::GenerateOBJ("Normal Unit", "OBJ//normalunit.obj");
	meshList[GEO_UNIT_NORMAL_PLAYER]->Init();

	meshList[GEO_UNIT_RANGE_PLAYER] = MeshBuilder::GenerateOBJ("Ranged Unit", "OBJ//rangeunit.obj");
	meshList[GEO_UNIT_RANGE_PLAYER]->Init();

	meshList[GEO_UNIT_TANK_PLAYER] = MeshBuilder::GenerateOBJ("Tank Unit", "OBJ//tankunit.obj");
	meshList[GEO_UNIT_TANK_PLAYER]->Init();

	meshList[GEO_UNIT_NEXUS_PLAYER] = MeshBuilder::GenerateOBJ("Nexus Unit", "OBJ//nexus.obj");
	meshList[GEO_UNIT_NEXUS_PLAYER]->Init();

	meshList[GEO_UNIT_TOWER_PLAYER] = MeshBuilder::GenerateOBJ("Tower Unit", "OBJ//tower.obj");
	meshList[GEO_UNIT_TOWER_PLAYER]->Init();

	meshList[GEO_UNIT_GENERATOR1_PLAYER] = MeshBuilder::GenerateOBJ("Generator1 Unit", "OBJ//generator1.obj");
	meshList[GEO_UNIT_GENERATOR1_PLAYER]->Init();

	meshList[GEO_UNIT_GENERATOR2_PLAYER] = MeshBuilder::GenerateOBJ("Generator2 Unit", "OBJ//generator2.obj");
	meshList[GEO_UNIT_GENERATOR2_PLAYER]->Init();

	meshList[GEO_LAB_PLAYER] = MeshBuilder::GenerateOBJ("Lab Unit", "OBJ//lab.obj");
	meshList[GEO_LAB_PLAYER]->Init();

	meshList[GEO_UNIT_WALL_PLAYER] = MeshBuilder::GenerateOBJ("Wall Unit", "OBJ//wall.obj");
	meshList[GEO_UNIT_WALL_PLAYER]->Init();

	meshList[GEO_PROJECTILE_PLAYER] = MeshBuilder::GenerateOBJ("Projectile Unit", "OBJ//projectile.obj");
	meshList[GEO_PROJECTILE_PLAYER]->Init();

	meshList[GEO_PROJECTILE_MELEE_PLAYER] = MeshBuilder::GenerateCube("Projectile Melee Unit", Color(1, 0, 0));
	meshList[GEO_PROJECTILE_MELEE_PLAYER]->Init();

	// Enemy Geometry with Enemy Texture

	meshList[GEO_UNIT_NORMAL_ENEMY] = MeshBuilder::GenerateOBJ("Normal Unit", "OBJ//normalunit.obj");
	meshList[GEO_UNIT_NORMAL_ENEMY]->Init();

	meshList[GEO_UNIT_RANGE_ENEMY] = MeshBuilder::GenerateOBJ("Ranged Unit", "OBJ//rangeunit.obj");
	meshList[GEO_UNIT_RANGE_ENEMY]->Init();

	meshList[GEO_UNIT_TANK_ENEMY] = MeshBuilder::GenerateOBJ("Tank Unit", "OBJ//tankunit.obj");
	meshList[GEO_UNIT_TANK_ENEMY]->Init();

	meshList[GEO_UNIT_NEXUS_ENEMY] = MeshBuilder::GenerateOBJ("Nexus Unit", "OBJ//nexus.obj");
	meshList[GEO_UNIT_NEXUS_ENEMY]->Init();

	meshList[GEO_UNIT_TOWER_ENEMY] = MeshBuilder::GenerateOBJ("Tower Unit", "OBJ//tower.obj");
	meshList[GEO_UNIT_TOWER_ENEMY]->Init();

	meshList[GEO_UNIT_GENERATOR1_ENEMY] = MeshBuilder::GenerateOBJ("Generator1 Unit", "OBJ//generator1.obj");
	meshList[GEO_UNIT_GENERATOR1_ENEMY]->Init();

	meshList[GEO_UNIT_GENERATOR2_ENEMY] = MeshBuilder::GenerateOBJ("Generator2 Unit", "OBJ//generator2.obj");
	meshList[GEO_UNIT_GENERATOR2_ENEMY]->Init();

	meshList[GEO_UNIT_WALL_ENEMY] = MeshBuilder::GenerateOBJ("Wall Unit", "OBJ//wall.obj");
	meshList[GEO_UNIT_WALL_ENEMY]->Init();

	meshList[GEO_LAB_ENEMY] = MeshBuilder::GenerateOBJ("Lab Unit", "OBJ//lab.obj");
	meshList[GEO_LAB_ENEMY]->Init();

	meshList[GEO_PROJECTILE_ENEMY] = MeshBuilder::GenerateOBJ("Projectile Unit", "OBJ//projectile.obj");
	meshList[GEO_PROJECTILE_ENEMY]->Init();

	meshList[GEO_INRANGE_WALL_PLAYER] = MeshBuilder::GenerateOBJ("Inrange gen1", "OBJ//wall.obj");
	meshList[GEO_INRANGE_WALL_PLAYER]->Init();

	meshList[GEO_INRANGE_GENERATOR1_PLAYER] = MeshBuilder::GenerateOBJ("Inrange gen2", "OBJ//generator1.obj");
	meshList[GEO_INRANGE_GENERATOR1_PLAYER]->Init();

	meshList[GEO_INRANGE_GENERATOR2_PLAYER] = MeshBuilder::GenerateOBJ("Inrange wall", "OBJ//generator2.obj");
	meshList[GEO_INRANGE_GENERATOR2_PLAYER]->Init();

	meshList[GEO_INRANGE_TOWER_PLAYER] = MeshBuilder::GenerateOBJ("Inrange wall", "OBJ//tower.obj");
	meshList[GEO_INRANGE_TOWER_PLAYER]->Init();
	
	meshList[GEO_PROJECTILE_MELEE_ENEMY] = MeshBuilder::GenerateCube("Projectile Melee Unit", Color(0, 0, 1));
	meshList[GEO_PROJECTILE_MELEE_ENEMY]->Init();

	meshList[GEO_PLAYERPARTICLE] = MeshBuilder::GenerateQuad("Playerparticle", Color(1, 1, 1), 1);
	meshList[GEO_PLAYERPARTICLE]->Init(10000);

	meshList[GEO_ENEMYPARTICLE] = MeshBuilder::GenerateQuad("Enemyparticle", Color(1, 1, 1), 1);
	meshList[GEO_ENEMYPARTICLE]->Init(10000);

	for (int i = 0; i < NUM_MESH; i++)
	{
		if (meshList[i] == NULL)
		{
			std::cout << "Mesh ID: " << i << " not initialised! This may cause errors during runtime!" << std::endl;
			isfilled = false;
		}
	}

	assert(isfilled == true && "Some meshes have not been initialised! Review the command window for more information.");
}

Mesh* MeshManager::CreateTerrain(GEO_TYPE type, const char* path)
{
	std::vector<unsigned char> m_heightMap;
	Mesh* terrain = MeshBuilder::GenerateTerrain("Terrain", path, m_heightMap);
	m_terrainList.insert({ terrain, m_heightMap });
	return terrain;
}

void MeshManager::Update(float dt)
{
	for (auto anim : animList)
	{
		anim.second.Update(dt);
	}
}

MeshManager::~MeshManager()
{
	for (int i = 0; i < NUM_MESH; ++i)
	{
		if (meshList[i])
			delete meshList[i];
	}
}