#ifndef BEHAVIOUR_MOVEMENT_H
#define BEHAVIOUR_MOVEMENT_H

#include "Behaviour.hpp"

class BehaviourMovement : public Behaviour
{
public:
	BehaviourMovement(int delay);
	BehaviourMovement(BehaviourMovement& other);
	~BehaviourMovement();

	int Update(GameObject* caller) override;

private:
	int delay;
	int maxDelay;
};

class BehaviourVision : public Behaviour
{
public:
	BehaviourVision(int visionDistance);
	BehaviourVision(BehaviourVision& other);
	~BehaviourVision();

	int Update(GameObject* caller) override;

private:
	int visionDistance;
};

Behaviour* NewBehaviour(int index, Behaviour& other)
{
	switch (index)
	{
	case 0: return new BehaviourMovement(dynamic_cast<BehaviourMovement&>(other)); break;
	case 1: return new BehaviourVision(dynamic_cast<BehaviourVision&>(other)); break;
	// case 3:
	default: return nullptr; break;
	}
}

#endif // !BEHAVIOUR_MOVEMENT_H

