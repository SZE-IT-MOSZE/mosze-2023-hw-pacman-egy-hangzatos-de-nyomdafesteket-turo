#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Updateable.hpp"
#include "Triggerable.hpp"
#include "Point.cpp"
#include "Engine.hpp"

class GameObject : public ITriggerable, public IUpdateable
{
public:
	GameObject() = delete;
	virtual ~GameObject() = 0;

private:
	Point location;
	Engine* engine;
};



#endif

