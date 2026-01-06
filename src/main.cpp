#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>

void Initialize()
{
}

int main()
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		std::cerr << "Failed to init SDL" << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window   *window   = SDL_CreateWindow("Tic Tac Toe", 900, 900, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);

	bool      running = true;
	SDL_Event event;

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_EVENT_QUIT:
				{
					running = false;
				}
			}
		}

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
