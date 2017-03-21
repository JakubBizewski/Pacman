#include "GameObject.h"

void GameObject::HandleEvents(SDL_Event* event) {}
void GameObject::Update() {}
void GameObject::Render() {}
void GameObject::Free() {}
SDL_Rect* GameObject::GetColliders() { return NULL; }

void GameObject::Delete()
{
	toDelete = true;
}

bool GameObject::ToDelete()
{
	return toDelete;
}