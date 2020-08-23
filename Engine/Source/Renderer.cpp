#include "Renderer.h"
#include <assert.h>
#include "Application.h"
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

void Renderer::addMaterial(Material* mat, Shader* shader)
{
	assert(mat != nullptr, "ERROR: TRYING TO REGISTER A NULLPTR AS A MATERIAL!");

	materialManager.push_back(mat);

	if (shader != nullptr)
	{
		shaderManager.push_back(shader);
		shader->InitShader();
	}

	MaterialtoShader.insert({ mat, shader });
}

void Renderer::assignMaterialtoMesh(Mesh* mesh, Material* material)
{
	assert(mesh != nullptr, "ERROR: TRYING TO ASSIGN A MATERIAL TO A NULLPTR!");

	MeshtoMaterial[mesh] = material;
}

unsigned Renderer::addFont(std::string filepath)
{
	unsigned id;
	id = LoadTGA(filepath.c_str());
	return id;
}

Mesh* Renderer::getMesh(GEO_TYPE type)
{
	return meshManager->meshList[type];
}

Material* Renderer::getMaterial(Mesh* mesh)
{
	return MeshtoMaterial[mesh];
}

Material* Renderer::getMaterial(GEO_TYPE type)
{
	return MeshtoMaterial[getMesh(type)];
}

void Renderer::Init()
{
	addMaterial(new Material, new Shader("Shader///basic.vs", "Shader//basic.fs"));
	meshManager = new MeshManager;
	defaultMaterial = materialManager[0];
	defaultShader = shaderManager[0];

	//Add a post processing shader here if you want
	postProcessingShader = nullptr;
	//Initialise the screenquad
	screenQuad = new ScreenQuad;
	screenQuad->Init();
	//Initialise the textmesh
	TextMesh = MeshBuilder::GenerateText("Text", 16, 16);
	TextMesh->Init();
	//Initialise all the fonts
	Consolas = addFont("Fonts//Consolas.tga");
	//Initialise the textmesh shader
	textshader = new TextShader;
	textshader->InitShader();
	for (auto mesh : meshManager->meshList)
	{
		MeshtoMaterial.insert({ mesh, nullptr });
	}

	//Initialising pipeline modules
	lightingManager.InitLights(shaderManager);

	/*Initialise all your shaders here*/
	Shader* test = new Shader("Shader//test.vs", "Shader//test.fs");
	shaderManager.push_back(test);

	Shader* billboard_Cylindrical = new Shader("Shader//cylindricalbillboard.vs", "Shader//cylindricalbillboard.fs");
	shaderManager.push_back(billboard_Cylindrical);

	Shader* billboard_Spherical = new Shader("Shader//sphericalbillboard.vs", "Shader//sphericalbillboard.fs");
	shaderManager.push_back(billboard_Spherical);

	/*Add your materials*/
	Material* boxmat = new Material();
	boxmat->kColor = glm::vec3(0.1f, 1.f, 1.f);
	boxmat->AssignTexture("Images//crate.tga");
	boxmat->AssignTexture("Images//grass.tga");
	materialManager.push_back(boxmat);

	Material* grass = new Material();
	grass->AssignTexture("Images//grass.tga");
	grass->kSpecular = glm::vec3(0, 0, 0);
	grass->kShininess = 0.f;
	materialManager.push_back(grass);

	Material* testParticleA = new Material();
	testParticleA->AssignTexture("Images//crate.tga");
	//testParticleA->AssignTexture("Images//grass.tga");
	materialManager.push_back(testParticleA);

	Material* testParticleB = new Material();
	testParticleB->AssignTexture("Images//crate.tga");
	//testParticleB->AssignTexture("Images//grass.tga");
	materialManager.push_back(testParticleB);

	//Material* playerMaterial = new Material();
	//playerMaterial->kColor = glm::vec3(1.f, 1.f, 1.f);
	//playerMaterial->AssignTexture("Images//player.tga");
	//materialManager.push_back(playerMaterial);

	/*Assign your material their shaders here*/
	addMaterial(boxmat/*, test*/);
	addMaterial(grass);
	//addMaterial(playerMaterial);
	addMaterial(testParticleA, billboard_Cylindrical);
	addMaterial(testParticleB, billboard_Spherical);

	/*Assign your meshes their materials here*/
	//assignMaterialtoMesh(meshManager->meshList[GEO_CUBE], boxmat);
	assignMaterialtoMesh(meshManager->meshList[GEO_TERRAIN], grass);
	assignMaterialtoMesh(meshManager->meshList[GEO_TESTPARTICLE_CYLINDRICAL], testParticleA);
	assignMaterialtoMesh(meshManager->meshList[GEO_TESTPARTICLE_SPHERICAL], testParticleB);

	/*Assignment of uniform blocks*/
	for (auto shader : shaderManager)
	{
		unsigned uniformblockMatrice = shader->getUniformBlock("MatricesBlock");
		shader->bindUniformBlock(uniformblockMatrice, 0);
	}

	glGenBuffers(1, &MatriceUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, MatriceUBO);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, MatriceUBO, 0, 2 * sizeof(glm::mat4));
}

void Renderer::Update(float dt)
{
	for (auto mesh : meshManager->meshList)
	{
		//Clears all dynamic transform matrices
		mesh->DynamicTransformMatrices.clear();
		mesh->DynamicTransformMatrices.shrink_to_fit();
	}
	meshManager->Update(dt);
}

void Renderer::Render(Camera& camera, bool useCameraShader)
{
	//Buffer all your pipeline modules here

	lightingManager.BufferLights();

	if (useCameraShader)
	{
		camera.FBO->BindForWriting();

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEPTH_BUFFER);

		glBindBuffer(GL_UNIFORM_BUFFER, MatriceUBO);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(camera.getProjectionMatrix()));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(camera.getViewMatrix()));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		if (!camera.getPostProcessingShader())
		{
			std::cout << "Camera has no shader attached!" << std::endl;
			return;
		}

		for (auto mesh : meshManager->meshList)
		{
			camera.getPostProcessingShader()->UseShader();
			camera.getPostProcessingShader()->UpdateShader(nullptr);
			mesh->Render();
		}
	}
	else
	{
		camera.FBO->BindForWriting();

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEPTH_BUFFER);

		glBindBuffer(GL_UNIFORM_BUFFER, MatriceUBO);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(camera.getProjectionMatrix()));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(camera.getViewMatrix()));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		lightingManager.BufferLights();

		for (auto mesh : meshManager->meshList)
		{
			if (mesh->DynamicTransformMatrices.size() + mesh->StaticTransformMatrices.size() <= 0)
			{
				continue;
			}
			Shader* shader;
			Material* material;

			material = MeshtoMaterial[mesh];
			if (material == nullptr)
			{
				material = defaultMaterial;
				shader = defaultShader;
			}
			else
			{
				shader = MaterialtoShader[material];
				if (shader == nullptr)
				{
					shader = defaultShader;
				}
			}
			shader->UseShader();
			shader->UpdateShader(material);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			mesh->Render();

			for (int i = 0; i < material->numTexture; i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	camera.UpdateAssignedTextures();

	if (camera.type == CAMERA_TYPE::CAMERA_MAIN)
	{
		screenQuad->screenTexture = camera.FBO->GetFrame();
	}
}

void Renderer::RenderCanvas()
{
	if (Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	float aspectRatio = (float)Application::GetWindowWidth() / (float)Application::GetWindowHeight();
	float shorterside = (float)((Application::GetWindowHeight() < Application::GetWindowWidth()) ? Application::GetWindowHeight() : Application::GetWindowWidth());

	screenQuad->defaultScreenShader->UseShader();
	for (auto& canvasimage : CanvasImage)
	{
		glm::mat4 model(1.f);
		model = glm::scale(model, glm::vec3(shorterside * 0.5f, shorterside * 0.5f, 1.f));
		model = model * canvasimage.first;

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, canvasimage.second);
		screenQuad->defaultScreenShader->UpdateShader(model);
		screenQuad->RenderIndividually();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glDisable(GL_DEPTH_TEST);
	textshader->UseShader();
	for (auto& canvastext : CanvasText)
	{
		glm::mat4 model(1.f);
		model = glm::scale(model, glm::vec3(shorterside * 0.35f, shorterside * 0.35f, 1.f));
		model = model * canvastext.first;
		textshader->UpdateShaderTexture(Consolas);
		textshader->UpdateShader(model);
		for (unsigned i = 0; i < canvastext.second.length(); ++i)
		{
			glm::mat4 characterspacing(1.f);
			characterspacing = characterspacing * model;
			characterspacing = glm::translate(characterspacing , glm::vec3(i * 0.5f, 0, 0));
			textshader->UpdateShader(characterspacing);
			TextMesh->RenderIndividually((unsigned)canvastext.second[i] * 6, 6);
		}
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	glEnable(GL_DEPTH_TEST);

	CanvasImage.clear();
	CanvasImage.shrink_to_fit();
	CanvasText.clear();
	CanvasText.shrink_to_fit();
}


void Renderer::RenderScreenQuad()
{
	glDisable(GL_DEPTH_TEST);
	float aspectRatio = (float)Application::GetWindowWidth() / (float)Application::GetWindowHeight();
	float shorterside = (float)((Application::GetWindowHeight() < Application::GetWindowWidth()) ? Application::GetWindowHeight() : Application::GetWindowWidth());
	glViewport(0, 0, Application::GetWindowWidth(), Application::GetWindowHeight());

	glm::mat4 proj;
	glm::mat4 view;

	proj = glm::ortho((float)-Application::GetWindowWidth() * 0.5f, (float)Application::GetWindowWidth() * 0.5f, (float)-Application::GetWindowHeight() * 0.5f, (float)Application::GetWindowHeight() * 0.5f, -1.f, 1.f);
	view = glm::mat4(1.f);

	glBindBuffer(GL_UNIFORM_BUFFER, MatriceUBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(proj));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glDisable(GL_DEPTH_TEST);

	/*Code stink, SP3 rush. Organise for next Banbutech version thanks*/
	//As much as I hate this, the post processing shader will be as ugly as the ACOMG one
	//So if anyone decides to do one, best of luck :P
	//Also change post processing shader to same type thanks
	if (postProcessingShader)
	{
		postProcessingShader->UseShader();
	}
	else
	{
		screenQuad->defaultScreenShader->UseShader();
	}
	/*Brute force, find a more elegant solution*/
	glm::mat4 model(1.f);
	model = glm::translate(model, glm::vec3(0, 0, 0));
	model = glm::scale(model, glm::vec3(0.5f * shorterside, 0.5f * shorterside, 1.f));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, screenQuad->screenTexture);
	screenQuad->defaultScreenShader->UpdateShader(model);
	screenQuad->RenderIndividually();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//I want to die, I am never using school classes again LOL
	RenderCanvas();
	glEnable(GL_DEPTH_TEST);
}

void Renderer::BufferStaticModels()
{
	for (auto mesh : meshManager->meshList)
	{
		mesh->BufferStaticModels();
	}
}

std::vector<unsigned char> Renderer::getHeightMap(Mesh* terrain)
{
	return meshManager->m_terrainList.at(terrain);
}
