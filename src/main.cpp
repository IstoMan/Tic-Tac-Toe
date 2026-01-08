#include "Engine.h"
#include "Game.h"
#include "Resource.h"
#include <iostream>

int main()
{
	Engine engine;
	if (!engine.Initialize())
	{
		std::cerr << "Failed to initialize engine." << std::endl;
		return 1;
	}

	Resource res;
	Game     game(res);

	engine.Run(game);

	return 0;
}
