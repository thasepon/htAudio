#include "PauseOrder.h"
#include"AudioData.h"
#include"AudioManager.h"
#include"Singleton.h"

namespace htAudio
{

	PauseOrder::~PauseOrder()
	{
	}

	void PauseOrder::SetPauseOrder(uint16_t source)
	{
		OrderFormat fmt = { source , 0 };
		Singleton<AudioManager>::get_Instance().SetAudioOrder(ORDERTYPE::PAUSE, fmt);
	}

	void PauseOrder::SetPauseOrder(uint16_t source, double latency)
	{
		OrderFormat fmt = { source , latency };
		Singleton<AudioManager>::get_Instance().SetAudioOrder(ORDERTYPE::PAUSE, fmt);
	}

}