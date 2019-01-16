#pragma once
#include "AudioOrder.h"

namespace htAudio
{

	class StopOrder : public AudioOrder
	{
	public:
		~StopOrder();

		static void SetOrder(AudioManager* ptr, int source);
		static void SetOrder(AudioManager* ptr, int source, int latency);

	};

}