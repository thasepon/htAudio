#include "StopOrder.h"
#include"AudioData.h"
#include"AudioManager.h"
#include"Singleton.h"

namespace htAudio
{
	StopOrder::~StopOrder()
	{
	}

	void StopOrder::SetStopOrder( uint16_t source)
	{
		OrderFormat fmt = { source , 0 };
		Singleton<AudioManager>::get_Instance().SetAudioOrder(ORDERTYPE::STOP, fmt);
	}

	void StopOrder::SetStopOrder( uint16_t source, double latency)
	{
		OrderFormat fmt = { source , latency };
		Singleton<AudioManager>::get_Instance().SetAudioOrder(ORDERTYPE::STOP, fmt);
	}

}