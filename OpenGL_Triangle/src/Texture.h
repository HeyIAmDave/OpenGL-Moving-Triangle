#pragma once
#include <glad/glad.h>

class Texture
{
public:
	Texture();

	void Init(unsigned char* data, int w, int h);

	void Bind() const;
	void Unbind() const;

	void CleanUp();
private:
	GLuint m_textureID;
	bool m_initialized;
};