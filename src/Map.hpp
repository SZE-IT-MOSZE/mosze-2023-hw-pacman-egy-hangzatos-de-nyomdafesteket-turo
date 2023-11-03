#ifndef MAP_H
#define MAP_H


#include "Tile.hpp"
#include "Engine.hpp"

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

	/// <summary>
	/// Pathfinds in the map bewteen begin and target. Should be used for in-room travel
	/// </summary>
	/// <param name="begin">Wehere the pathfinding should start from</param>
	/// <param name="target">Where the pathfinding should end</param>
	/// <returns>A linked list of points of the route</returns>
	DLinkedList<Point>* Pathfind(Point begin, Point target);

	/// <summary>
	/// Pathfinds in the map bewteen begin and target asynchronously. Should be used for in-room travel
	/// </summary>
	/// <param name="begin">Wehere the pathfinding should start from</param>
	/// <param name="target">Where the pathfinding should end</param>
	/// <returns>A linked list of points of the route</returns>
	DLinkedList<Point>* PathfindAsync(Point begin, Point target);

	/// <summary>
	/// Pathfinds in the logical map bewteen begin and target. Should be used for cross-room travel
	/// </summary>
	/// <param name="begin">Wehere the pathfinding should start from</param>
	/// <param name="target">Where the pathfinding should end</param>
	/// <returns>A linked list of points of the route</returns>
	DLinkedList<Point>* PathfindInLogicMap(Point begin, Point target);

	/// <summary>
	/// Pathfinds in the logical map bewteen begin and target asynchronously. Should be used for cross-room travel
	/// </summary>
	/// <param name="begin">Wehere the pathfinding should start from</param>
	/// <param name="target">Where the pathfinding should end</param>
	/// <returns>A linked list of points of the route</returns>
	DLinkedList<Point>* PathfindInLogicMapAsync(Point begin, Point target);



private:
	bool** baseMap;
	int width, height;

	bool** pathfindHelper;
	Tile*** fullMap;
	int fullWidth, fullHeight;

	/// <summary>
	/// Generates a cluster in the baseMap at a specified coordinate
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void GenerateCluster(int x, int y);

	/// <summary>
	/// Expands a walkable tile of the baseMap to the fullMap
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void GenerateRoom(int x, int y);

	/// <summary>
	/// Expands a non-walkable tile of the baseMap to the fullMap
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void GenerateWall(int x, int y);
};


#endif
