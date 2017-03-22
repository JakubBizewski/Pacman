#include "Point.h"

TileGraph* Point::tileGraph = NULL;

Point::Point()
{
	currTile = NULL;

	position.x = 0;
	position.y = 0;

	collider.w = Width;
	collider.h = Height;
}

Point::Point(Tile* tile)
{
	currTile = tile;

	if (currTile != NULL) {
		currTile->SetPoint(this);

		position.x = currTile->GetPosition().x * Tile::Width + 7;
		position.y = currTile->GetPosition().y * Tile::Width + 7;
	}
	else {
		position.x = 0;
		position.y = 0;
	}

	collider.w = Width;
	collider.h = Height;

	collider.x = position.x;
	collider.y = position.y;
}

Point::~Point()
{
	Free();
}

void Point::SetTile(Tile* newTile)
{
	if (currTile != NULL)
		currTile->SetPoint(NULL);

	currTile = newTile;

	if (currTile != NULL) {
		currTile->SetPoint(this);

		position.x = currTile->GetPosition().x * Tile::Width + 7;
		position.y = currTile->GetPosition().y * Tile::Height + 7;

		collider.x = position.x;
		collider.y = position.y;
	}
}

bool Point::LoadMedia()
{
	if (!pointTexture.LoadFromImage("./Resources/point2.bmp"))
		return false;

	return true;
}

void Point::Render()
{
	pointTexture.Render(position.x, position.y);
}

void Point::Free()
{
	pointTexture.Free();
}

void Point::Delete()
{
	// Calling the base function
	GameObject::Delete();

	currTile->SetPoint(NULL);
}

SDL_Rect Point::GetCollider()
{
	return collider;
}

SDL_Point Point::GetPosition()
{
	return position;
}

Tile* Point::GetTile()
{
	return currTile;
}