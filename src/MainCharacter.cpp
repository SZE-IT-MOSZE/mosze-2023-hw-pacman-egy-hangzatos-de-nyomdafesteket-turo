#ifndef MAIN_CHARACTER
#define MAIN_CHARACTER

#include "MainCharacter.hpp"

MainCharacter::MainCharacter() : GameObject()
{
	Init();
}

MainCharacter::MainCharacter(Engine* e) : GameObject(e)
{
	Init();
}

MainCharacter::MainCharacter(Engine* e, Point position) : GameObject(e, position)
{
	Init();
}

MainCharacter::~MainCharacter()
{
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		delete inventory[i];
	}
	delete[] inventory;
}

void MainCharacter::FirstUpdate()
{
}

int MainCharacter::Update()
{
	switch (KeyInput::GetActiveKeys()[0])
	{
		case KeyInput::KeyName::LeftArrow: StepLeft(); break;
		case KeyInput::KeyName::UpArrow: StepUp(); break;
		case KeyInput::KeyName::RightArrow: StepRight(); break;
		case KeyInput::KeyName::DownArrow: StepDown(); break;
		default: break;
	}
	return 0;
}

void MainCharacter::LastUpdate()
{
}

void MainCharacter::Init()
{
	inventory = new GameItem * [INVENTORY_SIZE];
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		inventory[i] = nullptr;
	}
}



#endif // !MAIN_CHARACTER