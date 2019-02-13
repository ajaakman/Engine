#include "Window.h"
#include "Utililites/Errors.h"



Engine::Window::Window()
{
}


Engine::Window::~Window()
{
	SDL_DestroyWindow(m_pWindow);
}

int Engine::Window::Init(std::string windowName, int width, int height, unsigned int currentFlags)
{
	Uint32 flags = SDL_WINDOW_OPENGL;

	if (currentFlags & HIDDEN)
		flags |= SDL_WINDOW_HIDDEN;
	if (currentFlags & FULLSCREEN)
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (currentFlags & BORDERLESS)
		flags |= SDL_WINDOW_BORDERLESS;

	m_pWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

	if (m_pWindow == nullptr)
	{
		FatalError("SDL Window could not be created!");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(m_pWindow);

	if (glContext == nullptr)
	{
		FatalError("SDL _GL context could not be created!");
	}
	// glewInit() needs to be called after a valid GLContext is set.
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		FatalError("Could not initialize GLEW!");
	}

	SDL_GL_SetSwapInterval(0); // VSync

	GL(glClearColor(0.9f, 0.9f, 0.9f, 1.0f));

	return 0;
}

void Engine::Window::SwapBuffer()
{
	SDL_GL_SwapWindow(m_pWindow);
}