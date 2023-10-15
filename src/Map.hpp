#ifndef MAP_H
#define MAP_H


// #include "Tile.hpp"

#define CLUSTER_SIZE 5

class Map
{
public:
	void GenerateBaseMap(int clusterCountWidth, int clusterCountHeight, int seed = 1);
	void GenerateFullMap();
	Map();
	~Map();

#ifdef DEBUG
	void DisplayMap();
#endif // DEBUG


private:
	bool** baseMap;
	int width, height;
	void GenerateCluster(int x, int y);
};


#endif
