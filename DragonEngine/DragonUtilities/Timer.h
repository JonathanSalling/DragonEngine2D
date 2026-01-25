#pragma once
#include <chrono>

namespace DragonUtilities
{
	class Timer
	{
	public:
		Timer();
		Timer(const Timer& aTimer) = delete; // i do not understand what is deleted here or why
		Timer& operator=(const Timer& aTimer) = delete; // i do not understand what is deleted here or why
		void Update();
		float GetDeltaTime() const;
		double GetTotalTime() const;

	private:
		std::chrono::steady_clock::time_point myProgramStartTimer;
		std::chrono::duration<float> myUpdateTime;
		std::chrono::duration<double> myTotalTime;

		std::chrono::steady_clock::time_point myPreviousFrame;
		std::chrono::steady_clock::time_point myCurrentFrame;
	};
}

