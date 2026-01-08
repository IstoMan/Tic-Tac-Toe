#pragma once
#include "GameObject.h"
#include "IGame.h"
#include "Resource.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <array>

enum class Mode
{
	Menu,
	GameOn,
	GameOff,
};
enum class Player
{
	NIL,
	P1,
	P2
};

class Game : public IGame
{
private:
	std::array<std::array<Symbols, 3>, 3> board;

	float      mouseX, mouseY;
	Mode       gameMode;
	Player     currentPlayer;
	Resource  &res;
	GameObject circle;
	GameObject cross;

public:
	Game(Resource &resources);
	~Game();

	void onRender() override;
	void onUpdate() override;

private:
	void handleInput();
	void placeSymbol(int x, int y, GameObject obj);
	void drawGrid();
	void drawPieces();
	void drawMenu();
};
