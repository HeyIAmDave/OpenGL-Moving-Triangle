#include "Loader.h"

Loader* Loader::s_instance;

Loader::Loader()
{
	if (s_instance == nullptr)
		s_instance = this;
}

Shader & Loader::LoadShader(const std::string & filePath)
{
	return m_shaderLoader.Load(filePath);
}

Texture & Loader::LoadTexture(const std::string & filePath)
{
	return m_textureLoader.Load(filePath);
}

Model & Loader::LoadModel(const std::string & filePath)
{
	return m_modelLoader.Load(filePath);
}

void Loader::CleanUp()
{
	m_shaderLoader.CleanUp();
	m_textureLoader.CleanUp();
	m_modelLoader.CleanUp();
}