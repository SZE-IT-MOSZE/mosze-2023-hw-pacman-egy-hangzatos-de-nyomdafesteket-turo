#include "src\Engine.hpp"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


int main()
{
	Engine* engine = Engine::GetInstance();
	int option = engine->MainMenu();
	if (option == (int)Engine::MenuOptions::PlayRandom)
	{
		engine->PrepareGame();
		std::cout << "Skip intro screen? [y/n]" << std::endl;
		char tmp;
		std::cin >> tmp;
		if (tmp == 'n' || tmp == 'N')
		{
			StartLoadingScreen(engine->GetGameObjectCount());
		}
		//Renderer::GetInstance()->DebugDisplay();

		bool exit = false;
		system("cls");
		Clock* gameClock = new Clock();
		gameClock->Start();
		while (!exit)
		{
			exit = engine->GameFrame();
			gameClock->Wait();
		}
		delete gameClock;
		system("cls");
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
	int leak = _CrtDumpMemoryLeaks();
	// std::cout << leak << std::endl;
	Sleep(2000);
	system("pause");
	return leak;
}
