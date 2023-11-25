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

	long unsigned int GetTotalFrames() { return frameCount; }

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