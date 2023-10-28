#ifndef ENGINE
#define ENGINE


#include "Engine.hpp"



Engine::Engine()
{
	Init(); // Init used for later parametering of ctor
}

void Engine::PrepareGame(int mapWidth, int mapHeight, int seed)
{
	map->GenerateBaseMap(mapWidth, mapHeight, seed);
	map->GenerateFullMap();
}

void Engine::MainMenu()
{



}

Engine::~Engine()
{
	triggerList->Empty(true);
	updateList->Empty(true);
	gameObjects->Empty(true);

	delete triggerList;
	delete updateList;
	delete updateDelay;
	delete gameObjects;
	delete map;
	delete keyReader;
	delete rendererPtr;
}

void Engine::Init()
{
	map = new Map();
	keyReader = KeyInput::GetInstance();
	triggerList = new DLinkedList<ITriggerable*>();
	updateList = new DLinkedList<IUpdateable*>();
	updateDelay = new DLinkedList<int>();
	gameObjects = new DLinkedList<GameObject*>();
	rendererPtr = Renderer::GetInstance();
	Renderer::engine = this;
}

Engine* Engine::GetInstance()
{
	if (enginePtr == nullptr)
	{
		enginePtr = new Engine();
	}
	return enginePtr;
}



#endif // !ENGINE