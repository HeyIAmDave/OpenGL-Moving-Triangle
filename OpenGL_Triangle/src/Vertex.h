#pragma once
#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 color;

	Vertex(const glm::vec3& _pos, const glm::vec2& _texCoord, const glm::vec3& _color)
	{
		pos = _pos;
		texCoord = _texCoord;
		color = _color;
	}
};