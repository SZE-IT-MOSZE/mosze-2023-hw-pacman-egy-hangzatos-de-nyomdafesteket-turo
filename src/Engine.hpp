#ifndef ENGINE_H
#define ENGINE_H

class Engine;

#include "Renderer.hpp"
#include "Map.hpp"
#include "GameObject.hpp"
#include "DLinkedList.hpp"
#include "KeyInput.hpp"


class Engine
{
public:

	void operator=(const Engine& other) = delete;
	Engine(const Engine& other) = delete;

	~Engine();

	static Engine* GetInstance();
	static Engine* enginePtr;
	DLinkedList<Point>* PathfindInRoom(Point begin, Point target);
	DLinkedList<Point>* PathfindInLogicMap(Point begin, Point target);
	DLinkedList<Point>* PathfindInLogicMapAsync(Point begin, Point target);
	DLinkedList<Point>* PathfindFullMapAsync(Point begin, Point target);
	void PrepareGame(int mapWidth, int mapHeight, int seed = 1);
	int MainMenu();

private:
	void Init();
	Engine();

	Map* map;

	KeyInput* keyReader;

	DLinkedList<ITriggerable*>* triggerList;

	DLinkedList<IUpdateable*>* updateList;

	DLinkedList<int>* updateDelay;

	DLinkedList<GameObject*>* gameObjects;

	Renderer* rendererPtr;

};

Engine* Engine::enginePtr = nullptr;


#endif
