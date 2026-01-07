#pragma once
#include "IGame.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>

namespace Core
{

struct SDLState
{
public:
	SDL_Window   *window;
	SDL_Renderer *renderer;
	float         size;
	float         logSize;

public:
	bool Initialize();
	SDLState(float size, float logSize);
	~SDLState();

private:
	void Cleanup();
};

class Engine
{
private:
	SDLState  state;
	SDL_Event event;
	bool      isRunning = true;

public:
	Engine(float size, float logSize) : state(size, logSize)
	{}
	SDLState &GetState()
	{
		return state;
	}
	bool Initialize();
	void run(IGame &game);
};
}        // namespace Core
