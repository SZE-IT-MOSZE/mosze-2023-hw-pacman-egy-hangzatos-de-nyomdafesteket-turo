//#define DEBUG

#include "src\Engine.hpp"
#include <iostream>


#ifdef DEBUG


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#endif // DEBUG

int main()
{
	Map* e = new Map();
	e->GenerateBaseMap(10, 3);
	e->DisplayMap();
	e->GenerateFullMap();
	e->DisplayFullMap();
	// Engine* e = Engine::GetInstance();
	// int option = e->MainMenu();
	delete e;
	std::cout << _CrtDumpMemoryLeaks();
	return 0;
}