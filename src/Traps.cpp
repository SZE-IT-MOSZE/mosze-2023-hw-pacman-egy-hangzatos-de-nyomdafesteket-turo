#include "Traps.hpp"


TrapRadiation::TrapRadiation() : Trap()
{
	Init();
}
TrapRadiation::TrapRadiation(Engine* e) : Trap(e)
{
	Init();
}
TrapRadiation::TrapRadiation(Engine* e, Point position) : Trap(e, position)
{
	Init();
}

void TrapRadiation::Init()
{
	activity = rand();
}

TrapRadiation::~TrapRadiation()
{

}

float TrapRadiation::GetActivity()
{
	return activity;
}

int TrapRadiation::Update()
{
	double dist = engine->Distance(this->location, mainCharacter->location) + 0.001;
	if (dist <= RADIATION_RANGE / 2)
	{
		int number = rand() / dist;
		if (number >= JITTER_CHANCE)
		{
			switch (rand() % 4)
			{
				case 0: mainCharacter->StepLeft(); break;
				case 1: mainCharacter->StepUp(); break;
				case 2: mainCharacter->StepRight(); break;
				case 3: mainCharacter->StepDown(); break;
				default: break;
			}
		}
	}
	return 0;
}
