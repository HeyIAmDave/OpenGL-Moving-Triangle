#include <stdio.h>

#include "Window.h"
#include "Loader.h"
#include "Model.h"
#include "Transform.h"
#include "Framebuffer.h"

Model CreateTriangle();

int main(int argc, char** argv)
{
	Window window;
	window.Init("Moving triangle", 1280, 720);
	Loader loader;
	Framebuffer fbo;
	fbo.Init();

	Shader shader = loader.LoadShader("shaders/basicShader.glsl");
	Texture texture = loader.LoadTexture("textures/maze.png");

	Model triangle = CreateTriangle();
	Model monkey = loader.LoadModel("models/monkey.obj");

	// Matrix
	Transform triangleTransform;
	Transform monkeyTransform;
	monkeyTransform.pos.x = -2;

	glm::mat4 proj = glm::perspective(glm::radians(100.0f), window.GetAspect(), 0.01f, 1000.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), { 0, -1, -3 });
	glm::mat4 triangleModel = glm::mat4(1.0f);
	glm::mat4 monkeyModel = glm::mat4(1.0f);
	
	float change = 0.0f;

	// Delta time
	float LAST_TIME = (float)glfwGetTime();

	while (!window.IsCloseRequested())
	{
		float CURRENT_TIME = (float)glfwGetTime();
		float DELTA_TIME = CURRENT_TIME - LAST_TIME;
		LAST_TIME = CURRENT_TIME;

		change += DELTA_TIME;

		triangleTransform.pos.x = glm::sin(change) + 2;
		triangleTransform.pos.y = glm::cos(change);

		triangleTransform.Rotate(change, { 0, 0, 1 });
		
		triangleTransform.scale.x = glm::sin(change) + 0.5f;
		triangleTransform.scale.y = glm::cos(change) + 0.5f;

		monkeyTransform.Rotate(change, { 0, 1, 0 });
		
		triangleModel = triangleTransform.CreateModelMatrix();
		monkeyModel = monkeyTransform.CreateModelMatrix();

		glEnable(GL_DEPTH_TEST);
		fbo.Bind();
		window.Clear();

		texture.Bind();
		shader.Bind();

		shader.LoadUniform("_proj", proj);
		shader.LoadUniform("_view", view);
		shader.LoadUniform("_model", triangleModel);
		shader.LoadUniform("_texture", 0);

		glDisable(GL_CULL_FACE);
		triangle.Render();
		glEnable(GL_CULL_FACE);
		shader.Unbind();
		texture.Unbind();

		texture.Bind();
		shader.Bind();

		shader.LoadUniform("_proj", proj);
		shader.LoadUniform("_view", view);
		shader.LoadUniform("_model", monkeyModel);
		shader.LoadUniform("_texture", 0);

		monkey.Render();
		shader.Unbind();
		texture.Unbind();

		glDisable(GL_DEPTH_TEST);
		fbo.Unbind();
		window.Clear(GL_COLOR_BUFFER_BIT);

		fbo.Draw();

		window.Update();
	}

	// Clean Up
	fbo.CleanUp();
	triangle.CleanUp();
	loader.CleanUp();
	window.CleanUp();

	return 0;
}

Model CreateTriangle()
{
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

	return triangle;
}