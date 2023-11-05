#ifndef MAIN_CHARACTER_H
#define MAIN_CHARACTER_H

#include "GameObject.hpp"
#include "Engine.hpp"

class MainCharacter : public GameObject
{
public: 
	MainCharacter();
	MainCharacter(Engine* e);
	MainCharacter(Engine* e, Point position);
	~MainCharacter();

	void FirstUpdate() override;
	int Update() override;
	void LastUpdate() override;
};

#endif
