#include "Engine.h"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cassert>
#include <cstdint>
#include <iostream>

static Engine *s_Engine = nullptr;

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
	SDL_SetRenderVSync(m_Renderer, 1);

	SDL_SetRenderLogicalPresentation(m_Renderer, m_LogSize, m_LogSize, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);

	s_Engine = this;
	return initialized;
}

void Engine::Run(App &game)
{
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

SDL_Renderer *Engine::GetRenderer()
{
	return m_Renderer;
}

Engine &Engine::Get()
{
	assert(s_Engine);
	return *s_Engine;
}

float Engine::GetLogSize()
{
	return m_LogSize;
}

float Engine::GetSize()
{
	return m_Size;
}
