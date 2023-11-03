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

void Renderer::Display(int location, int index)
{

}

Renderer::Renderer()
{
	renderPanels = new IRenderImage * [SCREEN_NUMBER];
	// engine = Engine::GetInstance(); // Causes self calling loop
}



#endif