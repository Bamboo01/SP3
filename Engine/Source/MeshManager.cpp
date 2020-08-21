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

	meshList[GEO_GRIDCUBE] = MeshBuilder::GenerateCube("GridCube", Color(1, 1, 1), 1);
	meshList[GEO_GRIDCUBE]->Init();
	meshList[GEO_GRIDCUBE]->mode = Mesh::DRAW_LINES;

	for (int i = 0; i < NUM_MESH; i++)
	{
		if (meshList[i] == NULL)
		{
			std::cout << "Mesh ID: " << i << " not initialised!" << std::endl;
			isfilled = false;
		}
	}

	assert(isfilled == true && "Some meshes have not been initialised! Review the command window for more information.");
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