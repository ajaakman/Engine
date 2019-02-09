#include <iostream>
#include <string>

#include "Game.h"
#include "Errors.h"

Game::Game()
	:p_mWindow(nullptr), n_mScreenWidth(1024), n_mScreenHeight(768)
{
	mGameState = GameState::PLAY;
}

Game::~Game()
{
	SDL_DestroyWindow(p_mWindow);
}

void Game::Run()
{
	Init();
	std::cout << glGetString(GL_VERSION) << std::endl;

	m_TestSprite.Init(-0.5f, -0.5f, 1.0f, 1.0f);

	GameLoop();
}

void Game::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	   
	p_mWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, n_mScreenWidth, n_mScreenHeight, SDL_WINDOW_OPENGL);

	if (p_mWindow == nullptr)
	{
		FatalError("SDL Window could not be created!");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(p_mWindow);

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
	m_ColorProgram.LinkShaders();
}

void Game::GameLoop()
{
	while (mGameState != GameState::END)
	{
		ProcessInput();
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
			mGameState = GameState::END;
			break;
		case SDL_MOUSEMOTION:
			std::cout << e.motion.x << " " << e.motion.y << std::endl;;
			break;
		}
	}
}

void Game::DrawGame()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_ColorProgram.Bind();
	m_TestSprite.Draw();
	m_ColorProgram.UnBind();

	SDL_GL_SwapWindow(p_mWindow);
}
