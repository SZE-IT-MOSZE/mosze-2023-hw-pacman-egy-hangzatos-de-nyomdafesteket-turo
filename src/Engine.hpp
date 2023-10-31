#ifndef ENGINE_H
#define ENGINE_H

class Engine;

#include "KeyInput.hpp"
#include "BStar.hpp"
#include "DLinkedList.hpp"
#include "DDelegate.hpp"
#include "Point.cpp"
#include "Updateable.hpp"
#include "Triggerable.hpp"
#include "Renderer.hpp"
#include "Map.hpp"
#include "GameObject.hpp"


class Engine
{
public:

	void operator=(const Engine& other) = delete;
	Engine(const Engine& other) = delete;

	~Engine();

	/// <summary>
	/// Access the singleton object's pointer
	/// </summary>
	/// <returns>The pointer to the Engine</returns>
	static Engine* GetInstance();


	/// <summary>
	/// The main menu where the player can choose their options
	/// </summary>
	/// <returns>The number of chosen option</returns>
	int MainMenu();

	/// <summary>
	/// The game
	/// </summary>
	void StartGame();

	enum Options
	{
		Quit = 0,
		PlayRandom = 1,
		LoadSavedMap = 2,
		CreateMap = 3
	};

	/// <summary>
	/// Prepare the game for playing on a randomly generated map.
	/// </summary>
	/// <param name="mapWidth">Width of the map</param>
	/// <param name="mapHeight">Height of the map</param>
	/// <param name="seed">Seed for the random generator</param>
	void PrepareGame(int mapWidth, int mapHeight, int seed = 1);

	/// <summary>
	/// Destroys the object from the game.
	/// </summary>
	/// <param name="target">Target to destroy</param>
	void DestroyObject(GameObject* target);

	Map* GetMap();

private:
	static Engine* enginePtr;

	/// <summary>
	/// Initialize pointer types
	/// </summary>
	void Init();

	/// <summary>
	/// A frame of the game. Every logic goes here
	/// </summary>
	void Frame();

	Engine();

	Map* map;

	KeyInput* keyReader;

	DLinkedList<ITriggerable*>* triggerList;

	DLinkedList<IUpdateable*>* updateList;

	DLinkedList<int>* updateDelay;

	DLinkedList<GameObject*>* gameObjects;

	DLinkedList<GameObject*>* deleteList; // Delete items at the end of the frame, before Clock

	Renderer* rendererPtr;

};

Engine* Engine::enginePtr = nullptr;


#endif
