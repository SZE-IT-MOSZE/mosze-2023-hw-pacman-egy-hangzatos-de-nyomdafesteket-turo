#ifndef ENGINE_H
#define ENGINE_H

class Engine;

#include "Clock.hpp"
#include "KeyInput.hpp"
#include "BStar.hpp"
#include "DLinkedList.hpp"
#include "DDelegate.hpp"
#include "Point.cpp"
#include "Updateable.hpp"
#include "Triggerable.hpp"
#include "RenderImage.hpp"
#include "Renderer.hpp"
#include "GameObject.hpp"
#include "NPC.hpp"
#include "MainCharacter.hpp"
#include "Behaviour.hpp"
#include "BehaviourTemplates.hpp"
#include "Map.hpp"
#include "Exit.hpp"
#include "GameItem.hpp"
#include "LIDAR.hpp"
#include "SensorBatch.hpp"
#include "LoadingScreen.cpp"
#include "Trap.hpp" // Why...
#include "EMFDetector.hpp"
#include <iostream>

#define UPDATE_DISTANCE (ROOM_WIDTH + ROOM_HEIGHT) * 2
#define LOS_CHECK_PRECISION 0.1
#define MATH_PI 3.14159265358979323846


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

	static enum MenuOptions
	{
		Quit = 0,
		PlayRandom = 1,
		LoadSavedMap = 2,
		CreateMap = 3,
		Test = 4,
		WRONGOPT
	};

	/// <summary>
	/// Prepare the game for playing on a randomly generated map.
	/// </summary>
	/// <param name="mapWidth">Width of the map</param>
	/// <param name="mapHeight">Height of the map</param>
	/// <param name="seed">Seed for the random generator</param>
	void PrepareGame();

	/// <summary>
	/// The game
	/// </summary>
	bool GameFrame();

	bool DebugFrame();

	/// <summary>
	/// Destroys the object from the game.
	/// </summary>
	/// <param name="target">Target to destroy</param>
	void DestroyObject(GameObject* target);

	Map* GetMap();

	MainCharacter* mainCharacter; 

	Exit** exits;

	/// <summary>
	/// Moves the given object to the specified target
	/// </summary>
	/// <param name="what">The object to move</param>
	/// <param name="target">The point where it should be</param>
	/// <returns>If the move was succesful</returns>
	bool MoveObject(GameObject* what, Point target);

	/// <summary>
	/// Calculates the distance between two points
	/// </summary>
	/// <param name="p1">Point 1</param>
	/// <param name="p2">Point 2</param>
	/// <returns>The distance between the two points</returns>
	static double Distance(Point p1, Point p2);

	/// <summary>
	/// Linear interpolation between two numbers
	/// </summary>
	/// <param name="x">Smaller number</param>
	/// <param name="y">Larger number</param>
	/// <param name="ratio">Ratio</param>
	/// <returns>The result of the interpolation</returns>
	static double LERP(int x, int y, double ratio);

	/// <summary>
	/// Ends the game at the next frame
	/// </summary>
	/// <param name="win">If the game was won or lost</param>
	void EndGame(bool win);

	/// <summary>
	/// Adds an object to the game
	/// </summary>
	/// <param name="what">The object</param>
	void AddGameObject(GameObject* what);

	GameObject** GetGameObjects() { return gameObjects; }

	int GetGameObjectCount() { return gameObjectsCount; }

	/// <summary>
	/// Determines if there is an unobstructed linear path between two points
	/// </summary>
	/// <param name="p1">Point 1</param>
	/// <param name="p2">Point 2</param>
	/// <returns>If there is an unobstructed linear path between the two points</returns>
	static bool LineOfSight(Point p1, Point p2);

	bool IsGameWon() { return gameWon; }

	/// <summary>
	/// Select all the gameObjects
	/// </summary>
	/// <typeparam name="T">Selector type</typeparam>
	/// <returns>A list of all the objects passing the selector</returns>
	template <class T>
	DLinkedList<T>* GetGameObjectsOfType();

	Trap** traps;
	int trapsCunt;

private:
	static Engine* enginePtr;

	/// <summary>
	/// Initialize pointer types
	/// </summary>
	void Init();

	/// <summary>
	/// A frame of the game. Every logic goes here
	/// </summary>
	/// <returns>If the game has ended</returns>
	bool Frame();

	Engine();

	Map* map;

	KeyInput* keyReader;

	DLinkedList<ITriggerable*>* triggerList;
	//ITriggerable** toTrigger;
	//int toTriggerCount; // TODO: Decide

	DLinkedList<GameObject*>* gameObjectsList; // During generation
	GameObject** gameObjects;
	int* updateDelay;
	int gameObjectsCount;

	DLinkedList<GameObject*>* deleteList; // Delete items at the end of the frame, before Clock

	Renderer* rendererPtr;

	/// <summary>
	/// Checks if the game should end
	/// </summary>
	/// <returns>If the game should end</returns>
	bool CheckExit();

	bool gameEnds;
	bool gameWon;
};

Engine* Engine::enginePtr = nullptr;


#endif
