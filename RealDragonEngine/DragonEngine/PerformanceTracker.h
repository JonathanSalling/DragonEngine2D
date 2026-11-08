#pragma once

namespace DragonEngine
{
	class PerformanceTracker
	{
	public:
		PerformanceTracker();

		void Update();

	private:
		void PrintStatistics() const;

		unsigned long long myLastFrameTime;
		unsigned long long myLastReportTime;

		double myAccumulatedFrameTime;
		int myFrameCount;
	};
}
