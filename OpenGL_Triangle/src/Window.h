#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
	Window();

	void Init(const std::string& title, int width, int height);

	void Clear(GLenum mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	void Update();

	void CleanUp();

	inline bool IsCloseRequested() const { return !s_isRunning; }
	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
	inline float GetAspect() const { return (float)m_width / m_height; }

	inline static Window& Get() { return *s_instance; }

private:
	GLFWwindow* m_window;
	static bool s_isRunning;
	int m_width, m_height;
	static Window* s_instance;

private:
	static void GLFWErrorCallback(int error, const char* desc);
};