#ifndef SEISMOGRAPH
#define SEISMOGRAPH


#include "Seismograph.hpp"

Seismograph::Seismograph(GameObject* container, Map* map) : GameItem(container, map)
{
	renderImage = new char* [RENDER_HEIGHT];
	for (int i = 0; i < RENDER_HEIGHT; i++)
	{
		renderImage[i] = new char[RENDER_WIDTH];
		for (int j = 0; j < RENDER_WIDTH; j++)
		{
			renderImage[i][j] = 'T';
		}
	}
	previousMap = new bool* [SEISMOGRAPH_RANGE];
	for (int i = 0; i < SEISMOGRAPH_RANGE; i++)
	{
		previousMap[i] = new bool[SEISMOGRAPH_RANGE];
		for (int j = 0; j < SEISMOGRAPH_RANGE; j++)
		{
			previousMap[i][j] = false;
		}
	}
	updateDelay = SEISMOGRAPH_UPDATE_DELAY;
}

bool Seismograph::IsUpdateable()
{
	if (updateDelay <= 0)
	{
		updateDelay = SEISMOGRAPH_UPDATE_DELAY;
		return true;
	}
	--updateDelay;

	for (int i = 0; i < SEISMOGRAPH_RANGE; i++)
	{
		for (int j = 0; j < SEISMOGRAPH_RANGE; j++)
		{
			Tile* item = map->fullMap[container->location.x + (i - SEISMOGRAPH_RANGE / 2)][container->location.y + (j - SEISMOGRAPH_RANGE / 2)];
			int debug = container->location.x + (i - SEISMOGRAPH_RANGE / 2);
			debug = container->location.y + (j - SEISMOGRAPH_RANGE / 2);
			//if (!((item->GetContent() == nullptr) && (previousMap[i][j] == false) || (item->GetContent() != nullptr) && (previousMap[i][j] == true))) // Map has changed
			//{
			//	++changeCount;
			//}

			if (previousMap[i][j] != item->IsPassable())
			{
				++changeCount;
			}

			previousMap[i][j] = item->IsPassable();

			//if (item->GetContent() == nullptr && previousMap[i][j] == true)
			//{
			//	++changeCount;
			//}
			//if (item->GetContent() == nullptr)
			//{
			//	previousMap[i][j] = false;
			//}
			//else
			//{
			//	previousMap[i][j] = true;
			//}
			// previousMap[i][j] = item->GetContent() != nullptr;
		}
	}
	return false;
}

char** Seismograph::ProduceImage()
{
	if (changeCount > 0)
	{
		renderImage[0][0] = 'A';
	}
	else
	{
		renderImage[0][0] = 'B';
	}

	changeCount = 0;
	return renderImage;
}

void Seismograph::Trigger()
{
}

bool Seismograph::Condition()
{
	return false;
}

Seismograph::~Seismograph()
{
	for (int i = 0; i < RENDER_HEIGHT; i++)
	{
		delete[] renderImage[i];
	}
	delete[] renderImage;
	for (int i = 0; i < SEISMOGRAPH_RANGE; i++)
	{
		delete[] previousMap[i];
	}
	delete[] previousMap;
}

#endif // !SEISMOGRAPH