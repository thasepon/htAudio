#include "ChronoTimer.h"

namespace htAudio {

	ChronoTimer::ChronoTimer()
	{
		StartTime = std::chrono::system_clock::now();
	}


	ChronoTimer::~ChronoTimer()
	{
	}

	double ChronoTimer::GetElapsedTime()
	{
		IntervalTime = std::chrono::system_clock::now();
		return std::chrono::duration_cast<std::chrono::seconds>(IntervalTime - StartTime).count();
	}

}