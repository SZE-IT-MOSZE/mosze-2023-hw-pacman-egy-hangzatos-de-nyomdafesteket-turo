#ifndef MAP
#define MAP

#include "Map.hpp"
#include <stdlib.h>
#include <iostream>


#ifdef DEBUG
#endif // DEBUG



void Map::GenerateBaseMap(int clusterCountWidth, int clusterCountHeight, int seed)
{
	srand(seed);
	this->width = clusterCountWidth * CLUSTER_SIZE + 2;
	this->height = clusterCountHeight * CLUSTER_SIZE + 2;
	baseMap = new bool* [height];

	// Make matrix
	for (int i = 0; i < height; i++)
	{
		baseMap[i] = new bool[width];
		for (int j = 0; j < width; j++)
		{
			if (i * j == 0 || i == height - 1 || j == width - 1)
			{
				baseMap[i][j] = false; // The edge of the matrix
			}
			else
			{
				baseMap[i][j] = true; // The "inside" of the matrix
			}
		}
	}

	for (int i = 0; i < clusterCountHeight; i++)
	{
		for (int j = 0; j < clusterCountWidth; j++)
		{
			// For every possible cluster, generate walls
			GenerateCluster(i * CLUSTER_SIZE + 1, j * CLUSTER_SIZE + 1);
		}
	}
}


void Map::GenerateCluster(int x, int y)
{
	int cSize = CLUSTER_SIZE + 1;

	// Build walls
	for (int i = x; i < x + cSize; i++)
	{
		baseMap[i][y + cSize / 2 - 1] = false;
	}
	for (int i = y; i < y + cSize; i++)
	{
		baseMap[x + cSize / 2 - 1][i] = false;
	}

	// Open pathways

	baseMap[x + rand() % 2][y - 1 + cSize / 2] = true;
	baseMap[x + rand() % 2 + 3][y - 1 + cSize / 2] = true;
	baseMap[x - 1 + cSize / 2][y + rand() % 2] = true;
	baseMap[x - 1 + cSize / 2][y + rand() % 2 + 3] = true;

	// This can cause isolated cells
	if (rand() % 2 == 0)
	{
		for (int i = x; i < x + cSize; i++)
		{
			baseMap[i][y] = false;
		}
		baseMap[x + rand() % 2][y] = true;
		baseMap[x + rand() % 2 + 3][y] = true;
	}
	else
	{
		for (int i = x; i < x + cSize; i++)
		{
			baseMap[i][y + cSize - 2] = false;
		}
		baseMap[x + rand() % 2][y + cSize - 2] = true;
		baseMap[x + rand() % 2 + 3][y + cSize - 2] = true;
	}

}

void Map::GenerateRoom(int x, int y)
{
	for (int i = x * ROOM_HEIGHT; i < x * ROOM_HEIGHT + ROOM_HEIGHT; i++)
	{
		// std::cout << i << ": ";
		for (int j = y * ROOM_WIDTH; j < y * ROOM_WIDTH + ROOM_WIDTH; j++)
		{
			// std::cout << j << " ";
			if (i == x * ROOM_HEIGHT || j == y * ROOM_WIDTH || i == x * ROOM_HEIGHT + ROOM_HEIGHT - 1 || j == y * ROOM_WIDTH + ROOM_WIDTH - 1)
			{
				fullMap[i][j] = new Tile(Tile::TileType::Wall); // The edge of the matrix
			}
			else
			{
				fullMap[i][j] = new Tile(Tile::TileType::Floor); // The "inside" of the matrix
			}
		}
		// std::cout << std::endl;
	}
	// Open doors
	// UP
	if (baseMap[x - 1][y] && baseMap[x][y])
	{
		for (int i = 0; i < DOOR_WIDTH; i++)
		{
			// index:
			//	 [TOP of the room][middle of the room - offset of half door width + i]
			fullMap[x * ROOM_HEIGHT][(y * ROOM_WIDTH + ROOM_WIDTH / 2) - DOOR_WIDTH / 2 + i]->SetTileType(Tile::TileType::Floor);
		}
	}
	// DOWN
	if (baseMap[x + 1][y] && baseMap[x][y])
	{
		for (int i = 0; i < DOOR_WIDTH; i++)
		{
			// index:
			//	 [BOTTOM of the room][middle of the room - offset of half door width + i]
			fullMap[x * ROOM_HEIGHT + ROOM_HEIGHT - 1][(y * ROOM_WIDTH + ROOM_WIDTH / 2) - DOOR_WIDTH / 2 + i]->SetTileType(Tile::TileType::Floor);
		}
	}
	// LEFT
	if (baseMap[x][y - 1] && baseMap[x][y])
	{
		for (int i = 0; i < DOOR_WIDTH; i++)
		{
			// index:
			//	 [BOTTOM of the room][middle of the room - offset of half door width + i]
			fullMap[x * ROOM_HEIGHT + ROOM_HEIGHT / 2 - DOOR_WIDTH / 2 + i][y * ROOM_WIDTH]->SetTileType(Tile::TileType::Floor);
		}
	}
	// RIGHT
	if (baseMap[x][y + 1] && baseMap[x][y])
	{
		for (int i = 0; i < DOOR_WIDTH; i++)
		{
			// index:
			//	 [BOTTOM of the room][middle of the room - offset of half door width + i]
			fullMap[x * ROOM_HEIGHT + ROOM_HEIGHT / 2 - DOOR_WIDTH / 2 + i][y * ROOM_WIDTH + ROOM_WIDTH - 1]->SetTileType(Tile::TileType::Floor);
		}
	}
}

void Map::GenerateWall(int x, int y)
{
	for (int i = x * ROOM_HEIGHT; i < x * ROOM_HEIGHT + ROOM_HEIGHT; i++)
	{
		// std::cout << i << ": ";
		for (int j = y * ROOM_WIDTH; j < y * ROOM_WIDTH + ROOM_WIDTH; j++)
		{
			// std::cout << j << " ";
			fullMap[i][j] = new Tile(Tile::TileType::Wall);
		}
		// std::cout << std::endl;
	}
}


void Map::GenerateFullMap()
{
	fullMap = new Tile * *[ROOM_HEIGHT * height];
	pathfindHelper = new bool* [ROOM_HEIGHT * height];

	for (int i = 0; i < ROOM_HEIGHT * height; i++)
	{
		fullMap[i] = new Tile * [ROOM_WIDTH * width];
		pathfindHelper[i] = new bool[ROOM_WIDTH * width];
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (!baseMap[i][j])
			{
				// std::cout << "Wall ";

				GenerateWall(i, j); // The edge of the matrix
			}
			else
			{
				// std::cout << "Room ";

				GenerateRoom(i, j); // The "inside" of the matrix
			}
		}
		// std::cout << std::endl;
	}

}

void Map::GenerateGameObjects()
{
	int totalSize = ROOM_HEIGHT * height * ROOM_WIDTH * width;
	float percentage = 0.0;
	bool forcedPlace = false;

	// Generate random walls
	percentage = 0.07;
	int changesMade = 0;
	int x, y;
	while (changesMade < percentage * totalSize)
	{
		x = rand() % (ROOM_HEIGHT * height);
		// std::cout << x << std::endl;
		y = rand() % (ROOM_WIDTH * width);
		if (pathfindHelper[x][y])
		{
			pathfindHelper[x][y] = false;
			fullMap[x][y]->SetTileType(Tile::TileType::Wall);
			changesMade++;
		}
	}

	// Select starting room
	x = height - 2;
	do
	{
		y = rand() % (width - 2);
	} while (!baseMap[x][y]);
	int startX, startY;
	startX = x;
	startY = y;
	// Clear out starting room

	for (int i = x * ROOM_HEIGHT + 1; i < x * ROOM_HEIGHT + ROOM_HEIGHT - 1; i++)
	{
		for (int j = y * ROOM_WIDTH + 1; j < y * ROOM_WIDTH + ROOM_WIDTH - 1; j++)
		{
			fullMap[i][j]->SetTileType(Tile::TileType::Floor);
			pathfindHelper[i][j] = true;
		}
	}

	if (baseMap[x - 1][y]) // Room UP starting room is available
	{
		for (int i = 0; i < DOOR_WIDTH; i++)
		{
			fullMap[x * ROOM_HEIGHT][(y * ROOM_WIDTH + ROOM_WIDTH / 2) - DOOR_WIDTH / 2 + i]->SetTileType(Tile::TileType::Floor);
			fullMap[x * ROOM_HEIGHT - 1][(y * ROOM_WIDTH + ROOM_WIDTH / 2) - DOOR_WIDTH / 2 + i]->SetTileType(Tile::TileType::Floor);
		}
	}
	if (baseMap[x][y - 1]) // Left
	{
		for (int i = 0; i < DOOR_WIDTH; i++)
		{
			fullMap[x * ROOM_HEIGHT + ROOM_HEIGHT / 2 - DOOR_WIDTH / 2 + i][y * ROOM_WIDTH]->SetTileType(Tile::TileType::Floor);
			fullMap[x * ROOM_HEIGHT + ROOM_HEIGHT / 2 - DOOR_WIDTH / 2 + i][y * ROOM_WIDTH - 1]->SetTileType(Tile::TileType::Floor);
		}
	}
	if (baseMap[x][y + 1]) // Right
	{
		for (int i = 0; i < DOOR_WIDTH; i++)
		{
			fullMap[x * ROOM_HEIGHT + ROOM_HEIGHT / 2 - DOOR_WIDTH / 2 + i][y * ROOM_WIDTH + ROOM_WIDTH - 1]->SetTileType(Tile::TileType::Floor);
			fullMap[x * ROOM_HEIGHT + ROOM_HEIGHT / 2 - DOOR_WIDTH / 2 + i][y * ROOM_WIDTH + ROOM_WIDTH]->SetTileType(Tile::TileType::Floor);
		}
	}

	// Select starting position

	x = 1 + x * ROOM_HEIGHT + rand() % (ROOM_HEIGHT - 2);
	y = 1 + y * ROOM_WIDTH + rand() % (ROOM_WIDTH - 2);

	engine->mainCharacter = new MainCharacter(engine, Point{ x, y });
	Renderer::GetInstance()->mainCharacter = engine->mainCharacter;

	fullMap[x][y]->content = engine->mainCharacter; // TODO: Make automatic 

	// Select exit position
	for (int i = 0; i < EXIT_COUNT; i++)
	{
		x = 1;
		do
		{
			y = rand() % (width - 2);
		} while (!baseMap[x][y]);
		int offsetX, offsetY;

		do
		{
			offsetX = 1 + rand() % (ROOM_HEIGHT - 2);
			offsetY = 1 + rand() % (ROOM_WIDTH - 2);
		} while (fullMap[x + offsetX][y + offsetY]->content != nullptr);
		engine->exits[i] = new Exit(engine, Point{ x * ROOM_HEIGHT + offsetX , y * ROOM_WIDTH + offsetY });
		fullMap[x * ROOM_HEIGHT + offsetX][y * ROOM_WIDTH + offsetY]->content = engine->exits[i];
	}

	// Place NPCs
	int behaviourCount = 4;
	Behaviour** behaviourTemplates = new Behaviour * [behaviourCount]; // TODO: rework
	behaviourTemplates[0] = new BehaviourVision(MINVISION);
	behaviourTemplates[1] = new BehaviourVision(MAXVISION);
	behaviourTemplates[2] = new BehaviourMovement(MAXDLEAY);
	behaviourTemplates[3] = new BehaviourMovement(MINDELAY);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (baseMap[i][j] && (i != startX || j != startY))
			{
				for (int k = 0; k < NPC_MULTIPLIER_PER_ROOM; k++)
				{
					if (rand() < NPC_CHANCE)
					{
						int offsetX, offsetY;

						do
						{
							offsetX = 1 + rand() % (ROOM_HEIGHT - 2);
							offsetY = 1 + rand() % (ROOM_WIDTH - 2);
						} while (fullMap[x + offsetX][y + offsetY]->content != nullptr);

						Behaviour** tmp = new Behaviour * [BEHAVIOUR_COUNT];

						tmp[0] = NewBehaviour(0, *behaviourTemplates[0 + rand() % 2]);
						tmp[1] = NewBehaviour(1, *behaviourTemplates[2 + rand() % 2]);

						NonPlayableCharacter* npc = new NonPlayableCharacter(tmp, Point{ i * ROOM_HEIGHT + offsetX, j * ROOM_WIDTH + offsetY });

						engine->AddGameObject(npc);
					}
				}
			}
		}
	}
	for (int i = 0; i < behaviourCount; i++)
	{
		delete behaviourTemplates[i];
	}
	delete[] behaviourTemplates;






	// After objects are placed
	for (int i = 0; i < height * ROOM_HEIGHT; i++)
	{
		for (int j = 0; j < width * ROOM_WIDTH; j++)
		{
			pathfindHelper[i][j] = fullMap[i][j]->Passable();
		}
	}

}

Map::Map()
{
	baseMap = nullptr;
	fullMap = nullptr;
	pathfindHelper = nullptr;
	engine = nullptr;
}
Map::Map(Engine* e)
{
	baseMap = nullptr;
	fullMap = nullptr;
	pathfindHelper = nullptr;
	this->engine = e;
}

Map::~Map()
{
	for (int i = 0; i < height; i++)
	{
		delete baseMap[i];
	}
	delete[] baseMap;

	for (int i = 0; i < height * ROOM_HEIGHT; i++)
	{
		delete pathfindHelper[i];
		for (int j = 0; j < width * ROOM_WIDTH; j++)
		{
			delete fullMap[i][j];
		}
		delete[] fullMap[i];
	}
	delete[] pathfindHelper;
	delete[] fullMap;
}


void Map::DisplayMap()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (baseMap[i][j])
			{
				std::cout << '1';
			}
			else
			{
				std::cout << '0';
			}

		}
		std::cout << std::endl;
	}
}

void Map::DisplayFullMap()
{
	for (int i = 0; i < height * ROOM_HEIGHT; i++)
	{
		for (int j = 0; j < width * ROOM_WIDTH; j++)
		{
			std::cout << fullMap[i][j]->GetIcon();
		}
		std::cout << std::endl;
	}
}

DLinkedList<Point>* Map::Pathfind(Point begin, Point target)
{
	return BStar(pathfindHelper, height * ROOM_HEIGHT, width * ROOM_WIDTH, begin, target);
}

DLinkedList<Point>* Map::PathfindInLogicMap(Point begin, Point target)
{
	return BStar(baseMap, height, width, begin, target);
}

#endif