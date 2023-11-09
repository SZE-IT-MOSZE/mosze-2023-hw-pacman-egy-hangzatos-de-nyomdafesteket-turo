#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include "GameObject.hpp"

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
	virtual int Update(GameObject* caller) = 0;
private:

};


#endif // !BEHAVIOUR_H
