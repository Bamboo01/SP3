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

Mesh* Renderer::getMesh(GEO_TYPE type)
{
	return meshManager->meshList[type];
}

void Renderer::Init()
{
	addMaterial(new Material, new Shader("Shader///basic.vs", "Shader//basic.fs"));
	meshManager = new MeshManager;
	defaultMaterial = materialManager[0];
	defaultShader = shaderManager[0];

	//Add a post processing shader here if you want
	postProcessingShader = nullptr;

	screenQuad = new ScreenQuad;
	screenQuad->Init();

	for (auto mesh : meshManager->meshList)
	{
		MeshtoMaterial.insert({ mesh, nullptr });
	}

	lightingManager.InitLights(shaderManager);

	/*Initialise all your shaders here*/

	/*Add your materials*/
	Material* boxmat = new Material();
	boxmat->kColor = glm::vec3(0.1f, 1.f, 1.f);
	boxmat->AssignTexture("Images//crate.tga");
	boxmat->AssignTexture("Images//grass.tga");
	materialManager.push_back(boxmat);

	Material* grid = new Material();
	grid->kColor = glm::vec3(1.0f, 1.f, 1.f);
	grid->AssignTexture("Images//grid.tga");
	materialManager.push_back(grid);
	/*Assign your material their shaders here*/
	addMaterial(boxmat);
	addMaterial(grid);
	/*Assign your meshes their materials here*/
	assignMaterialtoMesh(meshManager->meshList[GEO_CUBE], boxmat);
	assignMaterialtoMesh(meshManager->meshList[GEO_GRID], grid);

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

		lightingManager.BufferLights();

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


void Renderer::RenderScreenQuad()
{
	float longerside = (Application::GetWindowHeight() > Application::GetWindowHeight()) ? Application::GetWindowHeight() : Application::GetWindowWidth();
	float offsetx = (Application::GetWindowWidth() - longerside) * 0.5f;
	float offsety = (Application::GetWindowHeight() - longerside) * 0.5f;


	glViewport(offsetx, offsety, longerside, longerside);


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glDisable(GL_DEPTH_TEST);

	/*Code stink, SP3 rush. Organise for next Banbutech version thanks*/
	if (postProcessingShader)
	{
		postProcessingShader->UseShader();
	}
	else
	{
		screenQuad->defaultScreenShader->UseShader();
	}
	/*Brute force, find a more elegant solution*/

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, screenQuad->screenTexture);
	screenQuad->Render();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnable(GL_DEPTH_TEST);
}

void Renderer::BufferStaticModels()
{
	for (auto mesh : meshManager->meshList)
	{
		mesh->BufferStaticModels();
	}
}
