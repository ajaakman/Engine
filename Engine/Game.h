#pragma once
#include "SDL/SDL.h"
#include "GL/glew.h"

#include "Sprite.h"

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
	void DrawGame();

	SDL_Window* p_mWindow;
	int n_mScreenWidth;
	int n_mScreenHeight;

	GameState mGameState;

	Sprite m_TestSprite;

};

