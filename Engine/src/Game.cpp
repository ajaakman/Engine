#include <iostream>
#include <string>

#include "Game.h"
#include "Errors.h"

Game::Game() :  m_pWindow(nullptr), 
				m_nScreenWidth(1024), 
				m_nScreenHeight(768), 
				m_GameState(GameState::PLAY),
				m_fTime(0.0f)
{}

Game::~Game()
{
	SDL_DestroyWindow(m_pWindow);
}

void Game::Run()
{
	Init();
	GL(std::cout << glGetString(GL_VERSION) << std::endl);

	m_TestSprite.Init(-1.0f, -1.0f, 2.0f, 2.0f);

	GameLoop();
}

void Game::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	   
	m_pWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_nScreenWidth, m_nScreenHeight, SDL_WINDOW_OPENGL);

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

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	InitShaders();
}

void Game::InitShaders()
{
	m_ColorProgram.CompileShaders("src/Graphics/Renderer/Shaders/BasicShader.vert", "src/Graphics/Renderer/Shaders/BasicShader.frag");
	m_ColorProgram.AddAttribute("vertexPosition");
	m_ColorProgram.AddAttribute("vertexColor");
	m_ColorProgram.LinkShaders();
}

void Game::GameLoop()
{
	while (m_GameState != GameState::END)
	{
		ProcessInput();
		m_fTime += 0.01f;
		DrawGame();
	}
}

void Game::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			m_GameState = GameState::END;
			break;
		case SDL_MOUSEMOTION:
			std::cout << e.motion.x << " " << e.motion.y << std::endl;;
			break;
		}
	}
}

void Game::DrawGame()
{

	GL(glClearDepth(1.0));
	GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	m_ColorProgram.Bind();

	GLuint timeLocation = m_ColorProgram.getUniformLocation("time");
	GL(glUniform1f(timeLocation, m_fTime));

	m_TestSprite.Draw();
	m_ColorProgram.UnBind();

	SDL_GL_SwapWindow(m_pWindow);
}
