//#define DEBUG

#include "src\Engine.hpp"




#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef DEBUG

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
		std::cout << "Skip loading screen? [y/n]" << std::endl;
		char tmp;
		std::cin >> tmp;
		if (tmp == 'n' || tmp == 'N')
		{
			StartLoadingScreen(engine->GetGameObjectCount());
		}
		//Renderer::GetInstance()->DebugDisplay();

		bool exit = false;
		system("cls");
		while (!exit)
		{
			exit = engine->GameFrame();
			Sleep(100);
		}
		std::cout << std::endl;
		if (engine->IsGameWon())
		{
			std::cout << "Congratulation! You have won the game!";
		}
		else
		{
			std::cout << "You lost! Unfortunate...";
		}
		std::cout << std::endl;
	}
	delete Engine::GetInstance();
	std::cout << _CrtDumpMemoryLeaks();
	return 0;
}