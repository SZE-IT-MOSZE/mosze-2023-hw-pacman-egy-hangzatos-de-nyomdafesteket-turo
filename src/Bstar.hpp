#ifndef BSTAR_H
#define BSTAR_H

#include "DLinkedList.hpp"
#include "Point.cpp"
#include <iostream>

/// <summary>
/// Finds the shortest path between two points using BStar
/// </summary>
/// <param name="mtx">The layout of the labyrinth (false for walls, true for pathways)</param>
/// <param name="width">The width of the labyrinth</param>
/// <param name="height">The height of the labyrinth</param>
/// <param name="begin">Where the pathfinding should begin from</param>
/// <param name="target">Where the pathfinder should find the path</param>
/// <returns>A linked list of each step, a nullptr if path is not possible</returns>
DLinkedList<Point>* BStar(bool** mtx, int height, int width, Point begin, Point target);


#endif // !BSTAR_H


