#ifndef SEISMOGRAPH_H
#define SEISMOGRAPH_H

#include "Engine.hpp"

#define SEISMOGRAPH_RANGE (ROOM_HEIGHT - 2)
#define SEISMOGRAPH_SENSITIVITY RENDER_HEIGHT
#define SEISMOGRAPH_UPDATE_DELAY 5

class Seismograph : public IRenderImage, public GameItem
{
public:
	Seismograph(GameObject* container, Map* map);

	bool IsUpdateable() override;
	char** ProduceImage() override;

	virtual void Trigger();
	virtual bool Condition();

	~Seismograph();


private:
	char** renderImage;
	bool** previousMap;
	int changeCount;
	int updateDelay;
};



#endif // !SEISMOGRAPH_H


