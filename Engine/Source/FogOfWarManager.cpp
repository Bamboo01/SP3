#include "FogOfWarManager.h"

FogOfWarManager::FogOfWarManager()
{
}

FogOfWarManager::~FogOfWarManager()
{
}

void FogOfWarManager::InitManager(std::vector<Shader*> shaders)
{
	/*Assignment of uniform blocks*/
	for (auto shader : shaders)
	{
		unsigned uniformblockLight = shader->getUniformBlock("FogOfWarBlock");
		shader->bindUniformBlock(uniformblockLight, 2);
	}

	glGenBuffers(1, &ManagerUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, ManagerUBO);
	glBufferData(GL_UNIFORM_BUFFER, (MAX_UNITS * sizeof(glm::vec4)) + sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, 2, ManagerUBO, 0, (MAX_UNITS * sizeof(glm::vec4)) + sizeof(glm::vec4));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void FogOfWarManager::BufferManager()
{
	numUnits = positions.size();
	glBindBuffer(GL_UNIFORM_BUFFER, ManagerUBO);
	glBufferData(GL_UNIFORM_BUFFER, (MAX_UNITS * sizeof(glm::vec4)) + sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
	if (positions.size() > 0)
	{
		glBufferSubData(GL_UNIFORM_BUFFER, 0, numUnits * sizeof(glm::vec4), &positions[0]);
	}
	glBufferSubData(GL_UNIFORM_BUFFER, MAX_UNITS * sizeof(glm::vec4)	, sizeof(glm::vec4)				, glm::value_ptr(glm::vec4(numUnits, 0, 0, 0)));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	positions.clear();
	positions.shrink_to_fit();
}
