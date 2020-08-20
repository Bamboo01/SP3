#include "MeshManager.h"
#include "Shader.h"
#include "Material.h"
#include <map>
#include "Camera.h"
#include "Light.h"
#include <glm.hpp>
#include "LightingManager.h"
#include "ScreenQuad.h"
#include <string>


#pragma once

class Renderer
{
private:
	//Mesh, material, shaders
	std::map<Material*, Shader*> MaterialtoShader;
	std::map<Mesh*, Material*> MeshtoMaterial;
	MeshManager* meshManager;
	std::vector<Shader*> shaderManager;
	std::vector<Material*> materialManager;

	//Matrice UBO
	unsigned MatriceUBO;

	//Default Stuff
	Material* defaultMaterial;
	Shader* defaultShader;
	Shader* postProcessingShader;

	//Screen Quad
	ScreenQuad* screenQuad;

	//Add-ons to the rendering pipeline
	LightingManager lightingManager;

	void addMaterial(Material* mat, Shader* shader = nullptr);
	void assignMaterialtoMesh(Mesh* mesh, Material* material);

public:
	Mesh* getMesh(GEO_TYPE type);

	void Init();
	void Update(float dt);
	void Render(Camera& camera, bool useCameraShader);
	void RenderCanvas();
	void RenderScreenQuad();
	void BufferStaticModels();

	//Canvas stuff
	std::vector <std::pair<glm::mat4, unsigned>> CanvasImage;
	std::vector <std::pair<glm::mat4, std::string>> CanvasText;
};

