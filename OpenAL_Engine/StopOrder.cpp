#include "StopOrder.h"
#include"AudioData.h"
#include"AudioManager.h"

namespace htAudio
{
	StopOrder::~StopOrder()
	{
	}

	void StopOrder::SetStopOrder(AudioManager* ptr, uint16_t source)
	{
		OrderFormat fmt = { source , 0 };
		ptr->SetAudioOrder(ORDERTYPE::STOP, fmt);
	}

	void StopOrder::SetStopOrder(AudioManager* ptr, uint16_t source, double latency)
	{
		OrderFormat fmt = { source , latency };
		ptr->SetAudioOrder(ORDERTYPE::STOP, fmt);
	}

}