#include "Game.h"
#include "Engine.h"
#include "GameObject.h"
#include <SDL3/SDL_mouse.h>
#include <cmath>

Game::Game(Resource &resources) : gameMode(Mode::Menu), currentPlayer(Player::P1), res(resources), circle(O, res), cross(X, res)
{
	for (auto &row : board)
	{
		row.fill(Symbols::E);
	}
}

Game::~Game()
{
}

void Game::onUpdate()
{
	handleInput();
}

void Game::onRender()
{
	switch (gameMode)
	{
		case Mode::Menu:
			drawMenu();
			break;
		case Mode::GameOn:
			drawGrid();
			drawPieces();
			break;
		case Mode::GameOff:
			// TODO: Implement overlay game over menu
			break;
	}
}

void Game::placeSymbol(int x, int y, GameObject obj)
{
	float spacing = Engine::Get().GetLogSize() / 3;

	float     spriteSize = 30;
	SDL_FRect dst{
	    .x = spacing * x,
	    .y = spacing * y,
	    .w = spriteSize,
	    .h = spriteSize,
	};
	SDL_RenderTexture(Engine::Get().GetRenderer(), obj.tex, NULL, &dst);
}

void Game::handleInput()
{
	SDL_MouseButtonFlags mouseButton = SDL_GetMouseState(&mouseX, &mouseY);
	float                col         = floor(mouseX / (Engine::Get().GetSize() / 3));
	float                row         = floor(mouseY / (Engine::Get().GetSize() / 3));

	switch (gameMode)
	{
		case Mode::Menu:
		{
			if (mouseButton == SDL_BUTTON_LEFT)
			{
				gameMode = Mode::GameOn;
			}
		}
		break;
		case Mode::GameOn:
		{
			switch (currentPlayer)
			{
				case Player::P1:
				{
					board[col][row] = Symbols::X;
				}
				break;
				case Player::P2:
				{
					board[col][row] = Symbols::O;
				}
				break;
			}
		}
		case Mode::GameOff:
		{
			// TODO: Create an end screens
		}
		break;
	}
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
	float spacing   = Engine::Get().GetLogSize() / 3;
	float thickness = 5;

	SDL_FRect xAxis{
	    .x = 0,
	    .y = 0,
	    .w = Engine::Get().GetLogSize(),
	    .h = thickness,
	};

	SDL_FRect yAxis{
	    .x = 0,
	    .y = 0,
	    .w = thickness,
	    .h = Engine::Get().GetLogSize(),
	};

	SDL_SetRenderDrawColor(Engine::Get().GetRenderer(), 130, 130, 130, 255);
	SDL_RenderClear(Engine::Get().GetRenderer());

	SDL_SetRenderDrawColor(Engine::Get().GetRenderer(), 180, 180, 180, 255);
	for (size_t i = 1; i <= 2; i++)
	{
		xAxis.y = spacing * i - thickness / 2;
		SDL_RenderFillRect(Engine::Get().GetRenderer(), &xAxis);
	}

	for (size_t j = 1; j <= 2; j++)
	{
		yAxis.x = spacing * j - thickness / 2;
		SDL_RenderFillRect(Engine::Get().GetRenderer(), &yAxis);
	}
}

void Game::drawMenu()
{
	SDL_RenderClear(Engine::Get().GetRenderer());
	SDL_RenderTexture(Engine::Get().GetRenderer(), res.background, NULL, NULL);
	SDL_FRect dst{
	    .x = 15,
	    .y = 15,
	    .w = 60,
	    .h = 14,
	};

	SDL_RenderTexture(Engine::Get().GetRenderer(), res.menuTextTexture, NULL, &dst);
}
