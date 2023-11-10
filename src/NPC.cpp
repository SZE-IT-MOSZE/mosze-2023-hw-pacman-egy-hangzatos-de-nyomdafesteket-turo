#ifndef NPC_BASE
#define NPC_BASE


#include "NPC.hpp"

NonPlayableCharacter::NonPlayableCharacter()
{
	behaviourStates = new Behaviour * [BEHAVIOUR_COUNT];
	for (int i = 0; i < BEHAVIOUR_COUNT; i++)
	{
		behaviourStates[i] = nullptr;
	}
}

NonPlayableCharacter::NonPlayableCharacter(Behaviour** behaviours)
{
	this->behaviourStates = behaviours;
}

NonPlayableCharacter::NonPlayableCharacter(Behaviour** behaviours, Point position)
{
	this->behaviourStates = behaviours;
	this->location = position;
}

NonPlayableCharacter::~NonPlayableCharacter()
{
	for (int i = 0; i < BEHAVIOUR_COUNT; i++)
	{
		delete behaviourStates[i];
	}
	delete[] behaviourStates;
}

void NonPlayableCharacter::FirstUpdate()
{
}

int NonPlayableCharacter::Update()
{
	//for (int i = 0; i < BEHAVIOUR_COUNT; i++)
	//{
	//	behaviourStates[i]->Update(this);
	//}
	bool vision = behaviourStates[0]->Update(this);
	if (vision)
	{
		updateDelay = behaviourStates[1]->Update(this);
	}
	return updateDelay;
}

void NonPlayableCharacter::LastUpdate()
{
}

void NonPlayableCharacter::SetUpdateDelay(int delay)
{
	this->updateDelay = delay;
}


#endif // !NPC_BASE