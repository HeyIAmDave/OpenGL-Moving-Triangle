#include "Window.h"

bool Window::s_isRunning = false;
Window* Window::s_instance;


Window::Window()
	: m_width(640), m_height(480)
{
	if (s_instance == nullptr)
		s_instance = this;
}

void Window::Init(const std::string & title, int width, int height)
{
	m_width = width;
	m_height = height;

	glfwInit();
	glfwSetErrorCallback(GLFWErrorCallback);

	m_window = glfwCreateWindow(m_width, m_height, title.c_str(), 0, 0);
	glfwMakeContextCurrent(m_window);

	glfwSwapInterval(0);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
		s_isRunning = false;
	});

	glClearColor(0, 0, 0, 1);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	s_isRunning = true;
}

void Window::Clear(GLenum mask)
{
	glClear(mask);
}

void Window::Update()
{
	glfwPollEvents();
	glfwSwapBuffers(m_window);
}

void Window::CleanUp()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Window::GLFWErrorCallback(int error, const char * desc)
{
	printf("GLFW error (%i): %s\n", error, desc);
}