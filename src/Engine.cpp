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
	// TODO: Generate objects, place player and exit
}

void Engine::DestroyObject(GameObject* target)
{
	// TODO: DLinkedList IndexOf
	int index = updateList->IndexOf(target);
	// Move this after the game objects were updated
	//updateList->RemoveAt(index, true);
	//updateDelay->RemoveAt(index, true);
	deleteList->PushLast(target);
}

Map* Engine::GetMap()
{
	return map;
}

int Engine::MainMenu()
{


	return 0;
}

Engine::~Engine()
{
	triggerList->Empty(true);
	updateList->Empty(true);
	gameObjects->Empty(true);
	deleteList->Empty(true);

	delete triggerList;
	delete updateList;
	delete updateDelay;
	delete gameObjects;
	delete map;
	delete keyReader;
	delete rendererPtr;
	delete deleteList;
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
	deleteList = new DLinkedList<GameObject*>();
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