#include "Game.h"
#include "Engine.h"
#include "GameObject.h"
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_system.h>
#include <array>
#include <cmath>
#include <cstddef>
#include <print>

Game::Game(Resource &resources) : gameMode(Mode::Menu), currentPlayer(Player::P1), res(resources), circle(Symbols::O, res), cross(Symbols::X, res)
{
	for (std::array<Symbols, 3> &row : board)
	{
		row.fill(Symbols::NIL);
	}
}

void Game::onUpdate()
{
	if (gameMode == Mode::GameOn)
	{
		Winner win = checkWin();
		switch (win)
		{
			case Winner::P1:
			{
				std::println("P1 Won");
			}
			break;
			case Winner::P2:
			{
				std::println("P2 Won");
			}
			break;
			case Winner::Draw:
			{
				std::println("It's a Draw");
			}
			break;
			default:
				break;
		}
	}
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

Winner Game::checkWin()
{
	Symbols winner = Symbols::NIL;
	// lines
	for (size_t i = 0; i < 3; ++i)
	{
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][1] != Symbols::NIL)
		{
			winner = board[i][1];
		}
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[1][i] != Symbols::NIL)
		{
			winner = board[1][i];
		}
	}

	// diagonals
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != Symbols::NIL)
	{
		winner = board[1][1];
	}

	if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != Symbols::NIL)
	{
		winner = board[1][1];
	}

	bool Empty = false;
	for (size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j < 3; ++j)
		{
			if (board[i][j] == Symbols::NIL)
			{
				Empty = true;
			}
		}
	}

	switch (winner)
	{
		case Symbols::X:
			return Winner::P1;
			break;
		case Symbols::O:
			return Winner::P2;
			break;
		case Symbols::NIL:
			if (Empty)
			{
				return Winner::None;
			}
			else
			{
				return Winner::Draw;
			}
			break;
	}

	return Winner::None;
}
