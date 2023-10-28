#ifndef MAP_H
#define MAP_H


#include "Tile.hpp"

#define CLUSTER_SIZE 5
#define ROOM_WIDTH 10
#define ROOM_HEIGHT 6
#define DOOR_WIDTH 2

class Map
{
public:
	/// <summary>
	/// Generates a base map, simple bool matrix with a wall surrounding it and walls placed at random locations
	/// </summary>
	/// <param name="clusterCountWidth">The width of the labyrinth</param>
	/// <param name="clusterCountHeight">The height of the labyrinth</param>
	/// <param name="seed">Seed ofr random generation</param>
	void GenerateBaseMap(int clusterCountWidth, int clusterCountHeight, int seed = 1);

	/// <summary>
	/// Generates the full map, based on the base map
	/// </summary>
	void GenerateFullMap();

	Map();
	~Map();


	void DisplayMap();
	void DisplayFullMap();



private:
	bool** baseMap;
	int width, height;
	Tile*** tiles;
	void GenerateCluster(int x, int y);
	void GenerateRoom(int x, int y);
	void GenerateWall(int x, int y);
};


#endif
