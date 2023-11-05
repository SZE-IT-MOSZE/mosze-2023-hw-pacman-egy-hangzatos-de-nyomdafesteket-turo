#ifndef ENGINE
#define ENGINE


#include "Engine.hpp"

#define SAY std::cout <<
#define ENDL std::endl


Engine::Engine()
{
	Init(); // Init used for later parametering of ctor
}

void Engine::PrepareGame()
{
	int width, height, seed;
	width = 20;
	height = 7;
	seed = 1;

	std::cout << "Map width (recommended: " << width << "): ";
	std::cin >> width;

	std::cout << "Map height (recommended: " << height << "): ";
	std::cin >> height;

	std::cout << "Map seed (recommended: " << seed << "): ";
	std::cin >> seed;

	map->GenerateBaseMap(width, height, seed);
	map->GenerateFullMap();
	map->GenerateGameObjects();
	// map->DisplayFullMap();
	// TODO: Generate objects, place player and exit
}

bool Engine::GameFrame()
{
	for (int i = 0; i < updateList->Count(); i++)
	{
		updateList->SeekToIndex(i);
		updateDelay->SeekToIndex(i);
	}
	return false;
}

bool Engine::DebugFrame()
{
	KeyInput::Update();
	mainCharacter->Update();
	rendererPtr->DebugDisplay();
	if (keyReader->GetActiveKeys()[5] == KeyInput::KeyName::Esc)
	{
		return true;
	}
	return false;
}

void Engine::DestroyObject(GameObject* target)
{
	// TODO: DLinkedList IndexOf
	// int index = updateList->IndexOf(target);
	// Move this after the game objects were updated
	//updateList->RemoveAt(index, true);
	//updateDelay->RemoveAt(index, true);
	deleteList->PushLast(target);
}

Map* Engine::GetMap()
{
	return map;
}

bool Engine::MoveObject(GameObject* what, Point target)
{
	// Check if space is available
	if (map->fullMap[target.x][target.y]->content == nullptr && map->fullMap[target.x][target.y]->Passable())
	{
		map->fullMap[what->location.x][what->location.y]->content = nullptr;
		what->location = target;
		map->fullMap[what->location.x][what->location.y]->content = what;
		return true;
	}
	return false;
}

int Engine::MainMenu()
{
	SAY "Robo survivor" << ENDL;
	SAY "Options:" << ENDL;
	/*
	* 		Quit = 0,
		PlayRandom = 1,
		LoadSavedMap = 2,
		CreateMap = 3
	*/
	SAY "0: Quit the game" << ENDL;
	SAY "1: Play Random map" << ENDL;
	SAY "2: Load Saved Map" << ENDL;
	SAY "3: Create Map" << ENDL;
	int ret;
	std::cin >> ret;
	while (ret < (int)Engine::MenuOptions::Quit || ret > (int)Engine::MenuOptions::CreateMap)
	{
		SAY "Invalid option. Again!" << ENDL;
		std::cin >> ret;
	}

	return ret;
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
	delete mainCharacter;
}

void Engine::Init()
{
	map = new Map(this);
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