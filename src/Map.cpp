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

void Map::GenerateBaseMap(int clusterCountWidth, int clusterCountHeight, int seed)
{
	srand(seed);
	this->width = clusterCountWidth * CLUSTER_SIZE;
	this->height = clusterCountHeight * CLUSTER_SIZE;
	baseMap = new bool* [height + 2];
	for (int i = 0; i < height + 2; i++)
	{
		baseMap[i] = new bool[width + 2];
		for (int j = 0; j < width + 2; j++)
		{
			if (i * j == 0 || i == height + 1 || j == width + 1)
			{
				baseMap[i][j] = false;
			}
			else
			{
				baseMap[i][j] = true;
			}
		}
	}

	//#ifdef DEBUG
	//	std::cout << std::endl;
	//	Map::DisplayMap();
	//#endif

	for (int i = 0; i < clusterCountHeight; i++)
	{
		for (int j = 0; j < clusterCountWidth; j++)
		{
			GenerateCluster(i * CLUSTER_SIZE + 1, j * CLUSTER_SIZE + 1);
		}
	}
	//GenerateCluster(4, 1);
	//GenerateCluster(1, 4);
	//GenerateCluster(4, 4);


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

#endif // DEBUG




#endif