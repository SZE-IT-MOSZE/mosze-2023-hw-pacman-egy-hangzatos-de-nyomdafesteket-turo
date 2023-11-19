#ifndef SENSOR_BATCH_H
#define SENSOR_BATCH_H

#include "GameItem.hpp"
#include "Engine.hpp"
#include <iostream>
#include <string>

#define DISPLAY_DELAY_MAX 20

class SensorBatch: public GameItem, public IRenderImage
{
public:
	SensorBatch(GameObject* container, Map* map);
	~SensorBatch();

	char** ProduceImage() override;
	bool IsUpdateable() override;

	virtual void Trigger();
	virtual bool Condition();

private:
	
	void AddToOutputText(std::string content);
	int contentLine;
	//char** outputText;
	char** renderImage;

	bool lightSensorActive;

	int frameDelay;
};



#endif // !SENSOR_BATCH_H




