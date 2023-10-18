#ifndef MAP_H
#define MAP_H


#include "Tile.hpp"

#define CLUSTER_SIZE 5
#define ROOM_WIDTH 3
#define ROOM_HEIGHT 5

class Map
{
public:
	/// <summary>
	/// Generates a simple bool matrix with a wall surrounding it and walls placed at random locations
	/// </summary>
	/// <param name="clusterCountWidth">The width of the labyrinth</param>
	/// <param name="clusterCountHeight">The height of the labyrinth</param>
	/// <param name="seed">Seed ofr random generation</param>
	void GenerateBaseMap(int clusterCountWidth, int clusterCountHeight, int seed = 1);
	void GenerateFullMap();
	Map();
	~Map();

#ifdef DEBUG
	void DisplayMap();
	void DisplayFullMap();
#endif // DEBUG


private:
	bool** baseMap;
	int width, height;
	Tile*** tiles;
	void GenerateCluster(int x, int y);
	void GenerateRoom(int x, int y);
	void GenerateWall(int x, int y);
};


#endif
