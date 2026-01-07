#pragma once
#include "Engine.h"
#include <SDL3/SDL_render.h>
#include <filesystem>
#include <vector>

struct Resource
{
	std::vector<SDL_Texture *> textures;

	SDL_Texture *cross, *circle;

	SDL_Texture *loadTexture(const std::filesystem::path &texturePath, SDL_Renderer *renderer);
	void         load(Core::SDLState &state);

	~Resource();
};
