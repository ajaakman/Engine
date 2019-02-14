#include "Window.h"
#include "Utililites/Errors.h"


Engine::Window::Window()
{
}


Engine::Window::~Window()
{
#ifdef USING_GLFW		
	glfwTerminate();
#elif USING_SDL
	SDL_DestroyWindow(m_pWindow);
#endif
}

int Engine::Window::Init(std::string windowName, int width, int height, unsigned int currentFlags)
{
#ifdef USING_GLFW
	if (!glfwInit())
		FatalError("GLFW could not be initialized!");
	/////

	m_pWindow = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

	if (!m_pWindow)
	{
		glfwTerminate();
		FatalError("Window could not be created!");
	}
#elif USING_SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	Uint32 flags = SDL_WINDOW_OPENGL;

	if (currentFlags & HIDDEN)
		flags |= SDL_WINDOW_HIDDEN;
	if (currentFlags & FULLSCREEN)
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (currentFlags & BORDERLESS)
		flags |= SDL_WINDOW_BORDERLESS;

	m_pWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

	if (m_pWindow == nullptr)	
		FatalError("Window could not be created!");
#endif

	
#ifdef USING_GLFW		
	glfwMakeContextCurrent(m_pWindow);
#elif USING_SDL
	SDL_GLContext glContext = SDL_GL_CreateContext(m_pWindow);

	if (glContext == nullptr)
	{
		FatalError("GL context could not be created!");
	}
	// glewInit() needs to be called after a valid GLContext is set.
#endif
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		FatalError("Could not initialize GLEW!");
	}
#ifdef USING_GLFW		
	glfwSwapInterval(1);
#elif USING_SDL
	SDL_GL_SetSwapInterval(0); // VSync
#endif

	GL(glClearColor(0.9f, 0.9f, 0.9f, 1.0f));

	return 0;
}

void Engine::Window::SwapBuffer()
{
#ifdef USING_GLFW		
	glfwSwapBuffers(m_pWindow);
#elif USING_SDL
	SDL_GL_SwapWindow(m_pWindow);	
#endif
}

void Engine::Window::ProcessInput()
{
#ifdef USING_GLFW		
	glfwPollEvents();
#elif USING_SDL
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			m_GameState = GameState::END;
			break;
		case SDL_MOUSEMOTION:
			//std::cout << e.motion.x << " " << e.motion.y << std::endl;;
			break;
		}
	}
#endif
}

float Engine::Window::GetFrameTime()
{
#ifdef USING_GLFW
	return glfwGetTime() * 1000.0f;
#elif USING_SDL
	return SDL_GetTicks();
#endif
}
