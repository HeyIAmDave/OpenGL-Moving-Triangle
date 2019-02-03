#include "Framebuffer.h"
#include "Window.h"

Framebuffer::Framebuffer()
	: m_fbo(0), m_vbo(0), m_vao(0), m_initialized(false)
{ }

void Framebuffer::Init()
{
	if (m_initialized)
		return;

	m_colorTexture.Init(NULL, Window::Get().GetWidth(), Window::Get().GetHeight());
	m_depthTexture.Init(NULL, Window::Get().GetWidth(), Window::Get().GetHeight(), GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT);

	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorTexture.GetID(), 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture.GetID(), 0);

	GLenum fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
		printf("Error: failed to create framebuffer!\n");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	m_shader = Loader::Get().LoadShader("shaders/fboShader.glsl");

	CreateScreenQuad();

	m_initialized = true;
}

void Framebuffer::Bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void Framebuffer::Unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Draw()
{
	m_colorTexture.Bind();
	m_shader.Bind();
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	m_shader.Unbind();
	m_colorTexture.Unbind();
}

void Framebuffer::CleanUp()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteFramebuffers(1, &m_fbo);
	m_colorTexture.CleanUp();
	m_depthTexture.CleanUp();

	m_initialized = false;
}

void Framebuffer::CreateScreenQuad()
{
	float vertices[] =
	{
		1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f,

		-1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
	};

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)8);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}