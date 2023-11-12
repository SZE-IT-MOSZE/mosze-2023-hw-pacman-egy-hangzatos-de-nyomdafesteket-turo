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

//int Renderer::Update()
//{
//	for (int i = 0; i < SCREEN_NUMBER; i++)
//	{
//		if (renderPanels[i] != nullptr)
//		{
//			Display(i, i);
//		}
//	}
//	return 0;
//}

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

bool Renderer::StartDispayling(IRenderImage* target, int index)
{
	if (renderPanels[index] == nullptr)
	{
		renderPanels[index] = target;
		return true;
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
	PositionCursor(Point{ 0, 0 });
	int roomX = mainCharacter->location.x - mainCharacter->location.x % ROOM_HEIGHT;
	int roomY = mainCharacter->location.y - mainCharacter->location.y % ROOM_WIDTH;
	// SetCursorPos(0, 0);
	for (int i = roomX; i < roomX + ROOM_HEIGHT; i++)
	{
		for (int j = roomY; j < roomY + ROOM_WIDTH; j++)
		{
			if (engine->GetMap()->fullMap[i][j]->GetContent() == mainCharacter)
			{
				std::cout << 'M';
				continue;
			}
			bool exit = false;
			for (int k = 0; k < EXIT_COUNT; k++)
			{
				if (engine->GetMap()->fullMap[i][j]->GetContent() == engine->exits[k])
				{
					std::cout << 'E';
					exit = true;
					break;
				}
			}
			if (exit)
			{
				continue;
			}
			if (engine->GetMap()->fullMap[i][j]->GetContent() != nullptr)
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

void Renderer::Display()
{
	for (int i = 0; i < SCREEN_NUMBER; i++)
	{
		if (renderPanels[i] != nullptr)
		{
			DisplayScreen(i);
		}
	}
}

void Renderer::DisplayLogicScreen(int index, int offsetX, int offsetY)
{
	char** tmp = (renderPanels[index])->ProduceImage();
	for (int i = 0; i < RENDER_HEIGHT; i++)
	{
		PositionCursor(Point{ offsetY, offsetX + i});
		for (int j = 0; j < RENDER_WIDTH; j++)
		{
			std::cout << tmp[i][j];
		}
	}
}

void Renderer::PositionCursor(Point location)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ (short)location.x, (short)location.y });
}

void Renderer::DisplayScreen(int index)
{
	switch (index)
	{
	case TOP_LEFT: DisplayLogicScreen(index, 0, 0); break;
	case TOP_RIGHT: DisplayLogicScreen(index, 0, RENDER_WIDTH + 1); break;
	case BOTTOM_LEFT: DisplayLogicScreen(index, 0, RENDER_HEIGHT); break;
	case BOTTOM_Right: DisplayLogicScreen(index, RENDER_WIDTH, RENDER_HEIGHT); break;

	default: break;
	}
}

Renderer::Renderer()
{
	renderPanels = new IRenderImage * [SCREEN_NUMBER];
	for (int i = 0; i < SCREEN_NUMBER; i++)
	{
		renderPanels[i] = nullptr;
	}
	// engine = Engine::GetInstance(); // Causes self calling loop
}



#endif