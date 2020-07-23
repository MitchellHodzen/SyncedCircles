#pragma once
#include <SDL.h>
#include <cstdint>

class KTime
{
public:
	static void CalculateDeltaTime()
	{
		//If this is the first time calculating deltatime, set our initial currentFrameTime to now
		if (timerStarted == false)
		{
			Uint32 currentFrameTime = SDL_GetTicks();
			timerStarted = true;
		}

		//Calculate the time between the current frame and the last frame. Convert to seconds.
		lastFrameTimeMs = currentFrameTimeMs;
		currentFrameTimeMs = SDL_GetTicks();
		KTime::deltaTimeMs = (float)(currentFrameTimeMs - lastFrameTimeMs) / 1000;
	}

	//Get the time between the last frame and the current frame in seconds 
	static float GetDeltaTime()
	{
		return KTime::deltaTimeMs;
	}

	static uint32_t GetCurrentFrameTimeMs()
	{
		Uint32 currentFrameTime = SDL_GetTicks();
		return (uint32_t) currentFrameTime;
	}
	
private:
	KTime() {}
	static inline float deltaTimeMs = 0.0f;
	static inline Uint32 lastFrameTimeMs = 0;
	static inline Uint32 currentFrameTimeMs = 0;
	static inline bool timerStarted = false;

};