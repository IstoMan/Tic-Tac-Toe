#pragma once
#include "Resource.h"
#include <SDL3/SDL_render.h>
#include <iostream>

enum Symbols
{
	X,
	O,
	E
};

struct GameObject
{
	Symbols      type;
	SDL_Texture *tex;

	GameObject(Symbols sym, Resource &res) : type(sym)
	{
		switch (sym)
		{
			case X:
				tex = res.cross;
				break;
			case O:
				tex = res.circle;
				break;
			case E:
				std::cout << "Moron passed an empty symbol" << "\n";
				break;
		}
	}
};
