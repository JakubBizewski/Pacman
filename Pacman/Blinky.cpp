#include "Blinky.h"

Blinky::Blinky(Tile* tile, Texture* texture)
{
	// Set all variables to default state
	currTile = tile;
	nextTile = NULL;

	if (currTile != NULL) {
		//currTile->SetPacman(this);
		nextTile = tileGraph->GetTileAt(currTile->GetPosition().x + 1, currTile->GetPosition().y);

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
	/*switch (moveDir)
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
	}*/
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
		//currTile->SetPacman(this);

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