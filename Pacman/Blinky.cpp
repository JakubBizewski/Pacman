#include "Blinky.h"

Blinky::Blinky(Tile* tile, Texture* texture)
{
	// Set all variables to default state
	currTile = tile;
	nextTile = NULL;

	if (currTile != NULL) {
		currTile->SetBlinky(this);
		nextTile = tileGraph->GetTileAt(currTile->GetPosition().x, currTile->GetPosition().y);

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

	blinkyTexture = texture;
}

Blinky::~Blinky()
{
	Free();
}

void Blinky::Update()
{
	Pacman* pacman = tileGraph->GetPacman();

	// Check if the pacman is even alive
	if (pacman != NULL) {
		// The NPC will calculate a new path every time it has entered a new tile
		// In this way, it will dynamically follow Pacman
		if (currTile == nextTile) {
			// Get a path to Pacman using A* algorithm
			PathFinder astar(tileGraph);
			astar.SetAvoidFunction(Blinky::AvoidInPathFinder);
			path = astar.CalculateRoute(currTile, pacman->GetTile());

			nextTile = path[1];

			// All we really want to do after this is check the direction the NPC should go
			if (position.x < nextTile->GetPosition().x * Tile::Width)
				moveDir = MOVE_RIGHT;

			else if (position.x > nextTile->GetPosition().x * Tile::Width)
				moveDir = MOVE_LEFT;

			else if (position.y > nextTile->GetPosition().y * Tile::Width)
				moveDir = MOVE_UP;

			else if (position.y < nextTile->GetPosition().y * Tile::Width)
				moveDir = MOVE_DOWN;

			// Check if Blinky collides with Pacman, if so delete Pacman
			// TODO: There should be a Kill() method within Pacman, which will play death animation
			for (auto tile : tileGraph->GetNeighbours(currTile)) {
				if (tile->GetPacman() != NULL && CheckForCollision(tile->GetPacman()->GetCollider())) {
					tile->GetPacman()->Delete();
				}
			}
		}

		// Depending of the direction of movement, move the NPC accordingly
		switch (moveDir)
		{
		case MOVE_UP:
			position.y = std::max(position.y - Velocity, nextTile->GetPosition().y * Tile::Height);
			break;
		case MOVE_DOWN:
			position.y = std::min(position.y + Velocity, nextTile->GetPosition().y * Tile::Height);
			break;
		case MOVE_LEFT:
			position.x = std::max(position.x - Velocity, nextTile->GetPosition().x * Tile::Width);
			break;
		case MOVE_RIGHT:
			position.x = std::min(position.x + Velocity, nextTile->GetPosition().x * Tile::Width);
			break;
		}

		// Update the collider
		collider.x = position.x;
		collider.y = position.y;

		// Check if the NPC has moved to the next tile, if so, change his current tile
		if ((moveDir == MOVE_DOWN || moveDir == MOVE_UP) && position.y == nextTile->GetPosition().y * Tile::Height)
			SetTile(nextTile);

		if ((moveDir == MOVE_LEFT || moveDir == MOVE_RIGHT) && position.x == nextTile->GetPosition().x * Tile::Width)
			SetTile(nextTile);
	}
}

void Blinky::Render()
{
	SDL_Rect clip{ 0,0,25,25 };
	blinkyTexture->Render(position.x, position.y, &clip);
}

void Blinky::SetTile(Tile* newTile)
{
	if (currTile != NULL)
		currTile->SetPacman(NULL);

	currTile = newTile;

	if (currTile != NULL) {
		currTile->SetBlinky(this);

		position.x = currTile->GetPosition().x * Tile::Width;
		position.y = currTile->GetPosition().y * Tile::Height;
	}
}

void Blinky::SetNextTile(Tile* newNextTile)
{
	nextTile = newNextTile;
}

bool Blinky::CheckForCollision(const SDL_Rect &otherCollider)
{
	if (otherCollider.x > collider.x + collider.w) {
		//printf("1");
		return false;
	}

	if (otherCollider.y > collider.y + collider.h) {
		//printf("2");
		return false;
	}

	if (otherCollider.x + otherCollider.w < collider.x) {
		//printf("3");
		return false;
	}

	if (otherCollider.y + otherCollider.h < collider.y) {
		//printf("4");
		return false;
	}

	return true;
}

bool Blinky::CheckForCollision(const SDL_Rect &collider, const SDL_Rect &otherCollider)
{
	if (otherCollider.x > collider.x + collider.w) {
		//printf("1");
		return false;
	}

	if (otherCollider.y > collider.y + collider.h) {
		//printf("2");
		return false;
	}

	if (otherCollider.x + otherCollider.w < collider.x) {
		//printf("3");
		return false;
	}

	if (otherCollider.y + otherCollider.h < collider.y) {
		//printf("4");
		return false;
	}

	return true;
}

bool Blinky::HasPositionChanged(SDL_Point firstPos, SDL_Point secondPoint)
{
	if (firstPos.x != secondPoint.x || firstPos.y != secondPoint.y)
		return true;

	return false;
}

bool Blinky::AvoidInPathFinder(Tile* tile)
{
	if (tile->GetWall() != NULL) return true;

	return false;
}

void Blinky::Delete()
{
	// Calling the base function
	GameObject::Delete();

	//currTile->SetPacman(NULL);
}

MoveDirection Blinky::GetMoveDirection()
{
	return moveDir;
}

SDL_Rect Blinky::GetCollider()
{
	return collider;
}

SDL_Point Blinky::GetPosition()
{
	return position;
}

Tile* Blinky::GetTile()
{
	return currTile;
}

Tile* Blinky::GetNextTile()
{
	return nextTile;
}

bool Blinky::IsMoving()
{
	return moving;
}