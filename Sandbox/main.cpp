#include <iostream>
#include "../Engine/src/Game.h"

int main(int argc, char** argv)
{
	std::cout << "Running from Sandbox entry point..." << std::endl;

	{
		Game g;
		g.Run();
	}

	std::cout << "GoodBye..." << std::endl;

	std::cin.get();

	return 0;
}