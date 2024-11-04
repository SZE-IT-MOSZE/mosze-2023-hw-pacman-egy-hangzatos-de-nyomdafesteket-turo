#ifndef RENDERER_H
#define RENDERER_H

#define SCREEN_NUMBER 4
#define TOP_LEFT 0
#define TOP_RIGHT 1
#define BOTTOM_LEFT 2
#define BOTTOM_Right 3

#define SCREEN_WIDTH 154
#define SCREEN_HEIGHT 40

#define RENDER_WIDTH (SCREEN_WIDTH / 2)
#define RENDER_HEIGHT (SCREEN_HEIGHT / 2)

#include "MainCharacter.hpp"
#include "Engine.hpp"
#include <iostream>
#include <cstdlib>

/// <summary>
/// The handler of output
/// </summary>
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

	/// <summary>
	/// Start displaying an IRenderImage screen on one of the virtual screens
	/// </summary>
	/// <param name="target">What should be displayed</param>
	/// <returns>If the displaying is started</returns>
	bool StartDispayling(IRenderImage* target);

	/// <summary>
	/// Start displaying an IRenderImage screen on one of the virtual screens
	/// </summary>
	/// <param name="target">What should be displayed</param>
	/// <param name="index">The index of the virtual screen, where the image should appear</param>
	/// <returns>If the displaying is started</returns>
	bool StartDispayling(IRenderImage* target, int index);

	/// <summary>
	/// Stops displaying an IRenderImage screen on one of the virtual screens
	/// </summary>
	/// <param name="target">What should not be displayed</param>
	/// <returns>If the screen was in fact, being displayed</returns>
	bool StopDispayling(IRenderImage* target);

	MainCharacter* mainCharacter;

	void DebugDisplay();
	
	/// <summary>
	/// Displays all the virtual screens
	/// </summary>
	void Display();
	
	/// <summary>
	/// Displays one of the screens on the window
	/// </summary>
	/// <param name="index">The index of the IRenderImage</param>
	/// <param name="offsetX">Offset in the horizontal direction</param>
	/// <param name="offsetY">Offset in the vertical direction</param>
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