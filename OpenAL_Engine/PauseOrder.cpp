#include "PauseOrder.h"
#include"AudioData.h"
#include"AudioManager.h"
namespace htAudio
{

	PauseOrder::~PauseOrder()
	{
	}

	void PauseOrder::SetPauseOrder(AudioManager* ptr, uint16_t source)
	{
		OrderFormat fmt = { source , 0 };
		ptr->SetAudioOrder(ORDERTYPE::PAUSE, fmt);
	}

	void PauseOrder::SetPauseOrder(AudioManager* ptr, uint16_t source, double latency)
	{
		OrderFormat fmt = { source , latency };
		ptr->SetAudioOrder(ORDERTYPE::PAUSE, fmt);
	}

}