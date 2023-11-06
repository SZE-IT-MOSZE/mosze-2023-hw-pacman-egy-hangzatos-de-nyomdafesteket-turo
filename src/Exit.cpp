#include "Exit.hpp"

Exit::Exit() : GameObject()
{
}

Exit::Exit(Engine* e) : GameObject(e)
{
}

Exit::Exit(Engine* e, Point position) : GameObject(e, position)
{
	
}

Exit::~Exit()
{
}

void Exit::FirstUpdate()
{
	
}

int Exit::Update()
{
	float distance = Engine::Distance(engine->mainCharacter->location, this->location);
	if (distance <= WIN_DISTANCE)
	{
		engine->WinGame();
	}
	return 0;
}

void Exit::LastUpdate()
{

}
