//#define DEBUG

#include "src\Engine.hpp"

#ifdef DEBUG


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#endif // DEBUG

int main()
{

	Engine* e = Engine::GetInstance();
	int option = e->MainMenu();
	delete e;
	std::cout << _CrtDumpMemoryLeaks();
	return 0;
}