#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Engine.hpp"

class GameObject : public IUpdateable // , public ITriggerable, public IRenderImage
{
public:
	GameObject();
	GameObject(Engine* e);
	GameObject(Engine* e, Point position);
	virtual ~GameObject();

	/// <summary>
	/// Step left on the map
	/// </summary>
	virtual bool StepLeft();

	/// <summary>
	/// Step up on the map
	/// </summary>
	virtual bool StepUp();

	/// <summary>
	/// Step right on the map
	/// </summary>
	virtual bool StepRight();

	/// <summary>
	/// Step down on the map
	/// </summary>
	virtual bool StepDown();

	/// <summary>
	/// Destroys the object. Use this instead of delete
	/// </summary>
	virtual void DestroyThis();
	Point location; // Location of this object
protected:
	Engine* engine; // QOL pointer to reduce acess time
};



#endif

