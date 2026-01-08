#pragma once
#include "Resource.h"
#include <SDL3/SDL_render.h>

enum class Symbols
{
	X,
	O,
	NIL,
};

struct GameObject
{
	Symbols      type;
	SDL_Texture *tex;

	GameObject(Symbols sym, Resource &res) : type(sym)
	{
		switch (sym)
		{
			case Symbols::X:
				tex = res.cross;
				break;
			case Symbols::O:
				tex = res.circle;
				break;
			case Symbols::NIL:
				break;
		}
	}
};
