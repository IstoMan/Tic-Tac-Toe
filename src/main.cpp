#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <array>
#include <cmath>
#include <iostream>

const float SIZE     = 900;
const float LOG_SIZE = 90;

enum Symbols
{
	X,
	O,
	E
};

void drawGrid(SDL_Renderer *renderer);
void placeSymbol(int x, int y, SDL_Texture *symbol, SDL_Renderer *renderer);

std::pair<int, int>                   handleInput(float mouseX, float mouseY);
std::array<std::array<Symbols, 3>, 3> board = {Symbols::E};

int main()
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		std::cerr << "Failed to init SDL" << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window   *window   = SDL_CreateWindow("Tic Tac Toe", SIZE, SIZE, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
	SDL_SetRenderLogicalPresentation(renderer, LOG_SIZE, LOG_SIZE, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);

	SDL_Texture *cross  = IMG_LoadTexture(renderer, "assets/x.svg");
	SDL_Texture *circle = IMG_LoadTexture(renderer, "assets/o.svg");

	bool      running = true;
	SDL_Event event;
	float     mouseX = 0, mouseY = 0;

	board = {
	    {
	        {E, E, E},
	        {E, X, E},
	        {E, E, E},
	    }};

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

		SDL_SetRenderDrawColor(renderer, 130, 130, 130, 255);
		SDL_RenderClear(renderer);

		// draw commands
		drawGrid(renderer);
		std::pair<int, int> indexs = handleInput(mouseX, mouseY);
		if (indexs.first != -1 || indexs.second != -1)
		{
			board[indexs.first][indexs.second] = X;
		}

		for (size_t i = 0; i < 3; ++i)
		{
			for (size_t j = 0; j < 3; ++j)
			{
				if (board[i][j] != E)
				{
					if (board[i][j] == X)
					{
						placeSymbol(i, j, cross, renderer);
					}
					else if (board[i][j] == O)
					{
						placeSymbol(i, j, circle, renderer);
					}
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

void drawGrid(SDL_Renderer *renderer)
{
	float spacing   = LOG_SIZE / 3;
	float thickness = 5;

	SDL_FRect xAxis{
	    .x = 0,
	    .y = 0,
	    .w = LOG_SIZE,
	    .h = thickness,
	};

	SDL_FRect yAxis{
	    .x = 0,
	    .y = 0,
	    .w = thickness,
	    .h = LOG_SIZE,
	};

	SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
	for (size_t i = 1; i <= 2; i++)
	{
		xAxis.y = spacing * i - thickness / 2;
		SDL_RenderFillRect(renderer, &xAxis);
	}

	for (size_t j = 1; j <= 2; j++)
	{
		yAxis.x = spacing * j - thickness / 2;
		SDL_RenderFillRect(renderer, &yAxis);
	}
}

std::pair<int, int> handleInput(float mouseX, float mouseY)
{
	SDL_MouseButtonFlags mouseButton = SDL_GetMouseState(&mouseX, &mouseY);

	int col = -1, row = -1;

	if (mouseButton == SDL_BUTTON_LEFT)
	{
		col = floor(mouseX / (SIZE / 3));
		row = floor(mouseY / (SIZE / 3));
	}

	return std::make_pair(col, row);
}

void placeSymbol(int x, int y, SDL_Texture *symbol, SDL_Renderer *renderer)
{
	float spacing = LOG_SIZE / 3;

	float     spriteSize = 30;
	SDL_FRect dst{
	    .x = spacing * x,
	    .y = spacing * y,
	    .w = spriteSize,
	    .h = spriteSize,
	};
	SDL_RenderTexture(renderer, symbol, NULL, &dst);
}
