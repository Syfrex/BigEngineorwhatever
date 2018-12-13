#include "Engine.h"
#include "Window.h"
#include <assert.h>
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "../Files/LogHandler.h"
#include "../Files/LogFile.h"

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
	return window->Create(windowSettings);
}

void Big::Engine::Destroy()
{
	if (window)
	{
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

	const GLchar* vertexShaderSource = 
		"#version 330 core\n" 
		"layout (location = 0) in vec3 pos;"
		"layout (location = 1) in vec3 color;"
		"out vec3 vert_color;"
		"void main()" 
		"{"
		"vert_color = color;"
		"gl_Position = vec4(pos.x, pos.y, pos.z, 1.0f);"
		"}"
		;
	const GLchar* fragmentShaderSource =
		"#version 330 core\n"
		"in vec3 vert_color;"
		"out vec4 frag_color;"
		"void main()"
		"{"
		"frag_color = vec4(vert_color,1.0f);"
		"}"
		;

	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader,1,&vertexShaderSource, nullptr);
	glCompileShader(VertexShader);

	GLint  result;
	GLchar info[512];
	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(VertexShader, sizeof(info), nullptr, info);
		LogHandler::DoLog(info,LogFile::LogType::Error);
	}
	
	GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(FragmentShader);

	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(FragmentShader, sizeof(info), nullptr, info);
		LogHandler::DoLog(info, LogFile::LogType::Error);
	}
	GLuint ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragmentShader);
	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(ShaderProgram, sizeof(info), nullptr, info);
		LogHandler::DoLog(info, LogFile::LogType::Error);
	}
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);

	while (!window->Closing())
	{
		window->BeginRender();

		glUseProgram(ShaderProgram);
		glBindVertexArray(vao);

		glDrawArrays(GL_TRIANGLE_STRIP,0, ((sizeof(Vertices) / sizeof(GLfloat))) /6);

		glBindVertexArray(0);
		window->EndRender();
		//todo dodo, to do do do od dodooddodo doooooooooooooooooooooooo
		glfwPollEvents();

	}
	glDeleteProgram(ShaderProgram);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}
