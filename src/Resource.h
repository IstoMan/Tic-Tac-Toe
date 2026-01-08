#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <filesystem>
#include <vector>

struct Resource
{
	std::vector<SDL_Texture *> textures;
	std::vector<TTF_Font *>    fonts;

	SDL_Texture *cross, *circle, *background, *menuTextTexture;
	TTF_Font    *mainFont, *menuFont;

	SDL_Texture *loadTexture(const std::filesystem::path &texturePath);
	SDL_Texture *createTextTexture(TTF_Font *font, const std::string &text, SDL_Color color);
	TTF_Font    *loadFont(const std::filesystem::path &fontPath, float fontSize);

	Resource();
	~Resource();
};
