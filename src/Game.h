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

class Game : public App
{
private:
	std::array<std::array<Symbols, 3>, 3> board;

	Mode       gameMode;
	Player     currentPlayer;
	Resource  &res;
	GameObject circle;
	GameObject cross;

public:
	Game(Resource &resources);
	~Game();

	void  onRender() override;
	void  onEvent(SDL_Event &event) override;
	float mouseX, mouseY;

private:
	void handleInput();
	void placeSymbol(int x, int y, GameObject obj);
	void drawGrid();
	void drawPieces();
	void drawMenu();
};
