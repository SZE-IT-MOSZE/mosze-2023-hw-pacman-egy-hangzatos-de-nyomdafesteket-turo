#ifndef GAMEITEM_H
#define GAMEITEM_H

#include "Map.hpp"
#include "Engine.hpp"

class GameItem: public ITriggerable
{
public:
	GameItem(GameObject* container, Map* map);

	virtual ~GameItem();

	virtual void Trigger() = 0;
	virtual bool Condition() = 0;

protected:
	GameObject* container;
	Map* map;
};



#endif // !GAMEITEM_H