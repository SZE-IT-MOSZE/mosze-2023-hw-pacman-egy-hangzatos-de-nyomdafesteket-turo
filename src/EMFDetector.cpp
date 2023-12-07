#ifndef SEISMOGRAPH
#define SEISMOGRAPH


#include "EMFDetector.hpp"



EMFDetector::EMFDetector(GameObject* container, Map* map) : GameItem(container, map)
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

	// TERRIBLE PATTERN INCOMING
	std::string content = "EMF detector V 5.187.4636";
	for (int i = 0; i < content.size() && i < RENDER_WIDTH; i++)
	{
		renderImage[0][i] = content[i];
	}
	content = "Manufacturer: MOSZE Software Ltd. ; Hardware serial number: " + std::to_string(rand());
	for (int i = 0; i < content.size() && i < RENDER_WIDTH; i++)
	{
		renderImage[1][i] = content[i];
	}
	content = "Parameters: ";
	for (int i = 0; i < content.size() && i < RENDER_WIDTH; i++)
	{
		renderImage[2][i] = content[i];
	}
	content = "Power consumption: 12V, 3W";
	for (int i = 0; i < content.size() && i < RENDER_WIDTH; i++)
	{
		renderImage[3][3 + i] = content[i];
	}
	content = "Effective range: " + std::to_string(EMF_DETECTION_DISTANCE);
	for (int i = 0; i < content.size() && i < RENDER_WIDTH; i++)
	{
		renderImage[4][3 + i] = content[i];
	}
	content = "Minimal detectable flux density: 0.00002 T";
	for (int i = 0; i < content.size() && i < RENDER_WIDTH; i++)
	{
		renderImage[4][3 + i] = content[i];
	}
	content = "0 mGauss";
	for (int i = 0; i < content.size() && i < RENDER_WIDTH; i++)
	{
		renderImage[RENDER_HEIGHT - 1][RENDER_WIDTH / 4 - content.size() + i] = content[i];
	}
	content = "400+ mGauss";
	for (int i = 0; i < content.size() && i < RENDER_WIDTH; i++)
	{
		renderImage[RENDER_HEIGHT - 1][3 * RENDER_WIDTH / 4 + i + 1] = content[i];
	}
	previousMap = new void** [EMF_RANGE];
	for (int i = 0; i < EMF_RANGE; i++)
	{
		previousMap[i] = new void* [EMF_RANGE];
		for (int j = 0; j < EMF_RANGE; j++)
		{
			previousMap[i][j] = nullptr;
		}
	}
	updateDelay = EMF_UPDATE_DELAY;
}

bool EMFDetector::IsUpdateable()
{
	if (updateDelay <= 0)
	{
		updateDelay = EMF_UPDATE_DELAY;
		return true;
	}
	--updateDelay;

	return false;
}

char** EMFDetector::ProduceImage()
{
	int distance = EMF_DETECTION_DISTANCE;
	for (int i = 0; i < EMF_RANGE; i++)
	{
		for (int j = 0; j < EMF_RANGE; j++)
		{
			int indexX = container->location.x + (i - EMF_RANGE / 2);
			int indexY = container->location.y + (j - EMF_RANGE / 2);
			if (map->height * ROOM_HEIGHT <= indexX || indexX < 0)
			{
				continue;
			}
			if (map->width * ROOM_WIDTH <= indexY || indexY < 0)
			{
				continue;
			}
			Tile* item = map->fullMap[indexX][indexY];
			if (dynamic_cast<NonPlayableCharacter*>(item->GetContent()))
			{
				NonPlayableCharacter* npc = dynamic_cast<NonPlayableCharacter*>(item->GetContent());
				double dist = Engine::Distance(npc->location, container->location);
				if (dist < distance)
				{
					distance = dist;
				}
			}
		}
	}

	// center the arrow

	Point begin{ RENDER_HEIGHT - 1, RENDER_WIDTH / 2 };
	int radius = RENDER_HEIGHT - 2;

	//for (int i = 0; i < RENDER_HEIGHT; i++)
	for (int i = RENDER_HEIGHT - 1; i >= RENDER_HEIGHT * (12.0 / 25.0); i--)
	{
		for (int j = RENDER_WIDTH / 2 - radius; j < RENDER_WIDTH / 2 + radius + 1; j++)
		{
			renderImage[i][j] = ' ';
		}
	}
	float angleRatio = (MATH_PI - MATH_PI * (1.0 * distance / EMF_DETECTION_DISTANCE));
	angleRatio += sin(rand()) * (EMF_JITTER - 1.0 * EMF_JITTER / 2);
	if (angleRatio < 0)
	{
		angleRatio = 0;
	}
	else if (angleRatio > MATH_PI)
	{
		angleRatio = 1;
	}
	double debugHeight = sin(angleRatio) * (12.0 / 25.0); // yes, I measured the size of the display
	double debugWidth = cos(angleRatio);

	// Make pointer
	for (float i = 0; i < radius; i += 0.1)
	{
		int x = round(begin.x - debugHeight * i);

		int y = round(begin.y - debugWidth * i);
		renderImage[x][y] = '#';
	}

	return renderImage;
}

void EMFDetector::Trigger()
{
}

bool EMFDetector::Condition()
{
	return false;
}

EMFDetector::~EMFDetector()
{
	for (int i = 0; i < RENDER_HEIGHT; i++)
	{
		delete[] renderImage[i];
	}
	delete[] renderImage;
	for (int i = 0; i < EMF_RANGE; i++)
	{
		delete[] previousMap[i];
	}
	delete[] previousMap;
}

#endif // !SEISMOGRAPH