#pragma once
#include "App.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>

class Engine
{
private:
	SDL_Window   *m_Window;
	SDL_Renderer *m_Renderer;
	float         m_Size    = 900;
	float         m_LogSize = 90;

	SDL_Event event;
	bool      isRunning = true;

private:
	void Cleanup();

public:
	bool Initialize();
	~Engine();
	void           Run(App &game);
	float          GetLogSize();
	float          GetSize();
	SDL_Renderer  *GetRenderer();
	static Engine &Get();
};
