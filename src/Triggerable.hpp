#ifndef TRIGGERABLE_H
#define TRIGGERABLE_H

__interface ITriggerable
{
	/// <summary>
	/// One time call function
	/// </summary>
	virtual void Trigger() = 0;

	/// <summary>
	/// Condition for the trigger
	/// </summary>
	/// <returns>If the condition is met</returns>
	virtual bool Condition() = 0;
};

#endif