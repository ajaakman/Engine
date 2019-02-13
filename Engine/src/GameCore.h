#pragma once
#include <vector>

#include "Graphics/Renderer/Shaders/GLSL.h"
#include "Graphics/Renderables/Sprite.h"
#include "Graphics/GLTexture.h"
#include "Window.h"

namespace Engine {

	enum class GameState { PLAY, END };

	class GameCore
	{
	public:
		GameCore();
		virtual ~GameCore();

		virtual void Run();

	private:
		void Init();
		void InitShaders();
		void GameLoop();
		void ProcessInput();
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

}