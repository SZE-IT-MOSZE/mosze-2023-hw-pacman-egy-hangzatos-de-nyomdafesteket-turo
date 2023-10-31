#ifndef RENDERER
#define RENDERER

#include "Renderer.hpp"


int Renderer::Display(int roomSpec)
{
	return 0;
}

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
}

Renderer::Renderer()
{
	// engine = Engine::GetInstance(); // Causes self calling loop
}



#endif