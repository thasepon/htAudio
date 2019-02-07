#pragma once
#include "AudioOrder.h"
#include <cstdint>

namespace htAudio
{

	class PauseOrder : public AudioOrder
	{
	public:
		~PauseOrder();

		static void SetPauseOrder(uint16_t source);
		static void SetPauseOrder(uint16_t source, double latency);

	};

}