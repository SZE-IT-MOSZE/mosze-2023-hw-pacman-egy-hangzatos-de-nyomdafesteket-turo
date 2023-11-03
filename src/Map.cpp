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
	for (int i = x; i < x + cSize; i++)
	{
		baseMap[i][y] = false;
	}
	baseMap[x + rand() % 2][y] = true;
	baseMap[x + rand() % 2 + 3][y] = true;

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
				std::cout << "Wall ";

				GenerateWall(i, j); // The edge of the matrix
			}
			else
			{
				std::cout << "Room ";

				GenerateRoom(i, j); // The "inside" of the matrix
			}
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < height * ROOM_HEIGHT; i++)
	{
		for (int j = 0; j < width * ROOM_WIDTH; j++)
		{
			pathfindHelper[i][j] = fullMap[i][j]->Passable();
		}
	}
	// Yes, I could make this more efficient, but this way, the code is more simpler
}

Map::Map()
{
	baseMap = nullptr;
	fullMap = nullptr;
	pathfindHelper = nullptr;
}

Map::~Map()
{
	for (int i = 0; i < height; i++)
	{
		delete baseMap[i];
		delete pathfindHelper[i];
	}
	delete[] pathfindHelper;
	delete[] baseMap;

	for (int i = 0; i < height * ROOM_HEIGHT; i++)
	{
		for (int j = 0; j < width * ROOM_WIDTH; j++)
		{
			delete fullMap[i][j];
		}
		delete[] fullMap[i];
	}
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