#pragma once
#include "SDL/SDL.h"
#include "GL/glew.h"

class Game
{
public:
	Game();
	~Game();

	void Run();

private:
	void Init();

	SDL_Window* p_mWindow;
	int n_mScreenWidth;
	int n_mScreenHeight;

};

