#pragma once
#include"AudioManager.h"


namespace htAudio
{
	class AudioOrder
	{
	public:
		~AudioOrder();
		static void SetOrder(AudioManager* ptr, int source) {};
		static void SetOrder(AudioManager* ptr, int source, int latency) {};

	private:
	};

}