#pragma once
#include "App.h"
#include "GameObject.h"
#include "Resource.h"
#include <SDL3/SDL.h>
#include <array>

enum class Mode
{
	Menu,
	GameOn,
	GameOff,
};
enum class Player
{
	P1,
	P2
};

enum class Winner
{
	None,
	Draw,
	P1,
	P2
};

class Game : public App
{
private:
	std::array<std::array<Symbols, 3>, 3> board;

	Mode       gameMode;
	Player     currentPlayer;
	Resource  &res;
	Winner     winner;
	GameObject circle;
	GameObject cross;

public:
	Game(Resource &resources);

	void  onRender() override;
	void  onUpdate() override;
	void  onEvent(SDL_Event &event) override;
	float mouseX, mouseY;

private:
	void   handleInput();
	void   placeSymbol(int x, int y, GameObject obj);
	void   drawGrid();
	void   drawPieces();
	void   drawMenu();
	void   drawEndScreen();
	void   resetGame();
	Winner checkWin();
};
