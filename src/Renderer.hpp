#ifndef RENDERER_H
#define RENDERER_H

#define SCREEN_NUMBER 4
#define TOP_LEFT 0
#define TOP_RIGHT 1
#define BOTTOM_LEFT 2
#define BOTTOM_Right 3

#define SCREEN_WIDTH 156
#define SCREEN_HEIGHT 40

#define RENDER_WIDTH SCREEN_WIDTH / 2
#define RENDER_HEIGHT SCREEN_HEIGHT / 2

#include "MainCharacter.hpp"
#include "Engine.hpp"
#include <iostream>
#include <cstdlib>


class Renderer // : public IUpdateable
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

	//int Update();

	//void FirstUpdate() { }

	//void LastUpdate() { }

	bool StartDispayling(IRenderImage* target);

	bool StartDispayling(IRenderImage* target, int index);

	bool StopDispayling(IRenderImage* target);

	MainCharacter* mainCharacter;

	void DebugDisplay();
	
	void Display();

	void DisplayLogicScreen(int index, int offsetX, int offsetY);

	void PositionCursor(Point location); // SetConsoleCursorPosition() is already defined in consoleapi2.h

private:
	void DisplayScreen(int index);
	static Renderer* rendererPtr;
	IRenderImage** renderPanels;
	Renderer();

};

Renderer* Renderer::rendererPtr = nullptr;
Engine* Renderer::engine = nullptr;

#endif