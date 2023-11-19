#ifndef LIDAR_CPP
#define LIDAR_CPP

#include "LIDAR.hpp"

LIDAR::LIDAR(GameObject* container, Map* map) : GameItem(container, map)
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
	visibleTile = new bool* [ROOM_HEIGHT];
	for (int i = 0; i < ROOM_HEIGHT; i++)
	{
		visibleTile[i] = new bool[ROOM_WIDTH];
		for (int j = 0; j < ROOM_WIDTH; j++)
		{
			visibleTile[i][j] = false;
		}
	}
}

LIDAR::~LIDAR()
{
	for (int i = 0; i < RENDER_HEIGHT; i++)
	{
		delete[] renderImage[i];
	}
	delete[] renderImage;
	for (int i = 0; i < ROOM_HEIGHT; i++)
	{
		delete[] visibleTile[i];
	}
	delete[] visibleTile;
}

char** LIDAR::ProduceImage()
{
	int locX = container->location.x;
	int locY = container->location.y;

	int roomX = locX - locX % ROOM_HEIGHT;
	int roomY = locY - locY % ROOM_WIDTH;

	// Raycasting


	for (int i = 0; i < ROOM_HEIGHT; i++)
	{
		for (int j = 0; j < ROOM_WIDTH; j++)
		{
			// visibleTile[i][j] = false;

			visibleTile[i][j] = Engine::LineOfSight(Point{ roomX + i, roomY + j }, container->location);

		}
	}

	// Room width and room height might not match the render width and height
	// This centers the produced image to the render panel
	int offsetX = (RENDER_HEIGHT - ROOM_HEIGHT) / 2;
	int offsetY = (RENDER_WIDTH - ROOM_WIDTH) / 2;

	for (int i = 0; i < ROOM_HEIGHT; i++)
	{
		for (int j = 0; j < ROOM_WIDTH; j++)
		{
			if (visibleTile[i][j])
				// if (checked[i][j])
			{
				renderImage[offsetX + i][offsetY + j] = ' ';
			}
			else
			{
				renderImage[offsetX + i][offsetY + j] = '#';
			}
		}
	}
	// To see where the player is
	renderImage[offsetX + locX % ROOM_HEIGHT][offsetY + locY % ROOM_WIDTH] = 'P';

	return renderImage;
}

bool LIDAR::IsUpdateable()
{
	return true;
}

bool LIDAR::Condition()
{
	return false;
}
void LIDAR::Trigger()
{
}

#endif // !LIDAR

/*
	Broken LIDAR script?:

	int roomX = container->location.x - container->location.x % ROOM_HEIGHT;
	int roomY = container->location.y - container->location.y % ROOM_WIDTH;

	//int offsetX = container->location.x % ROOM_HEIGHT;
	//int offsetY = container->location.y % ROOM_WIDTH;

	int locX = container->location.x;
	int locY = container->location.y;

	// Raycasting

	for (int i = 0; i < 360; i++) // TODO: Change to different number to make it faster
	{
		for (int j = 1; j < range; j++)
		{
			int x, y;
			x = locX + round(sin(i * 3.14 / 180) + j);
			y = locY + round(cos(i * 3.14 / 180) + j);
			if (x < roomX || x > roomX + ROOM_HEIGHT || y < roomY || y > roomY + ROOM_WIDTH)
			{
				break;
			}
			if (map->fullMap[x][y]->content == nullptr && map->fullMap[x][y]->Passable())
			{
				visibleTile[x % ROOM_HEIGHT][y % ROOM_WIDTH] = true;
			}
			else
			{
				visibleTile[x % ROOM_HEIGHT][y % ROOM_WIDTH] = false;
			}
		}
	}
	int offsetX = (RENDER_HEIGHT - ROOM_HEIGHT) / 2;
	int offsetY = (RENDER_WIDTH - ROOM_WIDTH) / 2;
	for (int i = 0; i < ROOM_HEIGHT; i++)
	{
		for (int j = 0; j < ROOM_WIDTH; j++)
		{
			if (visibleTile[i][j])
			{
				renderImage[offsetX + i][offsetY + j] = ' ';
			}
			else
			{
				renderImage[offsetX + i][offsetY + j] = '#';
			}
		}
	}

	V2:

	for (int i = 0; i < ROOM_HEIGHT; i++)
	{
		for (int j = 0; j < ROOM_WIDTH; j++)
		{
			visibleTile[i][j] = false;
			int length = Engine::Distance(Point{ roomX + i, roomY + j }, container->location);
			for (int k = length - 1; k >= 0 && visibleTile[i][j] == false; k--)
			{
				double debug = Engine::LERP(roomX + i, container->location.x, k * 1.0 / length);
				int x = round(debug);
				debug = Engine::LERP(roomY + j, container->location.y, k * 1.0 / length);
				int y = round(debug); // NOT ACCURATE
				debug = k * 1.0 / length;
				if (Point{ x, y } == container->location)
				{
					continue;
				}
				bool debug2 = map->fullMap[x][y]->Passable();
				visibleTile[x % ROOM_HEIGHT][y % ROOM_WIDTH] = debug2;
				// checked[x % ROOM_HEIGHT][y % ROOM_WIDTH] = true;
				if (visibleTile[x % ROOM_HEIGHT][y % ROOM_WIDTH] == false)
				{
					break;
				}

			}

		}
	}

	V3:
	for (int i = 0; i < ROOM_HEIGHT; i++)
	{
		for (int j = 0; j < ROOM_WIDTH; j++)
		{
			visibleTile[i][j] = false;
			int length = Engine::Distance(Point{ roomX + i, roomY + j }, container->location);
			double dirX = (i - container->location.x % ROOM_HEIGHT) / (length * 1.0);
			double dirY = (j - container->location.y % ROOM_WIDTH) / (length * 1.0);
			double currentX, currentY;
			// for (double k = length - 1; k >= 0 && visibleTile[i][j] == false; k--)
			for (double k = 0; k < length; k++)
			{
				currentX = container->location.x + k * dirX;
				currentY = container->location.y + k * dirY;

				int x = round(currentX);
				int y = round(currentY);
				if (Point{ x, y } == container->location)
				{
					continue;
				}
				visibleTile[x % ROOM_HEIGHT][y % ROOM_WIDTH] = map->fullMap[x][y]->Passable();
				if (visibleTile[x % ROOM_HEIGHT][y % ROOM_WIDTH] == false)
				{
					break;
				}
			}

		}
	}

*/