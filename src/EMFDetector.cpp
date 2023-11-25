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
	std::string content = "EMF detector V 5.0";
	for (int i = 0; i < content.size() && i < RENDER_WIDTH; i++)
	{
		renderImage[0][i] = content[i];
	}
	content = "Detectable robots:";
	for (int i = 0; i < content.size() && i < RENDER_WIDTH; i++)
	{
		renderImage[1][i] = content[i];
	}
	renderImage[2][1] = '0';
	renderImage[2][2] = '-';
	content = std::to_string(EMF_CAPACITY);
	for (int i = 0; i < content.size() && i < RENDER_WIDTH; i++)
	{
		renderImage[2][3 + i] = content[i];
	}
	content = "High activity";
	for (int i = 0; i < content.size() && i < RENDER_WIDTH; i++)
	{
		renderImage[RENDER_HEIGHT - 1][RENDER_WIDTH / 4 - content.size() + i] = content[i];
	}
	content = "No activity";
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
				++robotCount;
			}
		}
	}

	// center the arrow

	Point begin{ RENDER_HEIGHT - 1, RENDER_WIDTH / 2 };
	int radius = RENDER_HEIGHT - 2;

	for (int i = 0; i < RENDER_HEIGHT; i++)
	{
		for (int j = RENDER_WIDTH / 2 - radius; j < RENDER_WIDTH / 2 + radius + 1; j++)
		{
			renderImage[i][j] = ' ';
		}
	}

	if (robotCount != 0)
	{
		float angleRatio;
		if (robotCount <= EMF_CAPACITY)
		{
			angleRatio = MATH_PI - MATH_PI * (1.0 * robotCount / EMF_CAPACITY);
		}
		else
		{
			angleRatio = MATH_PI;
		}

		double debugHeight = sin(angleRatio);
		double debugWidth = cos(angleRatio);

		// Make pointer
		for (float i = 0; i < radius; i += 0.1)
		{
			int x = round(begin.x - debugHeight * i);

			int y = round(begin.y - debugWidth * i);
			renderImage[x][y] = '#';
		}
	}
	else
	{
		for (float i = 0; i < radius; i += 1)
		{
			int y = RENDER_WIDTH / 2 + i;
			renderImage[begin.x][y] = '#';
		}
	}



	robotCount = 0;
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