#pragma once
#include <vector>

#include "Engine/src/Graphics/Renderer/Shaders/GLSL.h"
#include "Engine/src/Graphics/Renderables/Sprite.h"
#include "Engine/src/Graphics/GLTexture.h"
#include "Engine/src/Window.h"
#include "Engine/src/GameCore.h"

enum class GameState {PLAY, END};

class Game //: public Engine::GameCore
{
public:
	Game();
	~Game();

	void Run();

private:
	void Init();
	void InitShaders();
	void GameLoop();	
	void DrawFrame();
	void CalculateFPS();

	Engine::Window m_Window;
	int m_nScreenWidth;
	int m_nScreenHeight;

	GameState m_GameState;

	std::vector<Engine::Sprite*> m_Sprites;

	Engine::GLSL m_ColorProgram;

	float m_fTime;
	float m_fMaxFps;
	float m_fFps;
	float m_fDeltaTime;

};

