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
	void* tmp = behaviourStates[0]->Update(this);

	bool vision = *(bool*)tmp;
	delete tmp;
	if (vision)
	{
		tmp = behaviourStates[1]->Update(this);
		if (tmp == nullptr)
		{
			updateDelay = 0;
		}
		else
		{
			updateDelay = *(int*)tmp;
		}
		delete tmp;
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

void NonPlayableCharacter::Init()
{
	mainCharacter = engine->mainCharacter;
}


#endif // !NPC_BASE