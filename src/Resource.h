#pragma once
#include "Engine.h"
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <filesystem>
#include <vector>

struct Resource
{
	std::vector<SDL_Texture *> textures;
	std::vector<TTF_Font *>    fonts;

	SDL_Texture *cross, *circle;
	TTF_Font    *mainFont, *menuFont;

	SDL_Texture *loadTexture(const std::filesystem::path &texturePath, SDL_Renderer *renderer);
	TTF_Font    *loadFont(const std::filesystem::path &fontPath);
	void         load(Core::SDLState &state);

	~Resource();
};
