#include "Pacman.h"

TileGraph* Pacman::tileGraph = NULL;

Pacman::Pacman()
{
	// Set all variables to default state
	currTile = NULL;
	nextTile = NULL;

	position.x = 0;
	position.y = 0;

	collider.w = Width;
	collider.h = Height;

	moveDir = MOVE_RIGHT;
	nextDir = MOVE_RIGHT;

	frame = 0;
	frameCount = 0;
}

Pacman::Pacman(Tile* tile)
{
	// Set all variables to default state
	currTile = tile;
	nextTile = NULL;

	if (currTile != NULL) {
		currTile->SetPacman(this);

		position.x = currTile->GetPosition().x * Width;
		position.y = currTile->GetPosition().y * Height;
	}
	else {
		position.x = 0;
		position.y = 0;
	}

	collider.w = Width;
	collider.h = Height;

	moveDir = MOVE_RIGHT;
	nextDir = MOVE_RIGHT;

	frame = 0;
	frameCount = 0;
}

Pacman::~Pacman()
{
	Free();
}

/*void Pacman::SetPos(int newX, int newY)
{
	position.x = newX;
	position.y = newY;
}*/

void Pacman::SetTile(Tile* newTile)
{
	if (currTile != NULL)
		currTile->SetPacman(NULL);

	currTile = newTile;
	
	if (currTile != NULL) {
		currTile->SetPacman(this);

		position.x = currTile->GetPosition().x * Width;
		position.y = currTile->GetPosition().y * Height;
	}
}

void Pacman::SetNextTile(Tile* newNextTile)
{
	nextTile = newNextTile;
}

void Pacman::HandleEvents(SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN && event->key.repeat == 0) {
		switch (event->key.keysym.sym)
		{
		// Move up
		case SDLK_UP:
		case SDLK_w: nextDir = MOVE_UP; break;

		// Move down
		case SDLK_DOWN:
		case SDLK_s: nextDir = MOVE_DOWN; break;

		// Move left
		case SDLK_LEFT:
		case SDLK_a: nextDir = MOVE_LEFT; break;

		// Move right
		case SDLK_RIGHT:
		case SDLK_d: nextDir = MOVE_RIGHT; break;
		}
	}
}

bool Pacman::LoadMedia()
{
	if (!pacmanTexture.LoadFromImage("./Resources/PacMan.bmp"))
		return false;

	// Leftward movment animation clips
	leftAnimClips[0] = { 0,0,25,25 };
	leftAnimClips[1] = { 25,0,25,25 };

	// Rightward movment animation clips
	rightAnimClips[0] = { 0,25,25,25 };
	rightAnimClips[1] = { 25,25,25,25 };

	// Upward movement animation clips
	downAnimClips[0] = { 50,0,25,25 };
	downAnimClips[1] = { 75,0,25,25 };

	// Upward movement animation clips
	upAnimClips[0] = { 50,25,25,25 };
	upAnimClips[1] = { 75,25,25,25 };

	return true;
}

bool Pacman::TryToMove(MoveDirection direction)
{
	Tile* destTile = NULL;

	switch (direction)
	{
	case MOVE_UP:
		destTile = tileGraph->GetTileAt(currTile->GetPosition().x, currTile->GetPosition().y - 1);
		break;
	case MOVE_DOWN:
		destTile = tileGraph->GetTileAt(currTile->GetPosition().x, currTile->GetPosition().y + 1);
		break;
	case MOVE_LEFT:
		destTile = tileGraph->GetTileAt(currTile->GetPosition().x - 1, currTile->GetPosition().y);
		break;
	case MOVE_RIGHT:
		destTile = tileGraph->GetTileAt(currTile->GetPosition().x + 1, currTile->GetPosition().y);
		break;
	}

	if (destTile == NULL) {
		SetNextTile(NULL);
		return false;
	}

	if (destTile->GetWall() != NULL) {
		SetNextTile(NULL);
		return false;
	}

	SetNextTile(destTile);

	return true;
}

void Pacman::Update()
{
	if (moving) {
		frameCount++;
		frame = frameCount / 8;

		if (frame > MoveFrames - 1) {
			frame = 0;
			frameCount = 0;
		}
	}

	if (nextTile == currTile || nextTile == NULL) {
		if (nextDir != moveDir && TryToMove(nextDir))
			moveDir = nextDir;
		else
			TryToMove(moveDir);

		if (nextTile == NULL)
			moving = false;
		else
			moving = true;
	}
	else {
		switch (moveDir)
		{
		case MOVE_UP:
			position.y = std::max(position.y - Velocity, nextTile->GetPosition().y * Height);
			break;
		case MOVE_DOWN:
			position.y = std::min(position.y + Velocity, nextTile->GetPosition().y * Height);
			break;
		case MOVE_LEFT:
			position.x = std::max(position.x - Velocity, nextTile->GetPosition().x * Width);
			break;
		case MOVE_RIGHT:
			position.x = std::min(position.x + Velocity, nextTile->GetPosition().x * Width);
			break;
		}

		if ((moveDir == MOVE_DOWN || moveDir == MOVE_UP) && position.y == nextTile->GetPosition().y * Height)
			SetTile(nextTile);

		if ((moveDir == MOVE_LEFT || moveDir == MOVE_RIGHT) && position.x == nextTile->GetPosition().x * Width)
			SetTile(nextTile);
	}
}

void Pacman::Render()
{
	SDL_Rect* animClip = NULL;

	switch (moveDir)
	{
	case MOVE_UP:
		animClip = &upAnimClips[frame];
		break;
	case MOVE_DOWN:
		animClip = &downAnimClips[frame];
		break;
	case MOVE_LEFT:
		animClip = &leftAnimClips[frame];
		break;
	case MOVE_RIGHT:
		animClip = &rightAnimClips[frame];
		break;
	}

	pacmanTexture.Render(position.x, position.y, animClip);
}

void Pacman::Delete()
{
	// Calling the base function
	GameObject::Delete();

	currTile->SetPacman(NULL);
}

void Pacman::Free()
{
	pacmanTexture.Free();
}

MoveDirection Pacman::GetMoveDirection()
{
	return moveDir;
}

SDL_Rect Pacman::GetCollider()
{
	return collider;
}

SDL_Point Pacman::GetPosition()
{
	return position;
}

Tile* Pacman::GetTile()
{
	return currTile;
}

Tile* Pacman::GetNextTile()
{
	return nextTile;
}

bool Pacman::IsMoving()
{
	return moving;
}