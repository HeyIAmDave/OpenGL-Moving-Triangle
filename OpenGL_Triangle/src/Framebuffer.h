#pragma once
#include "Loader.h"

#include <glad/glad.h>

class Framebuffer
{
public:
	Framebuffer();
	
	void Init();

	void Bind() const;
	void Unbind() const;

	void Draw();

	void CleanUp();
private:
	GLuint m_fbo, m_vao, m_vbo;
	Texture m_colorTexture, m_depthTexture;
	Shader m_shader;
	bool m_initialized;

private:
	void CreateScreenQuad();
};