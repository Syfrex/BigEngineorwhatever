#pragma once
#include <string>
namespace Big
{
	class ShaderProgram
	{
	public:
		ShaderProgram();
		~ShaderProgram();
		enum ShaderType
		{
			VERTEX,
			FRAGMENT
		};
		bool Create();
		void Destroy();
		void Use();
		bool LoadShader(const std::string& uri, ShaderType shadertype);
	private:
		unsigned int Handle;
		bool CheckShaderError(unsigned int shader);
		bool CheckProgramError();
	};
}

