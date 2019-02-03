#pragma once
#include"AudioOrder.h"
#include"AudioManager.h"

namespace htAudio
{
	class PlayOrder : public AudioOrder
	{
	public:
		~PlayOrder();
		static void SetPlayOrder(AudioManager* ptr, uint16_t source);
		static void SetPlayOrder(AudioManager* ptr, uint16_t source, double latency);

	};
}