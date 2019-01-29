#include "Texture.h"

Texture::Texture()
	: m_textureID(0), m_initialized(false)
{ }

void Texture::Init(unsigned char * data, int w, int h)
{
	if (m_initialized)
		return;

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	m_initialized = true;
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::CleanUp()
{
	glDeleteTextures(1, &m_textureID);
	m_initialized = false;
}