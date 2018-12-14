#include "ShaderProgram.h"
#include "../Files/LogHandler.h"
#include "../Helpers/FileHelper.h"
#include "GL/glew.h"
#include <assert.h>


Big::ShaderProgram::ShaderProgram()
{
}


Big::ShaderProgram::~ShaderProgram()
{
}

bool Big::ShaderProgram::Create()
{
	Handle = glCreateProgram();
	return true;
}

void Big::ShaderProgram::Destroy()
{
	glDeleteProgram(Handle);
	Handle = 0;
}

void Big::ShaderProgram::Use()
{
	assert(Handle > 0);
	glUseProgram(Handle);
}

bool Big::ShaderProgram::LoadShader(const std::string& uri, ShaderType shadertype)
{
	bool Success = true;
	std::string source;
	GLuint shaderHandle = 0;
	if (FileHelper::GetFileContent(uri, source))
	{
		switch (shadertype)
		{
		case ShaderType::VERTEX:
			shaderHandle = glCreateShader(GL_VERTEX_SHADER);
			break;
		case ShaderType::FRAGMENT:
			shaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		default:
			return false;
		}
		const GLchar* glSource = source.c_str();
		glShaderSource(shaderHandle, 1, &glSource, nullptr);
		glCompileShader(shaderHandle);
		Success &= CheckShaderError(Handle);
		if (Success)
		{
			glAttachShader(Handle, shaderHandle);
			glLinkProgram(Handle);
			Success &= CheckProgramError();
		}
		
	}
	
	glDeleteShader(shaderHandle);
	return Success;
}

bool Big::ShaderProgram::CheckShaderError(unsigned int shader)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		GLint messageLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &messageLength);
		std::string errorMessage(messageLength, ' ');
		glGetShaderInfoLog(shader, messageLength, &messageLength, &errorMessage[0]);
		LogHandler::DoLog("Shader failed to link shader " + errorMessage, LogFile::LogType::Error);
		return false;
	}
	return true;
}

bool Big::ShaderProgram::CheckProgramError()
{
	GLint status;
	glGetProgramiv(Handle, GL_LINK_STATUS, &status);
	if (!status)
	{
		GLint messageLength = 0;
		glGetProgramiv(Handle, GL_INFO_LOG_LENGTH, &messageLength);
		std::string errorMessage(messageLength, ' ');
		glGetProgramInfoLog(Handle, messageLength, &messageLength, &errorMessage[0]);
		LogHandler::DoLog("Shader program failed to link shader " + errorMessage, LogFile::LogType::Error);
		return false;
	}
	return true;
}
