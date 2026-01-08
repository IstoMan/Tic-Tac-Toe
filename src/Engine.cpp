#include "Engine.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

namespace Core
{
bool Engine::Initialize()
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

	m_Window = SDL_CreateWindow("Tic Tac Toe", m_Size, m_Size, 0);
	if (!m_Window)
	{
		std::cerr << "Failed to init window" << SDL_GetError() << std::endl;
		initialized = false;
		Cleanup();
	}

	m_Renderer = SDL_CreateRenderer(m_Window, nullptr);
	if (!m_Renderer)
	{
		std::cerr << "Failed to init renderer" << SDL_GetError() << std::endl;
		initialized = false;
		Cleanup();
	}

	SDL_SetRenderLogicalPresentation(m_Renderer, m_LogSize, m_LogSize, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);
	return initialized;
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

		SDL_RenderPresent(m_Renderer);
	}
}

void Engine::Cleanup()
{
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	TTF_Quit();
	SDL_Quit();
}

Engine::~Engine()
{
	Cleanup();
}
}        // namespace Core
