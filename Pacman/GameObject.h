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

	// Mark the object to be deleted
	virtual void Delete();

	// Returns true if the objects is marked for deletion
	bool ToDelete();

private:
	bool toDelete;
};

