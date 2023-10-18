#ifndef MAP
#define MAP

#include "Map.hpp"
#include <stdlib.h>

#ifdef DEBUG
#include <iostream>
#endif // DEBUG



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
	for (int i = x; i < x + ROOM_HEIGHT; i++)
	{
		for (int j = y; j < y + ROOM_WIDTH; j++)
		{
			if (i * j == 0 || i == x + ROOM_HEIGHT || j == y + ROOM_WIDTH)
			{
				tiles[i][j] = new Tile(Tile::TileType::Wall); // The edge of the matrix
			}
			else
			{
				tiles[i][j] = new Tile(Tile::TileType::Floor); // The "inside" of the matrix
			}

		}
	}
}

void Map::GenerateWall(int x, int y)
{
	for (int i = x; i < x + ROOM_HEIGHT; i++)
	{
		for (int j = y; j < y + ROOM_WIDTH; j++)
		{
			tiles[i][j] = new Tile(Tile::TileType::Wall);
		}
	}
}


void Map::GenerateBaseMap(int clusterCountWidth, int clusterCountHeight, int seed)
{
	srand(seed);
	this->width = clusterCountWidth * CLUSTER_SIZE;
	this->height = clusterCountHeight * CLUSTER_SIZE;
	baseMap = new bool* [height + 2];

	// Make matrix
	for (int i = 0; i < height + 2; i++)
	{
		baseMap[i] = new bool[width + 2];
		for (int j = 0; j < width + 2; j++)
		{
			if (i * j == 0 || i == height + 1 || j == width + 1)
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

void Map::GenerateFullMap()
{
	tiles = new Tile**[ROOM_HEIGHT * (height + 2)];
	for (int i = 0; i < height + 2; i++)
	{
		for (int j = 0; j < ROOM_HEIGHT; j++)
		{
			tiles[i * ROOM_HEIGHT + j] = new Tile * [ROOM_WIDTH * (width * 10 + 2)]; //ERROR: Access violation reading
		}

		for (int j = 0; j < width + 2; j++)
		{
			if (i * j == 0 || i == height + 1 || j == width + 1)
			{
				GenerateWall(i * ROOM_WIDTH, j * ROOM_HEIGHT); // The edge of the matrix
			}
			else
			{
				GenerateRoom(i * ROOM_WIDTH, j * ROOM_HEIGHT); // The "inside" of the matrix
			}
		}
	}
}

Map::Map()
{
}

Map::~Map()
{
}

#ifdef DEBUG


void Map::DisplayMap()
{
	for (int i = 0; i < height + 2; i++)
	{
		for (int j = 0; j < width + 2; j++)
		{
			if (baseMap[i][j])
			{
				std::cout << '.';
			}
			else
			{
				std::cout << '#';
			}

		}
		std::cout << std::endl;
	}
}

void Map::DisplayFullMap()
{
	for (int i = 0; i < (height)*ROOM_HEIGHT; i++)
	{
		for (int j = 0; j < (width)*ROOM_WIDTH; j++)
		{
			std::cout << tiles[i][i]->GetIcon();
		}
		std::cout << std::endl;
	}
}

#endif // DEBUG




#endif