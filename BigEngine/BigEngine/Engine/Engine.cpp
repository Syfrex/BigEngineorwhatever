#include "Engine.h"
#include "Window.h"
#include <assert.h>
#include "../Files/LogHandler.h"
#include "../Files/LogFile.h"
#include "ShaderProgram.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

Big::Engine::Engine()
{
}


Big::Engine::~Engine()
{
}

bool Big::Engine::Create()
{
	bool success = true;
	LogHandler* logHandler = LogHandler::CreateInstance(logPath);
	success &= logHandler->CreateLog(engineLog);

	if (!success) { return false; }

	success &= Window::InitializeRenderSystem();
	if (!success) { return false; }

	Window::Settings windowSettings;
	windowSettings.width = 1024;
	windowSettings.heigth = 768;
	windowSettings.title = "Big Engine";
	windowSettings.Background = Color(Color::Magenta);

	assert(window == nullptr);
	window = new Window();

	success &= window->Create(windowSettings);
	if (!success)
	{
		LogHandler::DoLog("Failed to create window", LogFile::LogType::Error);
		return false;
	}
	shaderProgram = new ShaderProgram();
	success &= shaderProgram->Create();
	if (success)
	{
		success &= shaderProgram->LoadShader(defaultVertexShader, ShaderProgram::ShaderType::VERTEX);
		success &= shaderProgram->LoadShader(defaultFragmentShader, ShaderProgram::ShaderType::FRAGMENT);
	}

	return success;
}

void Big::Engine::Destroy()
{
	if (shaderProgram)
	{
		shaderProgram->Destroy();
		delete shaderProgram;
		shaderProgram = nullptr;
	}
	if (window)
	{
		window->Destroy();
		delete window;
		window = nullptr;
	}
	Window::DeInitializeRenderSystem();
	LogHandler::DestroyInstance();
}

void Big::Engine::Update()
{
	GLfloat Vertices[] =
	{
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,

		// 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		// 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		//-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	};
	GLuint vbo;
	glGenBuffers(1,&vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, nullptr);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (GLvoid*) (sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(1);


	while (!window->Closing())
	{
		window->BeginRender();

		shaderProgram->Use();
		glBindVertexArray(vao);

		glDrawArrays(GL_TRIANGLE_STRIP,0, ((sizeof(Vertices) / sizeof(GLfloat))) /6);

		glBindVertexArray(0);
		window->EndRender();
		//todo dodo, to do do do od dodooddodo doooooooooooooooooooooooo
		glfwPollEvents();

	}
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}
