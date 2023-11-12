#ifndef LIDAR_H
#define LIDAR_H

#include "Engine.hpp"

class LIDAR :  public IRenderImage, public GameItem
{
public:
	LIDAR(GameObject* container, Map* map);
	~LIDAR();
	char** ProduceImage() override;

	bool Condition() override;
	void Trigger() override;
	// static bool LineOfSight(Point p1, Point p2);
private:
	char** renderImage;
	bool** visibleTile;
};



#endif // !LIDAR_H
