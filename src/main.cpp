#include "Engine.h"
#include "Game.h"
#include "Resource.h"
#include <iostream>

int main()
{
	Core::Engine engine(900, 90);
	if (!engine.Initialize())
	{
		std::cerr << "Failed to initialize engine." << std::endl;
		return 1;
	}

	Resource res;
	res.load(engine.GetState());

	Game game(engine.GetState(), res);

	engine.run(game);

	return 0;
}
