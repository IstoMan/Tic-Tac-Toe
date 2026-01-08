#pragma once
#include <SDL3/SDL_events.h>

class App
{
public:
	virtual void onRender()                = 0;
	virtual void onUpdate()                = 0;
	virtual void onEvent(SDL_Event &event) = 0;
	virtual ~App()                         = default;
};
