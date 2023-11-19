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

TrapRadiation::~TrapRadiation()
{

}

int TrapRadiation::Update()
{
	if (engine->Distance(this->location, mainCharacter->location) <= RADIATION_RANGE)
	{
		if (rand() <= JITTER_CHANCE)
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
