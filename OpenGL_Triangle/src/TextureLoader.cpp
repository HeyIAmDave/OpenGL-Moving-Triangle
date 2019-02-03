#include "TextureLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

TextureLoader::TextureLoader()
{ }

Texture & TextureLoader::Load(const std::string & filePath)
{
	if (m_textures.find(filePath) == m_textures.end())
	{
		int w, h;
		unsigned char* data = stbi_load(("./data/" + filePath).c_str(), &w, &h, 0, 4);
		if (data == NULL)
			printf("Error: failed to load texture: %s\n", filePath.c_str());

		std::shared_ptr<Texture> texture = std::make_shared<Texture>();

		texture->Init(data, w, h);
		stbi_image_free(data);

		m_textures[filePath] = texture;
	}

	return *m_textures[filePath];
}

void TextureLoader::CleanUp()
{
	for (auto& texture : m_textures)
		texture.second->CleanUp();
}