#include "Resource.h"
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

SDL_Texture *Resource::loadTexture(const std::filesystem::path &texturePath,
                                   SDL_Renderer                *renderer)
{
	SDL_Texture *tex = IMG_LoadTexture(renderer, texturePath.c_str());
	SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_LINEAR);
	textures.push_back(tex);

	return tex;
}

TTF_Font *Resource::loadFont(const std::filesystem::path &fontPath)
{
	TTF_Font *font = TTF_OpenFont(fontPath.c_str(), 32);
	fonts.push_back(font);

	return font;
}

void Resource::load(Core::SDLState &state)
{
	cross  = loadTexture(std::filesystem::path("assets/x.svg"), state.renderer);
	circle = loadTexture(std::filesystem::path("assets/o.svg"), state.renderer);

	mainFont = loadFont("assets/fonts/SuperMario256.ttf");
	menuFont = loadFont("assets/fonts/Inter-Variable.ttf");
}

Resource::~Resource()
{
	for (SDL_Texture *tex : textures)
	{
		SDL_DestroyTexture(tex);
	}

	for (TTF_Font *font : fonts)
	{
		TTF_CloseFont(font);
	}
}
