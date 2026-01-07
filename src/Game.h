#pragma once
#include "Engine.h"
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

class Game : public IGame
{
private:
	std::array<std::array<Symbols, 3>, 3> board;

	float           mouseX, mouseY;
	Mode            gameMode;
	Core::SDLState &state;
	Resource       &res;
	GameObject      circle;
	GameObject      cross;

public:
	Game(Core::SDLState &engineState, Resource &resources);
	~Game();

	void onRender() override;
	void onUpdate() override;

private:
	void handleInput();
	void placeSymbol(int x, int y, GameObject obj);
	void drawGrid();
	void drawPieces();
	void drawMenu();

	SDL_Texture *menuTextTexture{nullptr};
};
