#include "Game.h"
#include <iostream>

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
	GameLoop();
}

void Game::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	p_mWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, n_mScreenWidth, n_mScreenHeight, SDL_WINDOW_OPENGL);
}

void Game::GameLoop()
{
	while (mGameState != GameState::END)
	{
		ProcessInput();
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
