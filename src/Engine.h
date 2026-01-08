#pragma once
#include "IGame.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>

namespace Core
{

class Engine
{
private:
	SDL_Window   *m_Window;
	SDL_Renderer *m_Renderer;
	float         m_Size    = 700;
	float         m_LogSize = 90;

	SDL_Event event;
	bool      isRunning = true;

private:
	void Cleanup();

public:
	bool Initialize();
	~Engine();
	void run(IGame &game);
};
}        // namespace Core
