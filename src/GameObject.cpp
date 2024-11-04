#ifndef GAMEOBJECT
#define GAMEOBJECT

#include "GameObject.hpp"



GameObject::GameObject()
{
	this->engine = Engine::GetInstance();
}

GameObject::GameObject(Engine* e)
{
	this->engine = e;
}

GameObject::GameObject(Engine* e, Point position)
{
	this->engine = e;
	this->location = position;
}

GameObject::~GameObject()
{
	
}

bool GameObject::StepLeft()
{
	return engine->MoveObject(this, location + PointLeft());
}

bool GameObject::StepUp()
{
	return engine->MoveObject(this, location + PointUp());
}

bool GameObject::StepRight()
{
	return engine->MoveObject(this, location + PointRight());
}

bool GameObject::StepDown()
{
	return engine->MoveObject(this, location + PointDown());
}

void GameObject::DestroyThis()
{
	engine->DestroyObject(this);
}

#endif