#ifndef BSTAR_H
#define BSTAR_H

#include "DLinkedList.hpp"
#include "Point.cpp"
#include <iostream>


DLinkedList<Point>* BStar(bool** mtx, int width, int height, Point begin, Point target);


#endif // !BSTAR_H


