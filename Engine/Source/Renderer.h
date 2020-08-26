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
#include "TextShader.h"


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

	//Text Mesh
	Mesh* TextMesh;
	//Text Shader
	TextShader* textshader;
	//Fonts
	unsigned Consolas;

	//Add-ons to the rendering pipeline
	LightingManager lightingManager;

	void addMaterial(Material* mat, Shader* shader = nullptr);
	void assignMaterialtoMesh(Mesh* mesh, Material* material);
	unsigned addFont(std::string filepath);

public:
	Mesh* getMesh(GEO_TYPE type);
	Material* getMaterial(Mesh* mesh);
	Material* getMaterial(GEO_TYPE type);
	Shader* getShader(Material* material);

	void Init();
	void Update(float dt);
	void Render(Camera& camera, bool useCameraShader);
	void RenderCanvas();
	void RenderScreenQuad();
	void BufferStaticModels();
	std::vector<unsigned char> getHeightMap(Mesh* terrain);

	//Canvas stuff
	std::vector <std::pair<glm::mat4, unsigned>> CanvasImage;
	std::vector <std::tuple<glm::mat4, std::string, glm::vec3>> CanvasText;
};

