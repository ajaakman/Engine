#pragma once

#include <string>
#include "GL/glew.h"

#ifdef USING_GLFW		
#include "GLFW/glfw3.h"
#elif USING_SDL
#include "SDL/SDL.h"
#endif

namespace Engine{

	enum WindowFlags { HIDDEN = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class Window
	{
	public:
		Window();
		~Window();

		int Init(std::string windowName, int width, int height, unsigned int currentFlags);

		void SwapBuffer();
		float GetFrameTime();

		void ProcessInput();

		int GetScreenWidth() { return m_nScreenWidth; }
		int GetScreenHeight() { return m_nScreenHeight; }

	private:

#ifdef USING_GLFW		
		GLFWwindow* m_pWindow;
#elif USING_SDL
		SDL_Window* m_pWindow;
#endif
		int m_nScreenWidth;
		int m_nScreenHeight;
	};

}

