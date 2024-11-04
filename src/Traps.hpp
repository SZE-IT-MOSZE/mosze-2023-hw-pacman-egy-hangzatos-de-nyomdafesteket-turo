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

/// <summary>
/// A trap that resembles a radioactive field
/// </summary>
class TrapRadiation : public Trap
{
public:
	TrapRadiation();
	TrapRadiation(Engine* e);
	TrapRadiation(Engine* e, Point position);
	virtual void Init() override;
	~TrapRadiation();
	float GetActivity();

	/// <summary>
	/// Unfinished: Decides if this trap is detectable by the specified sensor
	/// </summary>
	/// <param name="sensorID">The ID of the sensor (Should be reworked to dynamic_cast<>)</param>
	/// <returns>If this trap is detectable by the specified sensor</returns>
	virtual bool IsDetectable(int sensorID) override { return true; }
	virtual void FirstUpdate() {}
	virtual int Update() override;
	virtual void LastUpdate() {}

private:
	float activity;
};





#endif // !TRAPS_H

