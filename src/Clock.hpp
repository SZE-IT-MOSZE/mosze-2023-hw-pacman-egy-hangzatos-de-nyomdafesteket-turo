#ifndef CLOCK_H
#define CLOCK_H

#define FRAMERATE 5	/* 1000 / framerate = time for computation */
// 20: 50 ms
// 40: 25 ms
// 60: 16 ms

#include <iostream>
#include <chrono>
#include <ctime>
#include <windows.h>


// Update order: gameobjects; renderer; clock->Wait();

class Clock
{
public:
	Clock();
	~Clock();

	/// <summary>
	/// Sleeps for a certain amount of time
	/// </summary>
	/// <param name="framerate">Frames per second</param>
	void Wait(int framerate = FRAMERATE);

	/// <summary>
	/// Get the amount of frames since Start()
	/// </summary>
	/// <returns>The amount of frames since Start()</returns>
	long unsigned int GetTotalFrames() { return frameCount; }

	/// <summary>
	/// Get the time at the previous Wait() call
	/// </summary>
	/// <returns>The time at the previous Wait() call</returns>
	long unsigned int GetPreviousTime() { return previousTime; }

	long unsigned int GetTimeSinceEpoch();

	/// <summary>
	/// Start the timer
	/// </summary>
	void Start();

private:
	long unsigned int previousTime; // time at the previous Wait() was called
	long unsigned int frameCount;

};



#endif // !CLOCK_H