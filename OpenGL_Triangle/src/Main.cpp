#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Model.h"
#include "Shader.h"
#include "Texture.h"

static void GLFWErrorCallback(int error, const char* desc)
{
	printf("GLFW error (%i): %s\n", error, desc);
}

std::string LoadTextFile(const std::string& filePath);

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

	void Rotate(float angle, const glm::vec3& axis)
	{
		rot = glm::angleAxis(angle, axis);
	}

	glm::mat4 CreateModelMatrix() const
	{
		glm::mat4 tMat = glm::translate(glm::mat4(1.0f), pos);
		glm::mat4 rMat = glm::mat4_cast(rot);
		glm::mat4 sMat = glm::scale(glm::mat4(1.0f), scale);

		return tMat * rMat * sMat;
	}
};

int main(int argc, char** argv)
{
	glfwInit();
	glfwSetErrorCallback(GLFWErrorCallback);

	GLFWwindow* window = glfwCreateWindow(1280, 720, "OpenGL triangle", 0, 0);
	glfwMakeContextCurrent(window);

	glfwSwapInterval(0);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	static bool isRunning = true;
	glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
		isRunning = false;
	});

	glClearColor(0, 0, 0, 1);

	// Triangle setup
	Mesh mesh;
	mesh.vertices =
	{
		Vertex({-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}),
		Vertex({0.0f, 0.5f, 0.0f}, {0.5f, 1.0f}, {0.0f, 1.0f, 0.0f}),
		Vertex({0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}),
	};

	mesh.indices =
	{
		0, 1, 2
	};

	Model triangle;
	triangle.Init(mesh);

	Shader shader;
	shader.Init(LoadTextFile("shaders/basicShader.vert"), LoadTextFile("shaders/basicShader.frag"));

	Texture texture;
	{
		int w, h;
		unsigned char* data = stbi_load("./data/textures/test.png", &w, &h, 0, 4);
		if (data == NULL)
			printf("Error: failed to load texture!");

		texture.Init(data, w, h);
		stbi_image_free(data);
	}

	// Matrix
	Transform triangleTransform;

	glm::mat4 proj = glm::perspective(glm::radians(100.0f), 1280.0f / 720.0f, 0.01f, 1000.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), { 0, 0, -2 });
	glm::mat4 model = glm::mat4(1.0f);
	
	float change = 0.0f;

	// Delta time
	float LAST_TIME = (float)glfwGetTime();

	while (isRunning)
	{
		float CURRENT_TIME = (float)glfwGetTime();
		float DELTA_TIME = CURRENT_TIME - LAST_TIME;
		LAST_TIME = CURRENT_TIME;

		change += DELTA_TIME;

		triangleTransform.pos.x = glm::sin(change);
		triangleTransform.pos.y = glm::cos(change);

		triangleTransform.Rotate(change, { 0, 0, 1 });
		
		triangleTransform.scale.x = glm::sin(change) + 0.5f;
		triangleTransform.pos.y = glm::cos(change) + 0.5f;
		
		model = triangleTransform.CreateModelMatrix();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		texture.Bind();
		shader.Bind();

		shader.LoadUniform("_proj", proj);
		shader.LoadUniform("_view", view);
		shader.LoadUniform("_model", model);
		shader.LoadUniform("_texture", 0);

		triangle.Render();
		shader.Unbind();
		texture.Unbind();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// Clean Up
	triangle.CleanUp();
	shader.CleanUp();
	texture.CleanUp();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

std::string LoadTextFile(const std::string& filePath)
{
	std::ifstream file("./data/" + filePath);
	if (!file.good())
	{
		printf("Failed to load text file: %s", filePath.c_str());
		return "";
	}

	std::string result;
	file.seekg(0, std::ios::end);
	result.reserve((size_t)file.tellg());
	file.seekg(0, std::ios::beg);

	result.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	return result;
}