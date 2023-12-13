#ifndef LIDAR_H
#define LIDAR_H

#include "Engine.hpp"

/// <summary>
/// Lidar, creating a 2D map of the surroundings of the player
/// </summary>
class LIDAR : public IRenderImage, public GameItem
{
public:
	LIDAR(GameObject* container, Map* map);
	~LIDAR();

	bool IsUpdateable() override;
	char** ProduceImage() override;

	bool Condition() override;
	void Trigger() override;
	// static bool LineOfSight(Point p1, Point p2);
private:
	char** renderImage;
	bool** visibleTile;
};



#endif // !LIDAR_H
