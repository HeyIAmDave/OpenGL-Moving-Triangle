#pragma once
#include "ShaderLoader.h"
#include "TextureLoader.h"
#include "ModelLoader.h"

class Loader
{
public:
	Loader();

	Shader& LoadShader(const std::string& filePath);
	Texture& LoadTexture(const std::string& filePath);
	Model& LoadModel(const std::string& filePath);

	void CleanUp();

	inline static Loader& Get() { return *s_instance; }
private:
	static Loader* s_instance;

	ShaderLoader m_shaderLoader;
	TextureLoader m_textureLoader;
	ModelLoader m_modelLoader;
};