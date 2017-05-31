#include "Wall.h"

SDL_Rect Wall::textureClips[16];

//Wall::Wall()
//{
//	currTile = NULL;
//
//	position.x = 0;
//	position.y = 0;
//
//	collider.w = Width;
//	collider.h = Height;
//}

void Wall::CreateClips()
{
	// 0000 - standalone
	// 1000 - N
	// 0100 - E
	// 0010 - S
	// 0001 - W

	textureClips[0] = { 0, 0, 25, 25 };
	textureClips[DIR_N] = { 25, 0, 25, 25 };
	textureClips[DIR_E] = { 50, 0, 25, 25 };
	textureClips[DIR_S] = { 75, 0, 25, 25 };
	textureClips[DIR_W] = { 0, 25, 25, 25 };
	textureClips[DIR_N | DIR_E] = { 25, 25, 25, 25 };
	textureClips[DIR_S | DIR_E] = { 50, 25, 25, 25 };
	textureClips[DIR_S | DIR_W] = { 75, 25, 25, 25 };
	textureClips[DIR_N | DIR_W] = { 0, 50, 25, 25 };
	textureClips[DIR_N | DIR_S] = { 50, 100, 25, 25 };
	textureClips[DIR_E | DIR_W] = { 75, 100, 25, 25 };
	textureClips[DIR_N | DIR_E | DIR_W] = { 25, 50, 25, 25 };
	textureClips[DIR_N | DIR_E | DIR_S] = { 50, 50, 25, 25 };
	textureClips[DIR_E | DIR_S | DIR_W] = { 75, 50, 25, 25 };
	textureClips[DIR_N | DIR_S | DIR_W] = { 0, 75, 25, 25 };
	textureClips[DIR_N | DIR_E | DIR_S | DIR_W] = { 25, 75, 25, 25 };
}

Wall::Wall(Tile* tile, Texture* texture)
{
	currTile = tile;

	wallTexture = texture;

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

	UpdateConnections();

	std::array<Tile*, 4> neighbours = tileGraph->GetNeighbours(this->currTile);
	for (int i = 0; i < 4; i++) {
		if (CheckForWall(neighbours[i]))
			neighbours[i]->GetWall()->UpdateConnections();
	}
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

void Wall::UpdateConnections()
{
	std::array<Tile*, 4> neighbours = tileGraph->GetNeighbours(this->currTile);

	connections = 0;

	if (CheckForWall(neighbours[0]))
		connections |= DIR_S;
	if (CheckForWall(neighbours[1]))
		connections |= DIR_E;
	if (CheckForWall(neighbours[2]))
		connections |= DIR_N;
	if (CheckForWall(neighbours[3]))
		connections |= DIR_W;
}

void Wall::Delete()
{
	// Calling base function
	GameObject::Delete();

	currTile->SetWall(NULL);
}

void Wall::Render()
{
	wallTexture->Render(position.x, position.y, &textureClips[connections]);
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

bool Wall::CheckForWall(Tile* tile)
{
	if (tile != NULL && tile->GetWall() != NULL)
		return true;

	return false;
}
