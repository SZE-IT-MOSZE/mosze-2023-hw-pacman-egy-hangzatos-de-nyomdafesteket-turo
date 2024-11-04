#include "src\Engine.hpp"
#include "src\Testing.cpp"

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
			std::cout << "Congratulation! You won the game!";
		}
		else
		{
			std::cout << "You lost! Unfortunate...";
		}
		std::cout << std::endl;
	}
	else if (option == Engine::MenuOptions::Test)
	{
		system("cls");
		ErrorObject* errorsSummary = new ErrorObject();
		bool (**testFunctions)(ErrorObject*) = Testing::GetTests();
		std::cout << "Begin testing: " << TEST_ITERATION << " iterations will be made" << std::endl;
		for (int i = 0; i < TESTCOUNT; i++)
		{
			testFunctions[i](errorsSummary);
		}
		free(testFunctions);
		if (errorsSummary->messages->Count() == 0)
		{
			std::cout << "No errors present!" << std::endl;
		}
		else
		{
			std::cout << "Errors present (count: " << errorsSummary->messages->Count() << "): Messages:" << std::endl;
			for (int i = 0; i < errorsSummary->messages->Count(); i++)
			{
				errorsSummary->messages->SeekToIndex(i);
				std::cout << errorsSummary->messages->currentElement->data << std::endl;
			}
		}
		delete errorsSummary;
	}
	delete Engine::GetInstance();
	int leak = _CrtDumpMemoryLeaks();
	// std::cout << leak << std::endl;
	Sleep(2000);
	system("pause");
	return 0;
}
