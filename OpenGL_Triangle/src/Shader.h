#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader
{
public:
	Shader();

	void Init(const std::string& vsrc, const std::string& fsrc);

	void Bind() const;
	void Unbind() const;

	void CleanUp();
// Uniform loading
public:
	void LoadUniform(const std::string& name, int value);
	void LoadUniform(const std::string& name, const glm::mat4& value);

private:
	GLuint m_programID;
	bool m_initialized;

	GLuint CreateShader(GLenum type, const std::string& src);
};