#include "Resource.h"
#include "Engine.h"
#include <cassert>
#include <filesystem>

SDL_Texture *Resource::loadTexture(const std::filesystem::path &texturePath)
{
	SDL_Texture *tex = IMG_LoadTexture(Engine::Get().GetRenderer(), texturePath.c_str());
	SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
	SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_LINEAR);
	textures.push_back(tex);

	return tex;
}

SDL_Texture *Resource::createTextTexture(TTF_Font *font, const std::string &text, SDL_Color color)
{
	// SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), text.length(), color);
	SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), text.length(), color);

	SDL_Texture *tex = SDL_CreateTextureFromSurface(Engine::Get().GetRenderer(), surface);
	SDL_DestroySurface(surface);

	if (tex)
	{
		SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_LINEAR);
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

Resource::Resource()
{
	mainFont = loadFont(std::filesystem::path("assets/fonts/PlanetJumbo.ttf"), 80);
	menuFont = loadFont(std::filesystem::path("assets/fonts/Inter-Variable.ttf"), 18);

	titleText  = createTextTexture(mainFont, "Tic Tac Toe", {213, 166, 42, 255});
	cross      = loadTexture(std::filesystem::path("assets/x.svg"));
	circle     = loadTexture(std::filesystem::path("assets/o.svg"));
	background = loadTexture(std::filesystem::path("assets/background.jpg"));

	Uint8 opactiy = 100;
	SDL_SetTextureAlphaMod(background, opactiy);
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
