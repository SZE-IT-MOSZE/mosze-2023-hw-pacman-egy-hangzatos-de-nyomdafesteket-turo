#ifndef MAIN_CHARACTER
#define MAIN_CHARACTER

#include "MainCharacter.hpp"

MainCharacter::MainCharacter() : GameObject()
{

}

MainCharacter::MainCharacter(Engine* e) : GameObject(e)
{
	
}

MainCharacter::MainCharacter(Engine* e, Point position) : GameObject(e, position)
{

}

MainCharacter::~MainCharacter()
{
	
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



#endif // !MAIN_CHARACTER