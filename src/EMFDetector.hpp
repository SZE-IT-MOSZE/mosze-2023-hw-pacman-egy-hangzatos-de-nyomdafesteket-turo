#ifndef SEISMOGRAPH_H
#define SEISMOGRAPH_H

#define _USE_MATH_DEFINES

#include <cmath>
#include <string>
#include "NPC.hpp"
#include "Engine.hpp"

// BIGGER RANGES ARE SAFE
#define EMF_RANGE (ROOM_WIDTH / 2)
#define EMF_DETECTION_DISTANCE (EMF_RANGE / 2)
#define EMF_UPDATE_DELAY 1
#define EMF_JITTER 0.2


/// <summary>
/// EMF detector, displaying the distance to the closest robot
/// </summary>
class EMFDetector : public IRenderImage, public GameItem
{
public:
	EMFDetector(GameObject* container, Map* map);

	bool IsUpdateable() override;
	char** ProduceImage() override;

	virtual void Trigger();
	virtual bool Condition();

	~EMFDetector();


private:
	char** renderImage;
	void*** previousMap;
	//int robotCount;
	// int detectDistance;
	int updateDelay;
};



#endif // !SEISMOGRAPH_H


