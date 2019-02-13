#pragma once

#include <string>

#include "GL/glew.h"
#include "SDL/SDL.h"

namespace Engine{

	enum WindowFlags { HIDDEN = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class Window
	{
	public:
		Window();
		~Window();

		int Init(std::string windowName, int width, int height, unsigned int currentFlags);

		void SwapBuffer();

		int GetScreenWidth() { return m_nScreenWidth; }
		int GetScreenHeight() { return m_nScreenHeight; }

	private:

		SDL_Window* m_pWindow;
		int m_nScreenWidth;
		int m_nScreenHeight;
	};

}