#include "Pacman.h"

Pacman::Pacman()
{
	// Set all variables to default state
	position.x = 0;
	position.y = 0;

	collider.w = Width;
	collider.h = Height;

	moveDir = MOVE_RIGHT;

	frame = 0;
	frameCount = 0;
}

Pacman::~Pacman()
{
	Free();
}

void Pacman::SetPos(int newX, int newY)
{
	position.x = newX;
	position.y = newY;
}

void Pacman::HandleEvents(SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN && event->key.repeat == 0)
	{
		switch (event->key.keysym.sym)
		{
		// Move up
		case SDLK_UP:
		case SDLK_w: moveDir = MOVE_UP; break;

		// Move down
		case SDLK_DOWN:
		case SDLK_s: moveDir = MOVE_DOWN; break;

		// Move left
		case SDLK_LEFT:
		case SDLK_a: moveDir = MOVE_LEFT; break;

		// Move right
		case SDLK_RIGHT:
		case SDLK_d: moveDir = MOVE_RIGHT; break;
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

void Pacman::Update()
{
	if (moving)
	{
		frameCount++;
		frame = frameCount / 8;

		if (frame > MoveFrames - 1)
		{
			frame = 0;
			frameCount = 0;
		}
	}

	switch (moveDir)
	{
	case MOVE_UP:
		if ((position.y - Velocity) < 0) {
			position.y = 0;
			moving = false;
		}
		else {
			position.y -= Velocity;
			moving = true;
		}
		break;

	case MOVE_DOWN:
		if (((position.y + Height) + Velocity) > SCREEN_HEIGHT) {
			position.y = SCREEN_HEIGHT - Height;
			moving = false;
		}
		else {
			position.y += Velocity;
			moving = true;
		}
		break;

	case MOVE_LEFT:
		if ((position.x - Velocity) < 0) {
			position.x = 0;
			moving = false;
		}
		else {
			position.x -= Velocity;
			moving = true;
		}
		break;

	case MOVE_RIGHT:
		if (((position.x + Width) + Velocity) > SCREEN_WIDTH) {
			position.x = SCREEN_WIDTH - Width;
			moving = false;
		}
		else {
			position.x += Velocity;
			moving = true;
		}
		break;
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

void Pacman::Free()
{
	pacmanTexture.Free();
}