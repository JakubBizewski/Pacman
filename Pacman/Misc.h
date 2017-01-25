#pragma once

void removeFromVector(std::vector<GameObject*>& list, GameObject& objectToRemove)
{
	list.erase(std::remove(list.begin(), list.end(), &objectToRemove), list.end());
}