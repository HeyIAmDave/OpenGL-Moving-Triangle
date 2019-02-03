#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

struct Transform
{
	glm::vec3 pos;
	glm::quat rot;
	glm::vec3 scale;

	Transform()
	{
		pos = { 0, 0, 0 };
		rot = glm::quat({ 0, 0, 0 });
		scale = { 1, 1, 1 };
	}

	inline void Rotate(float angle, const glm::vec3& axis)
	{
		rot = glm::rotate(glm::mat4(1.0f), angle, axis);
	}

	inline glm::mat4 CreateModelMatrix() const
	{
		glm::mat4 tMat = glm::translate(glm::mat4(1.0f), pos);
		glm::mat4 rMat = glm::mat4_cast(rot);
		glm::mat4 sMat = glm::scale(glm::mat4(1.0f), scale);

		return tMat * rMat * sMat;
	}
};