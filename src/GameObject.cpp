#ifndef GAMEOBJECT
#define GAMEOBJECT

#include "GameObject.hpp"



#endif

GameObject::~GameObject()
{
}

void GameObject::StepLeft()
{
	location = location + PointLeft();
}

void GameObject::StepUp()
{
	location = location + PointUp();
}

void GameObject::StepRight()
{
	location = location + PointRight();
}

void GameObject::StepDown()
{
	location = location + PointDown();
}

void GameObject::DestroyThis()
{
	engine->DestroyObject(this);
}
