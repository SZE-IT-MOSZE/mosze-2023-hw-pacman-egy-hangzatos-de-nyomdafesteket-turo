#ifndef MAIN_CHARACTER_H
#define MAIN_CHARACTER_H

#include "GameObject.hpp"
#include "GameItem.hpp"
#include "Engine.hpp"

#define INVENTORY_SIZE 12

/// <summary>
/// The main character
/// </summary>
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
	GameItem** inventory;
protected:
	virtual void Init() override;
};

#endif
