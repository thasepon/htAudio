#pragma once
#include"AudioOrder.h"
#include <cstdint>

namespace htAudio
{
	class PlayOrder : public AudioOrder
	{
	public:
		~PlayOrder();
		static void SetPlayOrder(uint16_t source);
		static void SetPlayOrder(uint16_t source, double latency);

	};
}