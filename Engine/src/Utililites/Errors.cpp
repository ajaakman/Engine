#include <cstdlib>
#include <iostream>

#include <SDL/SDL.h>
#include <GL/glew.h>

#include "Errors.h"

void FatalError(std::string errorString)
{
	DBG(
	std::cout << errorString << std::endl;
	std::cout << "Press any key to quit...";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
	exit(34404);
	)
}

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "OpenGL Error (" << error << "): " << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}