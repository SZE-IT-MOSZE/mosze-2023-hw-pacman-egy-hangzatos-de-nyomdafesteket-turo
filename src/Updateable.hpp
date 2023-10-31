#ifndef UPDATEABLE_H
#define UPDATEABLE_H

__interface IUpdateable
{
public:
	/// <summary>
	/// Called by the engine at the first frame of this object's existance
	/// </summary>
	virtual void FisrtUpdate() = 0;

	/// <summary>
	/// Called every frame
	/// </summary>
	/// <returns>How many frames should be skipped before caling this function again</returns>
	virtual int Update() = 0;

	/// <summary>
	/// Called right before this object is about to be destroyed
	/// </summary>
	virtual void LastUpdate() = 0;
};

#endif