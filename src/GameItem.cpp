#ifndef GAMEITEM
#define GAMEITEM

#include "GameItem.hpp"

GameItem::GameItem(GameObject* container, Map* map)
{
	this->container = container;
	this->map = map;
}

GameItem::~GameItem()
{

}


#endif // !GAMEITEM