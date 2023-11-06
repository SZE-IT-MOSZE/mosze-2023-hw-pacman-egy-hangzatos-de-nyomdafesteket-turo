#ifndef RENDERER
#define RENDERER

#include "Renderer.hpp"


Renderer* Renderer::GetInstance()
{
	if (rendererPtr == nullptr)
	{
		rendererPtr = new Renderer();
	}
	return rendererPtr;
}



Renderer::~Renderer()
{
	delete[] renderPanels;
}

int Renderer::Update()
{
	for (int i = 0; i < SCREEN_NUMBER; i++)
	{
		if (renderPanels[i] != nullptr)
		{
			Display(i, i);
		}
	}
	return 0;
}

bool Renderer::StartDispayling(IRenderImage* target)
{
	for (int i = 0; i < SCREEN_NUMBER; i++)
	{
		if (renderPanels[i] == nullptr)
		{
			renderPanels[i] = target;
			return true;
		}
	}
	return false;
}

bool Renderer::StopDispayling(IRenderImage* target)
{
	for (int i = 0; i < SCREEN_NUMBER; i++)
	{
		if (renderPanels[i] == target)
		{
			renderPanels[i] = nullptr;
			return true;
		}
	}
	return false;
}

void Renderer::DebugDisplay()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,0 });


	int roomX = mainCharacter->location.x - mainCharacter->location.x % ROOM_HEIGHT;
	int roomY = mainCharacter->location.y - mainCharacter->location.y % ROOM_WIDTH;
	// SetCursorPos(0, 0);
	for (int i = roomX; i < roomX + ROOM_HEIGHT; i++)
	{
		for (int j = roomY; j < roomY + ROOM_WIDTH; j++)
		{
			if (engine->GetMap()->fullMap[i][j]->content == mainCharacter)
			{
				std::cout << 'M';
				continue;
			}
			int k;
			for (k = 0; k < EXITCOUNT; k++)
			{
				if (engine->GetMap()->fullMap[i][j]->content == engine->exits[k])
				{
					std::cout << 'E';
					break;
				}
			}
			if (engine->GetMap()->fullMap[i][j]->content != nullptr && (k >= EXITCOUNT))
			{
				std::cout << 'O';
				continue;
			}
			else 
			{
				std::cout << engine->GetMap()->fullMap[i][j]->GetIcon();
			}

		}
		std::cout << std::endl;
	}
}

void Renderer::Display(int location, int index)
{

}

Renderer::Renderer()
{
	renderPanels = new IRenderImage * [SCREEN_NUMBER];
	// engine = Engine::GetInstance(); // Causes self calling loop
}



#endif