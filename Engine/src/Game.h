#pragma once
#include "GL/glew.h"
#include "SDL/SDL.h"

#include "Graphics/Renderer/Shaders/GLSL.h"
#include "Graphics/Renderables/Sprite.h"

enum class GameState {PLAY, END};

class Game
{
public:
	Game();
	~Game();

	void Run();

private:
	void Init();
	void InitShaders();
	void GameLoop();
	void ProcessInput();
	void DrawGame();

	SDL_Window* p_mWindow;
	int n_mScreenWidth;
	int n_mScreenHeight;

	GameState mGameState;

	Sprite m_TestSprite;

	GLSL m_ColorProgram;

};

