//#define DEBUG

#include "src\Engine.hpp"


#ifdef DEBUG


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#endif // DEBUG



int main()
{
	Engine* engine = Engine::GetInstance();
	int option = engine->MainMenu();
	if (option == (int)Engine::MenuOptions::Quit)
	{
		delete Engine::GetInstance();
		std::cout << _CrtDumpMemoryLeaks();
		return 0;
	}
	else if (option == (int)Engine::MenuOptions::PlayRandom)
	{		
		engine->PrepareGame();
		Renderer::GetInstance()->DebugDisplay();
		bool exit = false;
		system("cls");
		while (!exit)
		{
			exit = engine->DebugFrame();
			Sleep(100);
		}
	}
	delete Engine::GetInstance();
	std::cout << _CrtDumpMemoryLeaks();
	return 0; 
}