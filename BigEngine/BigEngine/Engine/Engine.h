#pragma once
#include <string>
namespace Big
{
	class Window;
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

		const std::string logPath = "./logs/";
		const std::string engineLog = "Engine.txt";

	};
}

