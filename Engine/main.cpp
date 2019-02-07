#include <iostream>

#include "Game.h"
#include "Sprite.h"

int main(int argc, char** argv)
{
	{
		Game g;
		g.Run();
	}

	std::cout << "GoodBye..." << std::endl;

	std::cin.get();

	return 0;
}