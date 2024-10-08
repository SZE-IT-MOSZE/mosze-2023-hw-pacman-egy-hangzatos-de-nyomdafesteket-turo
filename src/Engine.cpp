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
	width = 7;
	height = 15;
	seed = 1;

	std::cout << "Map width (recommended: " << width << "): ";
	std::cin >> width;

	std::cout << "Map height (recommended: " << height << "): ";
	std::cin >> height;

	std::cout << "Map seed: ";
	std::cin >> seed;

	map->GenerateBaseMap(width, height, seed);
	map->GenerateFullMap();
	// map->DisplayMap();
	map->GenerateGameObjects();
	// map->DisplayFullMap();
	// 
	// TODO: move every gameobject into an array
	gameObjectsCount = gameObjectsList->Count();
	gameObjects = new GameObject * [gameObjectsCount];
	updateDelay = new int[gameObjectsCount];
	for (int i = 0; i < gameObjectsCount; i++)
	{
		gameObjectsList->SeekToIndex(i);
		gameObjects[i] = gameObjectsList->currentElement->data;
		updateDelay[i] = 0;
	}
	gameObjectsList->Empty();
}

bool Engine::GameFrame()
{
	KeyInput::Update(); // First and most important
	mainCharacter->Update();
	for (int i = 0; i < EXIT_COUNT; i++)
	{
		exits[i]->Update();
	}
	for (int i = 0; i < gameObjectsCount; i++)
	{
		if (Distance(mainCharacter->location, gameObjects[i]->location) <= UPDATE_DISTANCE)
		{
			if (updateDelay[i] <= 0)
			{
				updateDelay[i] = gameObjects[i]->Update();
			}
			else
			{
				updateDelay[i]--;
			}
		}
	}
	//rendererPtr->DebugDisplay();
	rendererPtr->Display();

	// rendererPtr.Dispaly(); // TODO

	//for (int i = 0; i < updateList->Count(); i++)
	//{
	//	updateDelayList->SeekToIndex(i);
	//	updateList->SeekToIndex(i);
	//	if (updateDelayList->currentElement->data <= 0)
	//	{
	//		updateDelayList->currentElement->data = updateList->currentElement->data->Update();
	//	}
	//	else
	//	{
	//		--updateDelayList->currentElement->data;
	//	}
	//}
	//for (int i = 0; i < gameObjectsCount; i++)
	//{
	//	if (Distance(mainCharacter->location, gameObjects[i]->location) <= UPDATE_DISTANCE)
	//	{
	//		updateList->PushLast(gameObjects[i]);
	//		updateDelayList->PushLast(0);
	//		isUpdatingGameObject[i] = true;
	//	}
	//	else if (isUpdatingGameObject[i])
	//	{
	//		int index = updateList->IndexOf(gameObjects[i]);
	//		updateList->RemoveAt(index);
	//		updateDelayList->RemoveAt(index);
	//		updateList->SeekToIndex(0);
	//		isUpdatingGameObject[i] = false;
	//	}
	//}

	return CheckExit();
}

bool Engine::DebugFrame()
{
	KeyInput::Update();
	for (int i = 0; i < EXIT_COUNT; i++)
	{
		exits[i]->Update();
	}
	mainCharacter->Update();
	rendererPtr->DebugDisplay();
	return CheckExit();
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
	if (/*map->fullMap[target.x][target.y]->GetContent() == nullptr &&*/ map->fullMap[target.x][target.y]->IsPassable())
	{
		map->fullMap[what->location.x][what->location.y]->SetContent(nullptr);
		//map->fullMap[what->location.x][what->location.y]->content = nullptr;
		what->location = target;
		//map->fullMap[what->location.x][what->location.y]->content = what;
		map->fullMap[what->location.x][what->location.y]->SetContent(what);
		return true;
	}
	return false;
}

double Engine::Distance(Point p1, Point p2)
{
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

double Engine::LERP(int x, int y, double ratio)
{
	if (x <= y)
	{		
		return 1.0 * x * (1.0 - ratio) + (y * ratio);
	}
	else
	{
		return LERP(y, x, ratio);
	}
}

void Engine::EndGame(bool win)
{
	gameEnds = true;
	gameWon = win;
}

bool Engine::Frame()
{
	return false;
}

void Engine::AddGameObject(GameObject* what)
{
	map->fullMap[what->location.x][what->location.y]->SetContent(what);
	this->gameObjectsList->PushLast(what);
}

bool Engine::LineOfSight(Point p1, Point p2)
{
	bool LOS = false;

	double length = Engine::Distance(p1, p2);

	// Normalized vector from locX, loxY to i, j
	double dirX = (p1.x - p2.x) / (length * 1.0);
	double dirY = (p1.y - p2.y) / (length * 1.0);

	// Currently checked tile
	double currentX, currentY;

	for (double k = 0; k < length /*&& visibleTile[i][j] == false*/; k += LOS_CHECK_PRECISION)
	{
		currentX = p2.x + k * dirX;
		currentY = p2.y + k * dirY;

		int x = round(currentX);
		int y = round(currentY);

		if (Point{ x, y } == p2)
		{
			continue;
		}
		// Check if there is something on the current tile
		LOS = Engine::GetInstance()->GetMap()->fullMap[x][y]->IsPassable();

		if (LOS == false)
		{
			break; // There is something, we can't look behind it
		}
	}

	return LOS;
}

bool Engine::CheckExit()
{
	return gameEnds || keyReader->GetActiveKeys()[5] == KeyInput::KeyName::Esc;
}

int Engine::MainMenu()
{


	SAY "Game is recommended to be played with character size of 20, full screen" << ENDL;
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
	SAY "4: Run tests" << ENDL;
	int ret;
	std::cin >> ret;
	while (ret < (int)Engine::MenuOptions::Quit || ret >= (int)Engine::MenuOptions::WRONGOPT)
	{
		SAY "Invalid option. Again!" << ENDL;
		std::cin >> ret;
	}
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	return ret;
}

Engine::~Engine()
{
	for (int i = 0; i < gameObjectsCount; i++)
	{
		delete gameObjects[i];
	}
	delete[] updateDelay;
	delete[] gameObjects;
	triggerList->Empty(true);
	gameObjectsList->Empty(true);
	deleteList->Empty(true);

	delete triggerList;
	delete gameObjectsList;
	delete map;
	delete keyReader;
	delete rendererPtr;
	delete deleteList;
	delete mainCharacter;

	for (int i = 0; i < EXIT_COUNT; i++)
	{
		delete exits[i];
	}
	delete[] exits;
	enginePtr = nullptr;
}

void Engine::Init()
{
	map = new Map(this);
	keyReader = KeyInput::GetInstance();
	triggerList = new DLinkedList<ITriggerable*>();
	gameObjectsList = new DLinkedList<GameObject*>();
	rendererPtr = Renderer::GetInstance();
	Renderer::engine = this;
	deleteList = new DLinkedList<GameObject*>();
	exits = new Exit * [EXIT_COUNT];
	for (int i = 0; i < EXIT_COUNT; i++)
	{
		exits[i] = nullptr;
	}
}

Engine* Engine::GetInstance()
{
	if (enginePtr == nullptr)
	{
		enginePtr = new Engine();
	}
	return enginePtr;
}

template<class T>
DLinkedList<T>* Engine::GetGameObjectsOfType()
{
	DLinkedList<T>* list = new DLinkedList<T>();

	for (int i = 0; i < gameObjectsCount; i++)
	{
		if (dynamic_cast<T>(gameObjects[i]))
		{
			list->PushLast(dynamic_cast<T>(gameObjects[i]));
		}
	}

	return list;
}


#endif // !ENGINE