#pragma once

#include <SDL.h>
#include <vector>

class GameObject
{
public:
	virtual void HandleEvents(SDL_Event* event);
	virtual void Update();
	virtual void Render();
	virtual void Free();
	virtual SDL_Rect* GetColliders();
};

