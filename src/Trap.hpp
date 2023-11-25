#ifndef TRAP_H
#define TRAP_H

class Engine;

#include "GameObject.hpp"
#include "Engine.hpp"


class Trap : public GameObject
{
public:
	Trap() : GameObject()
	{
		Init();
	}
	Trap(Engine* e) : GameObject(e)
	{
		Init();
	}
	Trap(Engine* e, Point position) : GameObject(e, position)
	{
		Init();
	}
	virtual ~Trap() {}

	virtual bool StepLeft() override { return false; }
	virtual bool StepUp() override { return false; }
	virtual bool StepRight() override { return false; }
	virtual bool StepDown() override { return false; }

	virtual void FirstUpdate() = 0;
	virtual int Update() = 0;
	virtual void LastUpdate() = 0;
	virtual bool IsDetectable(int sensorID) = 0;
protected:
	MainCharacter* mainCharacter;
	virtual void Init() override;

};

#endif // !TRAP_H
