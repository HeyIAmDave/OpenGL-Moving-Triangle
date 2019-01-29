#include "Model.h"

Model::Model()
	: m_vao(0), m_elementCount(0), m_attribCount(0), m_initialized(false)
{ }

void Model::Init(const Mesh & mesh)
{
	if (m_initialized)
		CleanUp();

	m_elementCount = mesh.indices.size();

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(NUM_BUFFERS, m_buffers);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh.vertices.size(), mesh.vertices.data(), GL_STATIC_DRAW);

	AddAttribute(3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	AddAttribute(2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	AddAttribute(3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[ELEMENT_BUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh.indices.size(), mesh.indices.data(), GL_STATIC_DRAW);

	m_initialized = true;
}

void Model::Render()
{
	if (!m_initialized)
		return;

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[ELEMENT_BUFFER]);

	glDrawElements(GL_TRIANGLES, m_elementCount, GL_UNSIGNED_INT, 0);
}

void Model::CleanUp()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(NUM_BUFFERS, m_buffers);
	m_elementCount = 0;
	m_attribCount = 0;
	m_initialized = false;
}

void Model::AddAttribute(GLuint size, GLenum type, GLsizei stride, const void* pointer, GLboolean normalize)
{
	glEnableVertexAttribArray(m_attribCount);
	glVertexAttribPointer(m_attribCount++, size, type, normalize, stride, pointer);
}