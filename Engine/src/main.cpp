#ifdef USING_GLFW	

#elif USING_SDL
#include <iostream>

#include "GameCore.h"

int main(int argc, char** argv)
{
	std::cout << "Running from Engine..." << std::endl;
	{
		Engine::GameCore g;
		g.Run();
	}

	std::cout << "GoodBye..." << std::endl;

	std::cin.get();

	return 0;
}

#endif