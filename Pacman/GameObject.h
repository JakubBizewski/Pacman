#pragma once

#include <SDL.h>
#include <vector>

class TileGraph;

class GameObject
{
public:
	static TileGraph* tileGraph;

	virtual void HandleEvents(SDL_Event* event);
	virtual void Update();
	virtual void Render();
	virtual void Free();
	virtual SDL_Rect GetCollider();

	virtual ~GameObject();

	// Mark the object to be deleted
	virtual void Delete();

	// Returns true if the objects is marked for deletion
	bool ToDelete() const;

private:
	bool toDelete;
};

