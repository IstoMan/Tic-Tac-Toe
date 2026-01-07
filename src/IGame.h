#pragma once

class IGame
{
public:
	virtual void onUpdate() = 0;
	virtual void onRender() = 0;
	virtual ~IGame() = default;
};
