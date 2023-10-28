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
		for (int j = y * ROOM_WIDTH; j < y * ROOM_WIDTH + ROOM_WIDTH; j++)
		{
			if (i == x * ROOM_HEIGHT || j == y * ROOM_WIDTH || i == x * ROOM_HEIGHT + ROOM_HEIGHT - 1 || j == y * ROOM_WIDTH + ROOM_WIDTH - 1)
			{
				tiles[i][j] = new Tile(Tile::TileType::Wall); // The edge of the matrix
			}
			else
			{
				tiles[i][j] = new Tile(Tile::TileType::Floor); // The "inside" of the matrix
			}
		}
	}
	// Open doors
	// UP
	if (baseMap[x - 1][y] && baseMap[x][y])
	{
		for (int i = 0; i < DOOR_WIDTH; i++)
		{
			// index:
			//	 [TOP of the room][middle of the room - offset of half door width + i]
			tiles[x * ROOM_HEIGHT][(y * ROOM_WIDTH + ROOM_WIDTH / 2) - DOOR_WIDTH / 2 + i]->SetTileType(Tile::TileType::Floor);
		}
	}
	// DOWN
	if (baseMap[x + 1][y] && baseMap[x][y])
	{
		for (int i = 0; i < DOOR_WIDTH; i++)
		{
			// index:
			//	 [BOTTOM of the room][middle of the room - offset of half door width + i]
			tiles[x * ROOM_HEIGHT + ROOM_HEIGHT - 1][(y * ROOM_WIDTH + ROOM_WIDTH / 2) - DOOR_WIDTH / 2 + i]->SetTileType(Tile::TileType::Floor);
		}
	}
	// LEFT
	if (baseMap[x][y - 1] && baseMap[x][y])
	{
		for (int i = 0; i < DOOR_WIDTH; i++)
		{
			// index:
			//	 [BOTTOM of the room][middle of the room - offset of half door width + i]
			tiles[x * ROOM_HEIGHT + ROOM_HEIGHT / 2 - DOOR_WIDTH / 2 + i][y * ROOM_WIDTH]->SetTileType(Tile::TileType::Floor);
		}
	}
	// RIGHT
	if (baseMap[x][y + 1] && baseMap[x][y])
	{
		for (int i = 0; i < DOOR_WIDTH; i++)
		{
			// index:
			//	 [BOTTOM of the room][middle of the room - offset of half door width + i]
			tiles[x * ROOM_HEIGHT + ROOM_HEIGHT / 2 - DOOR_WIDTH / 2 + i][y * ROOM_WIDTH + ROOM_WIDTH - 1]->SetTileType(Tile::TileType::Floor);
		}
	}
}

void Map::GenerateWall(int x, int y)
{
	for (int i = x * ROOM_HEIGHT; i < x * ROOM_HEIGHT + ROOM_HEIGHT; i++)
	{
		for (int j = y * ROOM_WIDTH; j < y * ROOM_WIDTH + ROOM_WIDTH; j++)
		{
			tiles[i][j] = new Tile(Tile::TileType::Wall);
		}
	}
}


void Map::GenerateFullMap()
{
	tiles = new Tile * *[ROOM_HEIGHT * height];
	for (int i = 0; i < ROOM_HEIGHT * height; i++)
	{
		tiles[i] = new Tile * [ROOM_WIDTH * width];
	}



	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// GenerateWall(i, j);
			if (!baseMap[i][j])
			{
#ifdef DEBUG
				std::cout << "Wall ";
#endif
				GenerateWall(i, j); // The edge of the matrix
			}
			else
			{
#ifdef DEBUG
				std::cout << "Room ";
#endif
				GenerateRoom(i, j); // The "inside" of the matrix
			}
		}
		std::cout << std::endl;
	}

	//	for (int i = 0; i < ROOM_HEIGHT * height; i++)
	//	{
	//		for (int j = i * ROOM_HEIGHT; j < i * ROOM_HEIGHT + ROOM_HEIGHT; j++)
	//		{
	//#ifdef DEBUG
	//			std::cout << j << std::endl;
	//#endif
	//			tiles[j] = new Tile * [ROOM_WIDTH * (width)];
	//		}
	//
	//		for (int j = i * ROOM_HEIGHT; j < i * ROOM_HEIGHT + ROOM_HEIGHT; j++)
	//		{
	//
	//			if (i * j == 0 || i == height - 1 || j == width - 1)
	//			{
	//				GenerateWall(i * ROOM_HEIGHT, j * ROOM_WIDTH); // The edge of the matrix
	//			}
	//			else
	//			{
	//				GenerateRoom(i * ROOM_HEIGHT, j * ROOM_WIDTH); // The "inside" of the matrix
	//			}
	//		}
	//	}
}

Map::Map()
{
	baseMap = nullptr;
	tiles = nullptr;
}

Map::~Map()
{
	for (int i = 0; i < height; i++)
	{
		delete baseMap[i];
	}
	delete[]baseMap;
	for (int i = 0; i < height * ROOM_HEIGHT; i++)
	{
		for (int j = 0; j < width * ROOM_WIDTH; j++)
		{
			delete tiles[i][j];
		}
		delete[] tiles[i];
	}
	delete[] tiles;

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
			std::cout << tiles[i][j]->GetIcon();
		}
		std::cout << std::endl;
	}
}






#endif