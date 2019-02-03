#include "ShaderLoader.h"

#include <fstream>
#include <sstream>

ShaderLoader::ShaderLoader()
{ }

Shader & ShaderLoader::Load(const std::string & filePath)
{
	if (m_shaders.find(filePath) == m_shaders.end())
	{
		ShaderSource src = LoadShaderFile(filePath);
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Init(src.vertexShader, src.fragmentShader);

		m_shaders[filePath] = shader;
	}

	return *m_shaders[filePath];
}

void ShaderLoader::CleanUp()
{
	for (auto& shader : m_shaders)
		shader.second->CleanUp();
}

ShaderSource ShaderLoader::LoadShaderFile(const std::string & filePath)
{
	ShaderSource result;
	std::ifstream file("./data/" + filePath);
	if (!file.good())
	{
		printf("Failed to Load shader file: %s\n", filePath.c_str());
		return result;
	}

	std::string line;
	std::string currentShader = "";

	while (std::getline(file, line))
	{
		if (line == "#vertexShader" || line == "#fragmentShader")
		{
			currentShader = line;
			continue;
		}

		if (currentShader == "#vertexShader")
			result.vertexShader += line + "\n";
		else
			result.fragmentShader += line + "\n";
	}

	file.close();
	return result;
}