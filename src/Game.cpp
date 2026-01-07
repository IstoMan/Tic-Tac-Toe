#include "Game.h"
#include "GameObject.h"
#include <cmath>

void Game::placeSymbol(int x, int y, GameObject obj)
{
	float spacing = state.logSize / 3;

	float     spriteSize = 30;
	SDL_FRect dst{
	    .x = spacing * x,
	    .y = spacing * y,
	    .w = spriteSize,
	    .h = spriteSize,
	};
	SDL_RenderTexture(state.renderer, obj.tex, NULL, &dst);
}

void Game::handleInput()
{
	SDL_MouseButtonFlags mouseButton = SDL_GetMouseState(&mouseX, &mouseY);

	int col = -1, row = -1;

	if (mouseButton == SDL_BUTTON_LEFT)
	{
		col = floor(mouseX / (state.size / 3));
		row = floor(mouseY / (state.size / 3));

		board[col][row] = Symbols::X;
	}
}

void Game::onRender()
{
	drawGrid();
	drawPieces();
}

void Game::drawPieces()
{
	for (size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j < 3; ++j)
		{
			switch (board[i][j])
			{
				case X:
					placeSymbol(i, j, cross);
					break;
				case O:
					placeSymbol(i, j, circle);
					break;
				case E:
					break;
			}
		}
	}
}

void Game::drawGrid()
{
	float spacing   = state.logSize / 3;
	float thickness = 5;

	SDL_FRect xAxis{
	    .x = 0,
	    .y = 0,
	    .w = state.logSize,
	    .h = thickness,
	};

	SDL_FRect yAxis{
	    .x = 0,
	    .y = 0,
	    .w = thickness,
	    .h = state.logSize,
	};

	SDL_SetRenderDrawColor(state.renderer, 130, 130, 130, 255);
	SDL_RenderClear(state.renderer);

	SDL_SetRenderDrawColor(state.renderer, 180, 180, 180, 255);
	for (size_t i = 1; i <= 2; i++)
	{
		xAxis.y = spacing * i - thickness / 2;
		SDL_RenderFillRect(state.renderer, &xAxis);
	}

	for (size_t j = 1; j <= 2; j++)
	{
		yAxis.x = spacing * j - thickness / 2;
		SDL_RenderFillRect(state.renderer, &yAxis);
	}
}

void Game::onUpdate()
{
	handleInput();
}
