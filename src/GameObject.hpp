#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Engine.hpp"

class GameObject : public IUpdateable // , public ITriggerable, public IRenderImage
{
public:
	GameObject() = delete; // Abstract
	virtual ~GameObject();

	/// <summary>
	/// Step left on the map
	/// </summary>
	virtual void StepLeft();

	/// <summary>
	/// Step up on the map
	/// </summary>
	virtual void StepUp();

	/// <summary>
	/// Step right on the map
	/// </summary>
	virtual void StepRight();

	/// <summary>
	/// Step down on the map
	/// </summary>
	virtual void StepDown();

	/// <summary>
	/// Destroys the object. Use this instead of delete
	/// </summary>
	virtual void DestroyThis();
private:
	Point location; // Location of this object
	Engine* engine; // QOL pointer to reduce acess time
};



#endif

