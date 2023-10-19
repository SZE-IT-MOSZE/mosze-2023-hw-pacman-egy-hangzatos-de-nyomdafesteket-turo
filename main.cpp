#define DEBUG


#include "src\DDelegate.hpp"
#include "src\Map.hpp"
#include "src\LoadingScreen.cpp"
#include "src\Point.cpp"

#ifdef DEBUG


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#endif // DEBUG

int main()
{
	// StartLoadingScreen();
	// DDelegate<void>* d = new DDelegate<void>();
	Map* m = new Map();

	m->GenerateBaseMap(2, 2, 1);
	m->DisplayMap();
	m->GenerateFullMap();
	m->DisplayFullMap();
	delete m;
	// delete d;

#ifdef DEBUG
	std::cout << _CrtDumpMemoryLeaks();
#endif // DEBUG

	return 0;
}