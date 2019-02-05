#include "Game.h"

Game::Game()
{
	p_mWindow = nullptr;
	n_mScreenWidth = 1024;
	n_mScreenHeight = 768;
}

Game::~Game()
{
}

void Game::Run()
{
	Init();
}

void Game::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	p_mWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, n_mScreenWidth, n_mScreenHeight, SDL_WINDOW_OPENGL);
}
