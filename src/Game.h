#pragma once
#include "Engine.h"
#include "GameObject.h"
#include "IGame.h"
#include "Resource.h"
#include <SDL3/SDL.h>
#include <array>

enum class Mode
{
	Menu,
	GameOn,
};

class Game : public IGame
{
	std::array<std::array<Symbols, 3>, 3> board;

	float           mouseX, mouseY;
	Mode            gameMode;
	Core::SDLState &state;
	Resource       &res;
	GameObject      circle;
	GameObject      cross;

public:
	Game(Core::SDLState &engineState, Resource &resources) : gameMode(Mode::Menu), state(engineState), res(resources), circle(O, res), cross(X, res)
	{
		for (auto &row : board)
		{
			row.fill(Symbols::E);
		}
	}

	void onRender() override;
	void onUpdate() override;
	void handleInput();
	void placeSymbol(int x, int y, GameObject obj);
	void drawGrid();
	void drawPieces();
};
