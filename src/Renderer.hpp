#ifndef RENDERER_H
#define RENDERER_H

#include "Engine.hpp"
#include <iostream>
#include <cstdlib>

class Renderer
{
public:

	void operator=(const Renderer& other) = delete;
	Renderer(const Renderer& other) = delete;
	static int Display(int roomSpec);
	static Renderer* GetInstance();
	~Renderer();
	static Engine* engine;
private:
	static Renderer* rendererPtr;
	Renderer();

};



#endif