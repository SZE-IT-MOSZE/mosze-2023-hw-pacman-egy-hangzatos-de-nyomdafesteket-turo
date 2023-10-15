#define DEBUG


#include "src\DDelegate.hpp"
#include "src\Map.hpp"
#include "src\LoadingScreen.cpp"



int main()
{
	StartLoadingScreen();
	DDelegate<void>* d = new DDelegate<void>();
	Map* m = new Map();
	m->GenerateBaseMap(10, 5, 3 + 1);
	m->DisplayMap();
	delete m;
	//delete d;
	return 0;
}