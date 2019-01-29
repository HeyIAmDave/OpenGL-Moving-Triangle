#pragma once
#include "Mesh.h"

#include <glad/glad.h>

class Model
{
public:
	Model();

	void Init(const Mesh& mesh);
	void Render();
	void CleanUp();

private:
	enum Buffer
	{
		VERTEX_BUFFER,
		ELEMENT_BUFFER,

		NUM_BUFFERS
	};
private:
	GLuint m_vao, m_elementCount, m_attribCount;
	GLuint m_buffers[NUM_BUFFERS];
	bool m_initialized;

private:
	void AddAttribute(GLuint size, GLenum type, GLsizei stride, const void* pointer, GLboolean normalize = GL_FALSE);
};