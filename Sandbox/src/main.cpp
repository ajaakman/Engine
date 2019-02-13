#include <iostream>
#include "Game.h"

int main(int argc, char** argv)
{
	std::cout << "Running Sandbox project..." << std::endl;

	{
		Game g;
		g.Run();
	}

	std::cout << "GoodBye..." << std::endl;

	std::cin.get();

	return 0;
}