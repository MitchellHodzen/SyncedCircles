#pragma once
#include <cstdint>
#include "KTime.h"

class Timer
{
public:

	void Restart()
	{
		Restart(0);
	}

	void Restart(uint32_t initialOffsetMs)
	{
		//Initial offset is how "late" the timer was started
		startTimeMs = KTime::GetCurrentFrameTimeMs() - initialOffsetMs;
	}

	uint32_t GetTimeElapsedMs()
	{

		if (startTimeMs == 0)
		{
			//If this is the first time getting the time elapsed, set it to the current frame time
			Restart();
		}
		//Get the current frame time
		uint32_t currentFrameTimeMs = KTime::GetCurrentFrameTimeMs();

		//Calculate the time elapsed since the timer was started
		uint32_t timeElapsedMs = currentFrameTimeMs - startTimeMs;

		return timeElapsedMs;
	}


private:
	uint32_t startTimeMs = 0;
};