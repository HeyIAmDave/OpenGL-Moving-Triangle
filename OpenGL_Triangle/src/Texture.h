#pragma once
#include <glad/glad.h>

class Texture
{
public:
	Texture();

	void Init(unsigned char* data, int w, int h, GLenum internalFormat = GL_RGBA, GLenum format = GL_RGBA);

	void Bind() const;
	void Unbind() const;

	void CleanUp();

	inline GLuint GetID() const { return m_textureID; }
private:
	GLuint m_textureID;
	bool m_initialized;
};