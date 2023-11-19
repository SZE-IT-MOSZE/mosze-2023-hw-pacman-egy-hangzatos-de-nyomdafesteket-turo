#ifndef TRAPS_H
#define TRAPS_H

#include "Trap.hpp"
#include "Engine.hpp"

#define JITTER_CHANCE (RAND_MAX / 50)
#define RADIATION_RANGE 10
#define RADIATION_COUNT 1

class TrapRadiation : public Trap
{
public:
	TrapRadiation();
	TrapRadiation(Engine* e);
	TrapRadiation(Engine* e, Point position);
	~TrapRadiation();
	virtual void FirstUpdate() {}
	virtual int Update() override;
	virtual void LastUpdate() {}

private:

};





#endif // !TRAPS_H

