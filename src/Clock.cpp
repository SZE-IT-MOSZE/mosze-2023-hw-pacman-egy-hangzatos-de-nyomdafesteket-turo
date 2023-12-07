#ifndef CLOCK
#define CLOCK

#include "Clock.hpp"

// TODO



Clock::Clock()
{
	frameCount = 0;
	previousTime = 0;
}

Clock::~Clock()
{
}

void Clock::Wait(int framerate)
{
	++frameCount;
	long unsigned int delta = GetTimeSinceEpoch() - previousTime;
	int sleep = 1000 / framerate - delta;
	if (sleep < 0)
	{
		sleep = 0;
	}
	Sleep(sleep);
	previousTime = GetTimeSinceEpoch();
}

long unsigned int Clock::GetTimeSinceEpoch()
{
	auto currentTime = std::chrono::system_clock::now();
	auto duration = currentTime.time_since_epoch();
	return static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());
}

void Clock::Start()
{
	previousTime = GetTimeSinceEpoch();
}


#endif // !CLOCK