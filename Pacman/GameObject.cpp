#include "GameObject.h"

TileGraph* GameObject::tileGraph = NULL;

void GameObject::HandleEvents(SDL_Event* event) {}
void GameObject::Update() {}
void GameObject::Render() {}
void GameObject::Free() {}
SDL_Rect GameObject::GetCollider() { return { 0,0,0,0 }; }
GameObject::~GameObject() {}

 
void GameObject::Delete()
{
	toDelete = true;
}

bool GameObject::ToDelete() const
{
	return toDelete;
};