#include "StopOrder.h"

namespace htAudio
{
	StopOrder::~StopOrder()
	{
	}

	void StopOrder::SetOrder(AudioManager* ptr, int source)
	{
		OrderFormat fmt = { source , 0 };
		ptr->SetAudioOrder(ORDERTYPE::STOP, fmt);
	}

	void StopOrder::SetOrder(AudioManager* ptr, int source, int latency)
	{
		OrderFormat fmt = { source , latency };
		ptr->SetAudioOrder(ORDERTYPE::STOP, fmt);
	}

}