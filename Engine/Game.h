#pragma once
#include "SDL/SDL.h"
#include "GL/glew.h"

enum class GameState {PLAY, END};

class Game
{
public:
	Game();
	~Game();

	void Run();

private:
	void Init();
	void GameLoop();
	void ProcessInput();

	SDL_Window* p_mWindow;
	int n_mScreenWidth;
	int n_mScreenHeight;

	GameState mGameState;

};

