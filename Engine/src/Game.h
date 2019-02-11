#pragma once
#include "GL/glew.h"
#include "SDL/SDL.h"

#include "Graphics/Renderer/Shaders/GLSL.h"
#include "Graphics/Renderables/Sprite.h"
#include "Graphics/GLTexture.h"

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
	void DrawFrame();

	SDL_Window* m_pWindow;
	int m_nScreenWidth;
	int m_nScreenHeight;

	GameState m_GameState;

	Sprite m_TestSprite;
	GLTexture m_PlayerTexture;

	GLSL m_ColorProgram;

	float m_fTime;

};

