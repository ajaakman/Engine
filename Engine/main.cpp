#include <iostream>
#include "SDL/SDL.h"

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	std::cout << "Hello World" << std::endl;
	std::cin.get();

	return 0;
}