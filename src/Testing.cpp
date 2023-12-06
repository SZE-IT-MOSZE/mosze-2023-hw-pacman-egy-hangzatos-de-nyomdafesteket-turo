#ifndef TESTING
#define TESTING

#include "Engine.hpp"

#define TEST_ITERATION 100
#define TESTCOUNT 3

class ErrorObject
{
public:
	ErrorObject()
	{
		messages = new DLinkedList<std::string>();
	}

	~ErrorObject()
	{
		messages->Empty();
		delete messages;
	}

	void AddErrorMessage(std::string msg)
	{
		messages->PushLast(msg);
	}

	DLinkedList<std::string>* messages;
private:
};

class Testing
{
public:
	Testing() = delete;

	static bool(**GetTests())(ErrorObject*)
	{
		void* tmp = calloc(TESTCOUNT, sizeof(bool(*)()));
		bool (**tests)(ErrorObject*) = (bool(**)(ErrorObject*))tmp;
		// bool (**tests)() = (bool(**)())calloc(TESTCOUNT, sizeof(bool(*)())); // syntax error? watafak?
		tests[0] = &IsEngineSingleton;
		tests[1] = &AreEngineFunctionsAccurate;
		tests[2] = &IsClockAdaptive;
		return tests;
	}

	static bool IsEngineSingleton(ErrorObject* error)
	{
		std::cout << "Testing engine integrity..." << std::endl;
		bool errorPresent = false;
		Engine* base = Engine::GetInstance();
		for (int i = 0; i < TEST_ITERATION; i++)
		{
			if (base != Engine::GetInstance())
			{
				std::cout << "Engine is not singleton" << std::endl;
				errorPresent = true;
			}
		}
		return !errorPresent;
	}

	static bool AreEngineFunctionsAccurate(ErrorObject* error)
	{
		std::cout << "Testing engine functions..." << std::endl;
		bool errorPresent = false;
		for (int i = 0; i < TEST_ITERATION; i++)
		{
			Point p = Point{ rand() - RAND_MAX / 2, rand() - RAND_MAX / 2 };
			double distance = sqrt(p.x * p.x + p.y * p.y);
			if (abs(Engine::Distance(p, Point{ 0, 0 }) - distance) >= 0.0001)
			{
				error->AddErrorMessage("Range is inaccurate, with the parameters: " + std::to_string(p.x) + "; " + std::to_string(p.y));
				errorPresent = true;
			}
		}
		// system("cls");
		std::cout << "Testing main menu function. Please select an option below..." << std::endl;
		int option = Engine::GetInstance()->MainMenu();
		if (option < (int)Engine::MenuOptions::Quit || option >= (int)Engine::MenuOptions::WRONGOPT)
		{
			error->AddErrorMessage("Main menu returned illegal option: " + std::to_string(option));
		}
		return !errorPresent;
	}

	static bool IsClockAdaptive(ErrorObject* error)
	{
		std::cout << "Testing clock..." << std::endl;
		int targetFramerate = 5;
		bool errorPresent = false;
		Clock* c = new Clock();
		c->Start();
		HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD pos = GetConsoleCursorPosition(output);
		std::cout.flush();
		for (int i = 0; i < TEST_ITERATION; i++)
		{
			int time1 = c->GetTimeSinceEpoch();
			switch (i % 4)
			{
				case 0:
					SAY '|';
					break;

				case 1:
					SAY '/';
					break;
				case 2:
					SAY '-';
					break;
				case 3:
					SAY '\\';
					break;
				default:
					break;
			}
			SetConsoleCursorPosition(output, pos);
			Sleep(i % 50);
			c->Wait(targetFramerate);
			// Calculate the difference of ACTUAL time passed and time by Wait()
			long unsigned int time2 = c->GetTimeSinceEpoch();
			int debug = time2 - time1;
			if (abs((debug - 1000 / targetFramerate) * 1.0) > 3 /* ms */)
			{
				error->AddErrorMessage("Clock was inaccurate by " + std::to_string(debug - 1000 / targetFramerate) + " ms");
				errorPresent = true;
			}
		}
		delete c;
		return errorPresent;
	}

private:

};




#endif // !TESTING
