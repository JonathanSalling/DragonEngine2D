#pragma once
#include <chrono>

namespace DragonEngine
{
	class Timer
	{
	public:
		Timer(const Timer& aTimer) = delete;
		Timer& operator=(const Timer& aTimer) = delete;

		static void Update() { GetInstance()->UpdateImplementation(); }
		static float GetDeltaTime() { return GetInstance()->GetDeltaTimeImplementation(); }
		static double GetTotalTime() { return GetInstance()->GetTotalTimeImplementation(); }

	private:
		Timer()
		{
			myProgramStartTimer = std::chrono::steady_clock::now();
			myPreviousFrame = myProgramStartTimer;
			myCurrentFrame = myProgramStartTimer;
			myUpdateTime = std::chrono::duration<float>(0.0f);
			myTotalTime = std::chrono::duration<double>(0.0);
		}

		static Timer* GetInstance() { static Timer instance; return &instance; }

		void UpdateImplementation()
		{
			myCurrentFrame = std::chrono::steady_clock::now();
			myUpdateTime = myCurrentFrame - myPreviousFrame;
			myTotalTime = myCurrentFrame - myProgramStartTimer;
			myPreviousFrame = myCurrentFrame;
		}

		float GetDeltaTimeImplementation() const { return myUpdateTime.count(); }

		double GetTotalTimeImplementation() const { return myTotalTime.count(); }


		std::chrono::steady_clock::time_point myProgramStartTimer;
		std::chrono::duration<float> myUpdateTime;
		std::chrono::duration<double> myTotalTime;

		std::chrono::steady_clock::time_point myPreviousFrame;
		std::chrono::steady_clock::time_point myCurrentFrame;
	};
}

