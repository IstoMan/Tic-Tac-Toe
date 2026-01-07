#include "Resource.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cassert>

SDL_Texture *Resource::loadTexture(const std::filesystem::path &texturePath,
                                   SDL_Renderer                *renderer)
{
	SDL_Texture *tex = IMG_LoadTexture(renderer, texturePath.c_str());
	SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_LINEAR);
	textures.push_back(tex);

	return tex;
}

SDL_Texture *Resource::createTextTexture(TTF_Font *font, const std::string &text, SDL_Color color, SDL_Renderer *renderer)
{
	// SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), text.length(), color);
	SDL_Surface *surface = TTF_RenderText_LCD(font, text.c_str(), text.length(), color, SDL_Color{130, 130, 130, 255});
	if (!surface)
	{
		return nullptr;
	}

	SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_LINEAR);
	SDL_DestroySurface(surface);

	if (tex)
	{
		textures.push_back(tex);
	}

	return tex;
}

TTF_Font *Resource::loadFont(const std::filesystem::path &fontPath, float fontSize)
{
	TTF_Font *font = TTF_OpenFont(fontPath.c_str(), fontSize);
	assert(font != nullptr);
	fonts.push_back(font);

	return font;
}

Resource::Resource(Core::SDLState &state)
{
	cross  = loadTexture(std::filesystem::path("assets/x.svg"), state.renderer);
	circle = loadTexture(std::filesystem::path("assets/o.svg"), state.renderer);

	mainFont = loadFont(std::filesystem::path("assets/fonts/PlanetJumbo.ttf"), 32);
	menuFont = loadFont(std::filesystem::path("assets/fonts/Inter-Variable.ttf"), 18);
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
