#pragma once
#include<chrono>

namespace htAudio {

	class ChronoTimer
	{
	public:
		ChronoTimer();
		~ChronoTimer();

		double GetElapsedTime();

	private:
		std::chrono::system_clock::time_point StartTime,IntervalTime;

	};

}