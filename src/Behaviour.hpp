#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include "GameObject.hpp"

/// <summary>
/// A base class for the behaviour of NPCs
/// </summary>
class Behaviour
{
public:
	Behaviour()
	{
	}
	Behaviour(Behaviour& other)
	{
		// Reserved
	}

	~Behaviour()
	{
	}
	virtual void* Update(GameObject* caller) = 0;
private:

};


#endif // !BEHAVIOUR_H
