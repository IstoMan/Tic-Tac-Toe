#pragma once

class App
{
public:
	virtual void onUpdate() = 0;
	virtual void onRender() = 0;
	virtual ~App()          = default;
};
