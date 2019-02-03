#pragma once
#include "AudioOrder.h"
#include"AudioManager.h"

namespace htAudio
{

	class StopOrder : public AudioOrder
	{
	public:
		~StopOrder();
		static void SetStopOrder(AudioManager* ptr, uint16_t source);
		static void SetStopOrder(AudioManager* ptr, uint16_t source, double latency);

	};

}