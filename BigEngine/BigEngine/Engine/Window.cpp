#include "Window.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "../Files/LogHandler.h"
#include "../Files/LogFile.h"


Big::Window::Window()
{
}


Big::Window::~Window()
{
}

bool Big::Window::InitializeRenderSystem()
{
	if (glfwInit())
	{
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		return true;
	}
	LogHandler::DoLog("Failed to initialize OpenGL.", LogFile::LogType::Error);

	return false;
}

void Big::Window::DeInitializeRenderSystem()
{
	glfwTerminate();
}

bool Big::Window::Create(Settings windowSettings)
{
	if (!glfwInit())
	{
		LogHandler::DoLog("Failed to create window :(((", LogFile::LogType::Error);
		return false;
	}

	glWindow = glfwCreateWindow(windowSettings.width, windowSettings.heigth, windowSettings.title.c_str(), nullptr, nullptr);
	if (!glWindow)
	{
		return false;
	}
	glfwMakeContextCurrent(glWindow);
	glewExperimental = GLEW_OK;
	GLenum error = glewInit();

	if (error != GLEW_OK)
	{
		LogHandler::DoLog( (const char*) glewGetErrorString(error), LogFile::LogType::Error);
		return false;
	}

	glClearColor(windowSettings.Background[0], windowSettings.Background[1], windowSettings.Background[2], windowSettings.Background[3]);

	return true;

}

void Big::Window::Destroy()
{
	if (glWindow)
	{
		glfwDestroyWindow(glWindow);
		glWindow = nullptr;
	}
}

bool Big::Window::Closing()
{
	return glfwWindowShouldClose(glWindow);
}

void Big::Window::BeginRender()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Big::Window::EndRender()
{
	glfwSwapBuffers(glWindow);
}

Big::Window::Settings::Settings(const Settings& copySettings)
{
	width = copySettings.width;
	heigth = copySettings.heigth;
	title = copySettings.title;
	Background = copySettings.Background;
}

Big::Window::Settings::Settings()
{

}
