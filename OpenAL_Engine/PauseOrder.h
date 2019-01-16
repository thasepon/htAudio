#pragma once
#include "AudioOrder.h"

namespace htAudio
{

	class PauseOrder : public AudioOrder
	{
	public:
		~PauseOrder();

		static void SetOrder(AudioManager* ptr, int source);
		static void SetOrder(AudioManager* ptr, int source, int latency);

	};

}