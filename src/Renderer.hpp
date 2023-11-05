#ifndef RENDERER_H
#define RENDERER_H

#define SCREEN_NUMBER 4
#define TOP_LEFT 0
#define TOP_RIGHT 1
#define BOTTOM_LEFT 2
#define BOTTOM_Right 3

#include "MainCharacter.hpp"
#include "Engine.hpp"
#include <iostream>
#include <cstdlib>


class Renderer: public IUpdateable
{
public:

	void operator=(const Renderer& other) = delete;
	Renderer(const Renderer& other) = delete;


	/// <summary>
	/// Access the pointer to this singleton object
	/// </summary>
	/// <returns>The pointer to thi objects</returns>
	static Renderer* GetInstance();

	~Renderer();
	static Engine* engine; // qol pointer to reduce acces time

	int Update();

	void FirstUpdate() { }

	void LastUpdate() { }

	bool StartDispayling(IRenderImage* target);

	bool StopDispayling(IRenderImage* target);

	MainCharacter* mainCharacter;

	void DebugDisplay();

private:
	void Display(int location, int index);
	static Renderer* rendererPtr;
	IRenderImage** renderPanels;
	Renderer();

};

Renderer* Renderer::rendererPtr = nullptr;
Engine* Renderer::engine = nullptr;

#endif