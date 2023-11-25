#ifndef SENSOR_BATCH
#define SENSOR_BATCH

#include "SensorBatch.hpp"

SensorBatch::SensorBatch(GameObject* container, Map* map) : GameItem(container, map)
{
	renderImage = new char* [RENDER_HEIGHT];
	for (int i = 0; i < RENDER_HEIGHT; i++)
	{
		renderImage[i] = new char[RENDER_WIDTH];
		for (int j = 0; j < RENDER_WIDTH; j++)
		{
			renderImage[i][j] = ' ';
		}
	}
	lightSensorActive = true;
	geigerCounterActive = true;
	radiationTrapList = nullptr;
}

SensorBatch::~SensorBatch()
{
	for (int i = 0; i < RENDER_HEIGHT; i++)
	{
		delete[] renderImage[i];
	}
	delete[] renderImage;
	delete radiationTrapList;
}

char** SensorBatch::ProduceImage()
{
	for (int i = 0; i < RENDER_HEIGHT; i++)
	{
		for (int j = 0; j < RENDER_WIDTH; j++)
		{
			renderImage[i][j] = ' ';
		}
	}
	contentLine = 0;
	if (lightSensorActive)
	{
		bool found = false;
		// double distance = INT_MAX;
		Exit** exits = Engine::GetInstance()->exits;
		for (int i = 0; i < EXIT_COUNT; i++)
		{
			if (Engine::Distance(exits[i]->location, container->location) < LIGHT_SENSOR_RANGE && Engine::LineOfSight(exits[i]->location, container->location))
			{
				double distance = Engine::Distance(exits[i]->location, container->location);
				AddToOutputText("Direct light visible. Distance: " + std::to_string(distance));
				AddToOutputText("\tDirection: x: " + std::to_string((exits[i]->location.y - container->location.y) / distance) + " y: " + std::to_string(((exits[i]->location.x - container->location.x) / distance)));
			}
		}
	}

	if (geigerCounterActive)
	{
		if (radiationTrapList == nullptr)
		{
			radiationTrapList = Engine::GetInstance()->GetGameObjectsOfType<TrapRadiation*>();
		}
		float radPower = 0.0f;
		for (int i = 0; i < radiationTrapList->Count(); i++)
		{
			radiationTrapList->SeekToIndex(i);
			double dist = Engine::Distance(radiationTrapList->currentElement->data->location, container->location) + 0.001;
			if (dist <= RADIATION_RANGE )
			{
				radPower += 0.25 / (MATH_PI * 2 * dist * radiationTrapList->currentElement->data->GetActivity()) * 100000;
			}
		}
		if (radPower > 0)
		{
			AddToOutputText("Radiation detected! Activity: " + std::to_string(radPower));
		}
	}
	return renderImage;
}

bool SensorBatch::IsUpdateable()
{
	if (frameDelay <= 0)
	{
		frameDelay = DISPLAY_DELAY_MAX;
		return true;
	}
	--frameDelay;
	return false;
}

void SensorBatch::Trigger()
{
}

bool SensorBatch::Condition()
{
	return true;
}

void SensorBatch::AddToOutputText(std::string content)
{
	if (contentLine < RENDER_HEIGHT)
	{
		for (int i = 0; i < content.size() && i < RENDER_WIDTH; i++)
		{
			renderImage[contentLine][i] = content[i];
		}
		++contentLine;
	}
}



#endif // !SENSOR_BATCH

