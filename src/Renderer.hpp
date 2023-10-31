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

	/// <summary>
	/// Access the pointer to this singleton object
	/// </summary>
	/// <returns>The pointer to thi objects</returns>
	static Renderer* GetInstance();

	~Renderer();
	static Engine* engine; // qol pointer to reduce acces time
private:
	static Renderer* rendererPtr;
	Renderer();

};

Renderer* Renderer::rendererPtr = nullptr;
Engine* Renderer::engine = nullptr;

#endif