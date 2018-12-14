#pragma once
#include <string>
namespace Big
{
	class Window;
	class ShaderProgram;
	class Engine
	{
	public:
		Engine();
		~Engine();

		bool Create();
		void Destroy();
		void Update();
	private:
		Window* window = nullptr;
		ShaderProgram* shaderProgram = nullptr;
		const std::string logPath = "./logs/";
		const std::string engineLog = "Engine.txt";
		const std::string defaultVertexShader = "./data/shaders/default.vert";
		const std::string defaultFragmentShader = "./data/shaders/default.frag";
	};
}

