#ifndef EXIT_H
#define EXIT_H

#define WIN_DISTANCE 3.0

#include "Engine.hpp"

/// <summary>
/// The objective of the game
/// </summary>
class Exit : public GameObject
{
public:
	Exit();
	Exit(Engine* e);
	Exit(Engine* e, Point position);
	~Exit();

	void FirstUpdate() override;
	int Update() override;
	void LastUpdate() override;
protected:
	virtual void Init() override;
};



#endif