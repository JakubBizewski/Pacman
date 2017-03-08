#include <SDL.h>
#include "Texture.h"
#include "GameObject.h"
#include "Tile.h"
#include "TileGraph.h"

#include<algorithm>

#pragma once

// Just a temporary solution
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum MoveDirection {
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_STILL
};

class Pacman : public GameObject
{
public:
	static TileGraph* tileGraph;

	// Prefixed width and height of Pacman
	static const int Width = 25;
	static const int Height = 25;

	// Number of frames in movment animation
	static const int MoveFrames = 2;

	// Movement per frame
	static const int Velocity = 3;

	Pacman();
	~Pacman();

	// Loads texture and sets up animation clips
	bool LoadMedia();

	// Sets postiton of pacman
	// void SetPos(int x, int y);
	void SetTile(Tile* newTile);

	void SetNextTile(Tile* newNextTile);

	// Handles key presses
	void HandleEvents(SDL_Event* event);

	// Updates the posititon and check collision
	void Update();

	// Renders pacman
	void Render();

	// Releases texture memory
	void Free();

	// Returns current direction of movement
	MoveDirection GetMoveDirection();

	// Returns collider
	SDL_Rect GetCollider();

	// Returns position
	SDL_Point GetPosition();

	Tile* GetTile();
	Tile* GetNextTile();

	// Returns true if pacman is moving
	bool IsMoving();

private:
	Texture pacmanTexture;

	SDL_Rect upAnimClips[2];
	SDL_Rect downAnimClips[2];
	SDL_Rect leftAnimClips[2];
	SDL_Rect rightAnimClips[2];

	int frame, frameCount;

	MoveDirection moveDir;
	MoveDirection nextDir;
	bool moving;
	SDL_Point position;

	Tile* currTile;
	Tile* nextTile;

	SDL_Rect collider;
};

