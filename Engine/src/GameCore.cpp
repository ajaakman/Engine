#ifdef USING_GLFW	
#elif USING_SDL
#include <iostream>
#include <string>

#include "GameCore.h"
#include "Engine.h"

Engine::GameCore::GameCore() :  m_nScreenWidth(1024),
								m_nScreenHeight(768),
								m_GameState(GameState::PLAY),
								m_fTime(0.0f),
								m_fMaxFps(60.0f)
								{}

Engine::GameCore::~GameCore()
{
}

void Engine::GameCore::Run()
{
	Init();
	DBG(GL(std::printf("***     OpenGL Version: %s     ***\n", glGetString(GL_VERSION))));

	int spriteRow = 10;

	for (int i = 0; i < spriteRow; i++)
	{
		for (int j = 0; j < spriteRow; j++)
		{
			m_Sprites.push_back(new Engine::Sprite());
			m_Sprites.back()->Init(-1.0f + i * (1.0f / (float)spriteRow*2.0f), -1.0f + j * (1.0f / (float)spriteRow*2.0f), 2.0f / 10.0f, 2.0f / 10.0f, "../Resources/Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
		}
	}

	GameLoop();
}

void Engine::GameCore::Init()
{
	Engine::Init();

	m_Window.Init("My Game", m_nScreenWidth, m_nScreenHeight, 0);

	InitShaders();
}

void Engine::GameCore::InitShaders()
{
	m_ColorProgram.CompileShaders("../Resources/Shaders/BasicShader.vert", "../Resources/Shaders/BasicShader.frag");
	m_ColorProgram.AddAttribute("vertexPosition");
	m_ColorProgram.AddAttribute("vertexColor");
	m_ColorProgram.AddAttribute("vertexUV");
	m_ColorProgram.LinkShaders();
}

void Engine::GameCore::GameLoop()
{
	while (m_GameState != GameState::END)
	{
		float startTicks = SDL_GetTicks();


		ProcessInput();
		DrawFrame();
		m_fTime += 0.1f;

		CalculateFPS();
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 60)
		{
			std::cout << m_fFps << "\n";
			frameCounter = 0;
		}


		float frameTicks = SDL_GetTicks() - startTicks;
		if (1000.0f / m_fMaxFps > frameTicks)
			SDL_Delay(1000.0f / m_fMaxFps - frameTicks);
	}
}

void Engine::GameCore::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			m_GameState = GameState::END;
			break;
		case SDL_MOUSEMOTION:
			//std::cout << e.motion.x << " " << e.motion.y << std::endl;;
			break;
		}
	}
}

void Engine::GameCore::DrawFrame()
{
	GL(glClearDepth(1.0));
	GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	m_ColorProgram.Bind();
	GL(glActiveTexture(GL_TEXTURE0));
	GLint textureLocation = m_ColorProgram.getUniformLocation("tex2D");
	GL(glUniform1i(textureLocation, 0));

	GLint timeLocation = m_ColorProgram.getUniformLocation("time");
	GL(glUniform1f(timeLocation, m_fTime));

	for (auto & sprite : m_Sprites)
		sprite->Draw();

	GL(glBindTexture(GL_TEXTURE_2D, 0));
	m_ColorProgram.UnBind();

	m_Window.SwapBuffer();
}

void Engine::GameCore::CalculateFPS()
{
	static const int NUM_SAMPLES = 60;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float prevTicks = SDL_GetTicks();
	float currentTicks = SDL_GetTicks();

	m_fDeltaTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = m_fDeltaTime;

	prevTicks = currentTicks;

	int count;
	currentFrame++;

	if (currentFrame < NUM_SAMPLES)
		count = currentFrame;
	else
		count = NUM_SAMPLES;

	float frameTimeAverage = 0;
	for (int i = 0; i < count; ++i)
		frameTimeAverage += frameTimes[i];

	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
		m_fFps = 1000.0f / frameTimeAverage;
	else
		m_fFps = 60.0f;
}

#endif

