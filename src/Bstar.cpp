#ifndef BSTAR
#define BSTAR

#include "Bstar.hpp"

/// <summary>
/// Finds the shortest path between two points using BStar
/// </summary>
/// <param name="mtx">The layout of the labyrinth (false for walls, true for pathways)</param>
/// <param name="width">The width of the labyrinth</param>
/// <param name="height">The height of the labyrinth</param>
/// <param name="begin">Where the pathfinding should begin from</param>
/// <param name="target">Where the pathfinder should find the path</param>
/// <returns>A linked list of each step, a nullptr if path is not possible</returns>
DLinkedList<Point>* BStar(bool** mtx, int width, int height, Point begin, Point target)
{
	/*
	*	BStar is a pathfinding algorithm created by D, Kálmán, in 2018
	*	Worst cae performance is O(N * N), but heavily depends on the ratio of walls and pathways
	*	If the pathways are 'thin', performance converges to O(N), where N is the length of the shortest path between point A and B
	*	The more walls the better
	*	Shortest route guaranteed
	*	
	*	Explanation:
	*	Imagine pouring sand into an infinitely tall labyrinth from the top of the target point
	*	Once the sand reaches "your feet", the point where you want to start, you just need to climb upwards
	*	
	*	Logic of this function:
	*	Create a numeric matrix based on the labyrinth provided. Create it with a 0 wall aound every side
	*	Start pouring the sand in on one end, continously checking if it has reached the starting point
	*	If there is no more space for sand to be poured in, the route is not possible
	*	When the sand reached the starting point, climb only upwards and mark the steps	
	*/

	bool found = false;

	DLinkedList<Point>* path = new DLinkedList<Point>(); // The result
	DLinkedList<Point>* plusOne = new DLinkedList<Point>(); // Cell selector
	plusOne->PushLast(Point{ target.x + 1, target.y + 1 });

	DLinkedList<Point>* newCells = new DLinkedList<Point>(); // Helper

	// Convert the labyrinth to an int matrix

	int** labyrinth = (int**)calloc(height + 2, sizeof(int*)); // calloc is used so the elements are 0 by default

	for (int i = 0; i < height + 2; i++)
	{
		labyrinth[i] = (int*)calloc(width + 2, sizeof(int)); // calloc is used for similar reason
	}

	for (int i = 1; i < height + 1; i++)
	{
		for (int j = 1; j < width + 1; j++)
		{
			if (mtx[i - 1][j - 1])
			{
				labyrinth[i][j] = 1;
			}
		}
	}


	// Main searching loop
	while (!found)
	{

		// Increment the tiles
		for (int i = 0; i < plusOne->Count(); i++)
		{
			plusOne->SeekToIndex(i);
			Point item = plusOne->currentElement->data; // Reduce memory access time (Yes, I know cache exists)
			++labyrinth[item.x][item.y];
		}

		// Identify cells next to the pile
		for (int i = 0; i < plusOne->Count(); i++)
		{
			plusOne->SeekToIndex(i);
			Point item = plusOne->currentElement->data; // Reduce memory access time

			// UP
			if (labyrinth[item.x - 1][item.y] == 1)
			{
				newCells->PushLast({ item.x - 1, item.y });
			}

			// DOWN
			if (labyrinth[item.x + 1][item.y] == 1)
			{
				newCells->PushLast({ item.x + 1, item.y });
			}

			// LEFT
			if (labyrinth[item.x][item.y - 1] == 1)
			{
				newCells->PushLast({ item.x, item.y - 1 });
			}

			// RIGHT
			if (labyrinth[item.x][item.y + 1] == 1)
			{
				newCells->PushLast({ item.x, item.y + 1 });
			}
		}


		// Check if there are no more possible routes
		if (newCells->Count() == 0)
		{
			for (int i = 0; i < height + 2; i++)
			{
				free(labyrinth[i]);
			}
			free(labyrinth);
			path->Empty(true);
			delete path;
			plusOne->Empty(true);
			delete plusOne;
			newCells->Empty(true);
			delete newCells;
			return nullptr; // Path is not possible
		}

		// Clear duplicates and check if target is reached
		{
			Point* tmp = new Point[newCells->Count()]; // Reduce indexing time
			int tmpLen = 0;
			for (int i = 0; i < newCells->Count(); i++)
			{
				newCells->SeekToIndex(i);
				Point item = newCells->currentElement->data; // Reduce memory access time
				if (item == Point{ begin.x + 1, begin.y + 1 }) // Check if the target is reached
				{
					found = true;
					break;
				}

				// Target is not reached, check duplicates and add them to the pile
				bool once = true; 
				for (int i = 0; i < tmpLen; i++)
				{
					if (tmp[i] == item)
					{
						once = false;
						break;
					}
				}
				if (once)
				{
					tmp[tmpLen] = item; // C6386: Buffer overrun; ???
					tmpLen++;
					plusOne->PushLast(item);
				}
			}
			newCells->Empty(true); // Reuse
			delete[] tmp; // Recycle
		}
	}

	// Path is certain
	// Traceback
	path->PushLast(begin);
	// Check for a tile higher than our current position
	while (path->lastElement->data != target)
	{
		Point item = path->lastElement->data; // Reduce memory access time
		// UP
		if (labyrinth[item.x + 1 - 1][item.y + 1] > labyrinth[item.x + 1][item.y + 1])
		{
			item.x -= 1;
			path->PushLast(item);
		}
		// DOWN
		else if (labyrinth[item.x + 1 + 1][item.y + 1] > labyrinth[item.x + 1][item.y + 1])
		{
			item.x += 1;
			path->PushLast(item);
		}
		// LEFT
		else if (labyrinth[item.x + 1][item.y + 1 - 1] > labyrinth[item.x + 1][item.y + 1])
		{
			item.y -= 1;
			path->PushLast(item);
		}
		// RIGHT
		else if (labyrinth[item.x + 1][item.y + 1 + 1] > labyrinth[item.x + 1][item.y + 1])
		{
			item.y += 1;
			path->PushLast(item);
		}
	}
	// Path is complete
	
	// Cleanup
	for (int i = 0; i < height + 2; i++)
	{
		free(labyrinth[i]);
	}
	free(labyrinth);
	plusOne->Empty(true);
	delete plusOne;
	newCells->Empty(true);
	delete newCells;

	return path;
}




#endif // !BSTAR