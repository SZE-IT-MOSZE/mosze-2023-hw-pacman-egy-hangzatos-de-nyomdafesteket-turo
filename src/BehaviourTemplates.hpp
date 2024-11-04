#ifndef BEHAVIOUR_MOVEMENT_H
#define BEHAVIOUR_MOVEMENT_H

#include "Behaviour.hpp"


#define MAXDLEAY 500
#define MINDELAY 1

/// <summary>
/// Intended use: define possible movement patterns for the NPCs (moves randomly, towards the player, etc.)
/// </summary>
class BehaviourMovement : public Behaviour
{
public:
	BehaviourMovement(int delay);
	BehaviourMovement(BehaviourMovement& other);
	~BehaviourMovement();

	void* Update(GameObject* caller) override;

private:
	int delay;
	int maxDelay;
};

#define MAXVISION 20
#define MINVISION 5

/// <summary>
/// Intended use: Define a condition whether the move (and unmade BehaviourInteract) should be allowed to update
/// </summary>
class BehaviourVision : public Behaviour
{
public:
	BehaviourVision(int visionDistance);
	BehaviourVision(BehaviourVision& other);
	~BehaviourVision();

	void* Update(GameObject* caller) override;

private:
	int visionDistance;
};

/// <summary>
/// Factory method for the behaviour
/// </summary>
/// <param name="index">Unique index of the Behaviour class</param>
/// <param name="other">The original object to use as the template</param>
/// <returns>A copied behaviour</returns>
Behaviour* NewBehaviour(int index, Behaviour& other)
{
	switch (index)
	{
	case 0: return new BehaviourVision(dynamic_cast<BehaviourVision&>(other)); break;
	case 1: return new BehaviourMovement(dynamic_cast<BehaviourMovement&>(other)); break;
	// case 3:
	default: return nullptr; break;
	}
}

#endif // !BEHAVIOUR_MOVEMENT_H


