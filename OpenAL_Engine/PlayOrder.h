#pragma once
#include"AudioOrder.h"
#include"AudioManager.h"

namespace htAudio
{
	class PlayOrder : public AudioOrder
	{
	public:
		~PlayOrder();

		static void SetOrder(AudioManager* ptr, int source);
		static void SetOrder(AudioManager* ptr, int source, int latency);

	};
}