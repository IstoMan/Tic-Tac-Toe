#include "Engine.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

namespace Core
{
bool Engine::Initialize()
{
	return state.Initialize();
}

void Engine::run(IGame &game)
{
	SDL_Event event;

	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_EVENT_QUIT:
				{
					isRunning = false;
				}
			}
		}

		game.onRender();
		game.onUpdate();

		SDL_RenderPresent(state.renderer);
	}
}

SDLState::SDLState(float size, float logSize) : window(nullptr), renderer(nullptr), size(size), logSize(logSize)
{
}

bool SDLState::Initialize()
{
	bool initialized = true;
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		std::cerr << "Failed to init SDL" << SDL_GetError() << std::endl;
		initialized = false;
		Cleanup();
	}

	if (!TTF_Init())
	{
		std::cerr << "Failed to init font system " << SDL_GetError() << std::endl;
		initialized = false;
		Cleanup();
	}

	window = SDL_CreateWindow("Tic Tac Toe", size, size, 0);
	if (!window)
	{
		std::cerr << "Failed to init window" << SDL_GetError() << std::endl;
		initialized = false;
		Cleanup();
	}

	renderer = SDL_CreateRenderer(window, nullptr);
	if (!renderer)
	{
		std::cerr << "Failed to init renderer" << SDL_GetError() << std::endl;
		initialized = false;
		Cleanup();
	}

	SDL_SetRenderLogicalPresentation(renderer, logSize, logSize, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);
	return initialized;
}

void SDLState::Cleanup()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}

SDLState::~SDLState()
{
	Cleanup();
}
}        // namespace Core
