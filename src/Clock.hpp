#ifndef CLOCK_H
#define CLOCK_H

#define FRAMERATE 20	// 1000 / framerate = time for computation
						// 20: 50 ms
						// 40: 25 ms
						// 60: 16 ms

#include <iostream>
#include <chrono>
#include <ctime> 


// Update order: gameobjects; renderer; clock->Wait();

class Clock
{
public:
	Clock();
	~Clock();

	/// <summary>
	/// Time since the Wait() call
	/// </summary>
	/// <returns>Time since the Wait() call in miliseconds</returns>
	long unsigned int DeltaTimeMs();

	/// <summary>
	/// Sleeps for a certain amount of time
	/// </summary>
	/// <param name="framerate">Frames per second</param>
	void Wait(int framerate = FRAMERATE);

	/// <summary>
	/// Time since the Start() was called
	/// </summary>
	/// <returns>Time since the Start() was called in miliseconds</returns>
	long unsigned int TotalTime();

	/// <summary>
	/// Start the timer
	/// </summary>
	void Start();

	/// <summary>
	/// Stop the timer
	/// </summary>
	void Stop();

private:
	long unsigned int start; // time of starting the clock
	long unsigned int previousTime; // time at the previous Wait() call before Sleep() was called

	
};



#endif // !CLOCK_H