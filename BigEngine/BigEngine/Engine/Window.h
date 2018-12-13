#pragma once
#include <string>
#include "../Math/Color.h"
struct GLFWwindow;
namespace Big
{
	class Window
	{
	public:
		Window();
		~Window();

		struct Settings
		{
			Settings();
			Settings(const Settings& copySettings);
			int width;
			int heigth;
			std::string title;
			Color Background;
		};

		static bool InitializeRenderSystem();
		static void DeInitializeRenderSystem();

		bool Create(Settings windowSettings);
		void Destroy();
		bool Closing();
		void BeginRender();
		void EndRender();

	private:
		GLFWwindow* glWindow;
		Settings settings;
	};
}

