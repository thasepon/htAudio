#pragma once
#include "AudioOrder.h"
#include <cstdint>

namespace htAudio
{

	class StopOrder : public AudioOrder
	{
	public:
		~StopOrder();
		static void SetStopOrder( uint16_t source);
		static void SetStopOrder( uint16_t source, double latency);

	};

}