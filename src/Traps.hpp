#ifndef TRAPS_H
#define TRAPS_H

#include "Trap.hpp"
#include "Engine.hpp"

#define RADIATION_CHANCE RAND_MAX / 10 /* usage: rand() < CHANCE */
#define RADIATION_MULTIPLIER_PER_ROOM 1
#define JITTER_CHANCE (RAND_MAX / 2)
#define RADIATION_RANGE 10
#define RADIATION_COUNT 1
#define RADIATION_MAX 1000

class TrapRadiation : public Trap
{
public:
	TrapRadiation();
	TrapRadiation(Engine* e);
	TrapRadiation(Engine* e, Point position);
	virtual void Init() override;
	~TrapRadiation();
	float GetActivity();
	virtual bool IsDetectable(int sensorID) override { return true; }
	virtual void FirstUpdate() {}
	virtual int Update() override;
	virtual void LastUpdate() {}

private:
	float activity;
};





#endif // !TRAPS_H

