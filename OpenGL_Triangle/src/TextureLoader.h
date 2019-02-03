#pragma once
#include "Texture.h"

#include <memory>
#include <unordered_map>

class TextureLoader
{
	using TextureMap = std::unordered_map<std::string, std::shared_ptr<Texture>>;

public:
	TextureLoader();

	Texture& Load(const std::string& filePath);

	void CleanUp();
private:
	TextureMap m_textures;
};