#pragma once
#include "Shader.h"

#include <unordered_map>
#include <memory>

struct ShaderSource
{
	std::string vertexShader;
	std::string fragmentShader;
};

class ShaderLoader
{
	using ShaderMap = std::unordered_map<std::string, std::shared_ptr<Shader>>;

public:
	ShaderLoader();

	Shader& Load(const std::string& filePath);

	void CleanUp();
private:
	ShaderMap m_shaders;

private:
	ShaderSource LoadShaderFile(const std::string& filePath);
};