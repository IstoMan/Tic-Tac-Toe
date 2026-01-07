#include "Resource.h"
#include <SDL3_image/SDL_image.h>

SDL_Texture *Resource::loadTexture(const std::filesystem::path &texturePath,
                                   SDL_Renderer                *renderer)
{
	SDL_Texture *tex = IMG_LoadTexture(renderer, texturePath.c_str());
	SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_LINEAR);
	textures.push_back(tex);

	return tex;
}

void Resource::load(Core::SDLState &state)
{
	cross  = loadTexture(std::filesystem::path("assets/x.svg"), state.renderer);
	circle = loadTexture(std::filesystem::path("assets/o.svg"), state.renderer);
}

Resource::~Resource()
{
	for (SDL_Texture *tex : textures)
	{
		SDL_DestroyTexture(tex);
	}
}
