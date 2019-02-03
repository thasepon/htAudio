#pragma once
#include "AudioOrder.h"
#include"AudioManager.h"

namespace htAudio
{

	class PauseOrder : public AudioOrder
	{
	public:
		~PauseOrder();

		static void SetPauseOrder(AudioManager* ptr, uint16_t source);
		static void SetPauseOrder(AudioManager* ptr, uint16_t source, double latency);

	};

}