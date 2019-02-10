#include <cstdlib>
#include <iostream>

#include <SDL/SDL.h>

#include "Errors.h"

void FatalError(std::string errorString)
{
	std::cout << errorString << std::endl;
	std::cout << "Press any key to quit...";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
	exit(34404);
}