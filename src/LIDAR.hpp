#ifndef LIDAR_H
#define LIDAR_H

#include "Engine.hpp"

#define LIDAR_PRECISION 0.1

class LIDAR :  public IRenderImage, public GameItem
{
public:
	LIDAR(GameObject* container, Map* map);
	~LIDAR();
	char** ProduceImage() override;

	bool Condition() override;
	void Trigger() override;

private:
	char** renderImage;
	bool** visibleTile;
	int range;
};



#endif // !LIDAR_H
