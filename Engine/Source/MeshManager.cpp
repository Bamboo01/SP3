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
	meshList[GEO_AXES] =  MeshBuilder::GenerateAxes("reference");
	meshList[GEO_AXES]->Init();

	meshList[GEO_CUBE] =  MeshBuilder::GenerateCube("cube", Color(1.f, 1.f, 1.f), 1.f);
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

	meshList[GEO_TESTPARTICLE_CYLINDRICAL] = MeshBuilder::GenerateQuad("ParticleA", Color(1,1,1), 1);
	meshList[GEO_TESTPARTICLE_CYLINDRICAL]->Init(100000);

	meshList[GEO_TESTPARTICLE_SPHERICAL] = MeshBuilder::GenerateQuad("ParticleB", Color(1, 1, 1), 1);
	meshList[GEO_TESTPARTICLE_SPHERICAL]->Init(100000);

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