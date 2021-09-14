#include "GameObject.h"

GameObject::GameObject()
{
	collider = nullptr;
}

GameObject::~GameObject()
{
	delete collider;
}