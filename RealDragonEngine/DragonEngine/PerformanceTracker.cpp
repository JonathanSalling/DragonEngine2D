#include "PerformanceTracker.h"
#include <SDL3/SDL.h>

DragonEngine::PerformanceTracker::PerformanceTracker()
{
	myLastFrameTime = SDL_GetPerformanceCounter();
	myLastReportTime = myLastFrameTime;

	myAccumulatedFrameTime = 0.0;
	myFrameCount = 0;
}

void DragonEngine::PerformanceTracker::Update()
{
	const unsigned long long currentTime = SDL_GetPerformanceCounter();

	const unsigned long long frameTicks = currentTime - myLastFrameTime;

	const double frameTime = (double)frameTicks / (double)SDL_GetPerformanceFrequency() * 1000.0;

	myLastFrameTime = currentTime;

	myAccumulatedFrameTime += frameTime;
	myFrameCount++;

	const double reportTime = (double)(currentTime - myLastReportTime) / (double)SDL_GetPerformanceFrequency();

	if (reportTime >= 1.0)
	{
		PrintStatistics();

		myAccumulatedFrameTime = 0.0;
		myFrameCount = 0;
		myLastReportTime = currentTime;
	}
}

void DragonEngine::PerformanceTracker::PrintStatistics() const
{
	if (myFrameCount <= 0)
	{
		return;
	}

	const double averageFrameTime = myAccumulatedFrameTime / myFrameCount;

	const double averageFps = 1000.0 / averageFrameTime;

	SDL_Log("FPS: %.1f | Frame Time: %.2f ms", averageFps, averageFrameTime);
}