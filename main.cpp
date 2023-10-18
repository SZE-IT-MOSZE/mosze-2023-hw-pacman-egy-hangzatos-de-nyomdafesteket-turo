#define DEBUG


#include "src\DDelegate.hpp"
#include "src\Map.hpp"
#include "src\LoadingScreen.cpp"
#include "src\Point.cpp"



int main()
{
	// StartLoadingScreen();
	DDelegate<void>* d = new DDelegate<void>();
	Map* m = new Map();

	m->GenerateBaseMap(1, 1, 1);
	m->DisplayMap();
	m->GenerateFullMap();
	m->DisplayFullMap();
	delete m;
	//delete d;
	return 0;
}