#ifndef BEHAVIOUR_TEMPLATES
#define BEHAVIOUR_TEMPLATES

#include "BehaviourTemplates.hpp"

BehaviourMovement::BehaviourMovement(int maxDelay) : Behaviour()
{
	delay = 0;
	this->maxDelay = maxDelay;
}

BehaviourMovement::BehaviourMovement(BehaviourMovement& other)
{
	this->delay = 0;
	this->maxDelay = other.maxDelay;
}

BehaviourMovement::~BehaviourMovement()
{
}

int BehaviourMovement::Update(GameObject* caller)
{
	if (delay <= 0)
	{
		delay = rand() % maxDelay;
		switch (rand() % 4)
		{
		case 0: caller->StepLeft(); break;
		case 1: caller->StepUp(); break;
		case 2: caller->StepRight(); break;
		case 3: caller->StepDown(); break;
		default: break;
		}
	}
	else
	{
		--delay;
	}
	return 0;
}


BehaviourVision::BehaviourVision(int visionDistance) : Behaviour()
{
	this->visionDistance = visionDistance;
}

BehaviourVision::BehaviourVision(BehaviourVision& other)
{
	this->visionDistance = other.visionDistance;
}

BehaviourVision::~BehaviourVision()
{
}

int BehaviourVision::Update(GameObject* caller)
{
	if (Engine::Distance(caller->location, Engine::GetInstance()->mainCharacter->location) <= visionDistance)
	{
		return 1;
	}
	return 0;
}



#endif // !BEHAVIOUR_TEMPLATES