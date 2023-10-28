#ifndef TRIGGERABLE_H
#define TRIGGERABLE_H

__interface ITriggerable
{
	virtual void Trigger() = 0;
	virtual bool Condition() = 0;
};

#endif