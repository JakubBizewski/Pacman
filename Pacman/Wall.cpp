#include "Wall.h"

TileGraph* Wall::tileGraph = NULL;


Wall::Wall()
{
	currTile = NULL;

	position.x = 0;
	position.y = 0;

	collider.w = Width;
	collider.h = Height;
}

Wall::Wall(Tile* tile)
{
	currTile = tile;

	if (currTile != NULL) {
		currTile->SetWall(this);

		position.x = currTile->GetPosition().x * Width;
		position.y = currTile->GetPosition().y * Height;
	}
	else {
		position.x = 0;
		position.y = 0;
	}

	collider.w = Width;
	collider.h = Height;
}

Wall::~Wall()
{
	Free();
}

void Wall::SetTile(Tile* newTile)
{
	if (currTile != NULL)
		currTile->SetWall(NULL);

	currTile = newTile;

	if (currTile != NULL) {
		currTile->SetWall(this);

		position.x = currTile->GetPosition().x * Width;
		position.y = currTile->GetPosition().y * Height;
	}
}

void Wall::Delete()
{
	// Calling base function
	GameObject::Delete();

	currTile->SetWall(NULL);
}

bool Wall::LoadMedia()
{
	if (!wallTexture.LoadFromImage("./Resources/wall.bmp"))
		return false;

	return true;
}

void Wall::Render()
{
	wallTexture.Render(position.x, position.y);
}

void Wall::Free()
{
	wallTexture.Free();
}

SDL_Rect Wall::GetCollider()
{
	return collider;
}

SDL_Point Wall::GetPosition()
{
	return position;
}

Tile* Wall::GetTile()
{
	return currTile;
}