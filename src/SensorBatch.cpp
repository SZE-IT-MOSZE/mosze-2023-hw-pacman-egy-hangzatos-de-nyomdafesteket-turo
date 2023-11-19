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
}

SensorBatch::~SensorBatch()
{
	for (int i = 0; i < RENDER_HEIGHT; i++)
	{
		delete[] renderImage[i];
	}
	delete[] renderImage;
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
			if (Engine::Distance(exits[i]->location, container->location) < ROOM_WIDTH && Engine::LineOfSight(exits[i]->location, container->location))
			{
				double distance = Engine::Distance(exits[i]->location, container->location);
				AddToOutputText("Direct light visible. Distance: " + std::to_string(distance));
				AddToOutputText("\tDirection: x: " + std::to_string((exits[i]->location.y - container->location.y) / distance) + " y: " + std::to_string(((exits[i]->location.x - container->location.x) / distance)));
			}
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

