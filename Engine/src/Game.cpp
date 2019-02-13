#include <iostream>
#include <string>

#include "Game.h"
#include "Utililites/Errors.h"

Game::Game() :  m_pWindow(nullptr), 
				m_nScreenWidth(1024), 
				m_nScreenHeight(768), 
				m_GameState(GameState::PLAY),
				m_fTime(0.0f),
				m_fMaxFps(60.0f)
{}

Game::~Game()
{
	SDL_DestroyWindow(m_pWindow);
}

void Game::Run()
{
	Init();
	DBG(GL(std::printf("***     OpenGL Version: %s     ***\n", glGetString(GL_VERSION))));

	int spriteRow = 10;

	for (int i = 0; i < spriteRow; i++)
	{
		for (int j = 0; j < spriteRow; j++)
		{
			m_Sprites.push_back(new Sprite());
			m_Sprites.back()->Init(-1.0f + i * (1.0f/(float)spriteRow*2.0f), -1.0f + j * (1.0f / (float)spriteRow*2.0f), 2.0f / 10.0f, 2.0f / 10.0f, "src/Graphics/Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
		}
	}
			 
	GameLoop();
}

void Game::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	   
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_pWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_nScreenWidth, m_nScreenHeight, SDL_WINDOW_OPENGL);

	if (m_pWindow == nullptr)
	{
		FatalError("SDL Window could not be created!");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(m_pWindow);

	if (glContext == nullptr)
	{
		FatalError("SDL _GL context could not be created!");
	}
	// glewInit() needs to be called after a valid GLContext is set.
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		FatalError("Could not initialize GLEW!");
	}

	SDL_GL_SetSwapInterval(0); // VSync

	GL(glClearColor(0.9f, 0.9f, 0.9f, 1.0f));

	InitShaders();
}

void Game::InitShaders()
{
	m_ColorProgram.CompileShaders("src/Graphics/Renderer/Shaders/BasicShader.vert", "src/Graphics/Renderer/Shaders/BasicShader.frag");
	m_ColorProgram.AddAttribute("vertexPosition");
	m_ColorProgram.AddAttribute("vertexColor");
	m_ColorProgram.AddAttribute("vertexUV");
	m_ColorProgram.LinkShaders();
}

void Game::GameLoop()
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

void Game::ProcessInput()
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

void Game::DrawFrame()
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

	SDL_GL_SwapWindow(m_pWindow);
}

void Game::CalculateFPS()
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

