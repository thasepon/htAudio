#include "PauseOrder.h"

namespace htAudio
{

	PauseOrder::~PauseOrder()
	{
	}

	void PauseOrder::SetOrder(AudioManager* ptr, int source)
	{
		OrderFormat fmt = { source , 0 };
		ptr->SetAudioOrder(ORDERTYPE::PAUSE, fmt);
	}

	void PauseOrder::SetOrder(AudioManager* ptr, int source, int latency)
	{
		OrderFormat fmt = { source , latency };
		ptr->SetAudioOrder(ORDERTYPE::PAUSE, fmt);
	}

}