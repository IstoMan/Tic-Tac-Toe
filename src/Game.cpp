#include "Game.h"
#include "Engine.h"
#include "GameObject.h"
#include <SDL3/SDL_mouse.h>
#include <cmath>
#include <cstddef>
#include <print>

Game::Game(Resource &resources) : gameMode(Mode::Menu), currentPlayer(Player::P1), res(resources), circle(Symbols::O, res), cross(Symbols::X, res)
{
}

void Game::onUpdate()
{
	Symbols win = checkWin();
}

void Game::onEvent(SDL_Event &event)
{
	if (event.type == SDL_EVENT_MOUSE_BUTTON_UP && event.button.button == SDL_BUTTON_LEFT)
	{
		switch (gameMode)
		{
			case Mode::Menu:
			{
				gameMode = Mode::GameOn;
			}
			break;
			case Mode::GameOn:
			{
				mouseX = event.button.x;
				mouseY = event.button.y;

				float col = floor(mouseX / (Engine::Get().GetSize() / 3));
				float row = floor(mouseY / (Engine::Get().GetSize() / 3));

				switch (currentPlayer)
				{
					case Player::P1:
					{
						if (board[col][row] != Symbols::X && board[col][row] != Symbols::O)
						{
							board[col][row] = Symbols::X;
							currentPlayer   = Player::P2;
						}
					}
					break;
					case Player::P2:
					{
						if (board[col][row] != Symbols::X && board[col][row] != Symbols::O)
						{
							board[col][row] = Symbols::O;
							currentPlayer   = Player::P1;
						}
					}
					break;
				}
			}
			break;
			case Mode::GameOff:
			{
				// TODO: Create a end screen
			}
			break;
		}
	}
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

void Game::drawPieces()
{
	for (size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j < 3; ++j)
		{
			switch (board[i][j])
			{
				case Symbols::X:
					placeSymbol(i, j, cross);
					break;
				case Symbols::O:
					placeSymbol(i, j, circle);
					break;
				case Symbols::NIL:
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

Symbols Game::checkWin()
{
	// vertical
	for (size_t i = 0; i < 3; ++i)
	{
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
		{
			return board[i][0];
		}
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
		{
			return board[0][i];
		}
	}

	// horizontal
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
	{
		return board[1][1];
	}

	if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
	{
		return board[1][1];
	}

	bool isEmpty = true;
	for (size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j < 3; ++j)
		{
			if (board[i][j] == Symbols::O && board[i][j] == Symbols::X)
			{
				isEmpty = false;
			}
		}
	}

	if (!isEmpty)
	{
		return Symbols::NIL;
	}

	return Symbols::NIL;
}
