#include "pch.h"
#include "Timer.h"

DragonUtilities::Timer::Timer()
{
	myProgramStartTimer = std::chrono::steady_clock::now();
	myPreviousFrame = std::chrono::steady_clock::now();
	myUpdateTime = std::chrono::seconds(0);
	myTotalTime = std::chrono::seconds(0);
}

void DragonUtilities::Timer::Update()
{
	myCurrentFrame = std::chrono::steady_clock::now();
	myUpdateTime = myCurrentFrame - myPreviousFrame;
	myPreviousFrame = myCurrentFrame;
	myTotalTime = myCurrentFrame - myProgramStartTimer;
}

float DragonUtilities::Timer::GetDeltaTime() const
{
	return myUpdateTime.count();
}

double DragonUtilities::Timer::GetTotalTime() const
{
	return myTotalTime.count();
}
