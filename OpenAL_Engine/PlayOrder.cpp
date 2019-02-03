#include "PlayOrder.h"
#include"AudioData.h"
#include"AudioManager.h"

namespace htAudio
{
	PlayOrder::~PlayOrder()
	{

	}

	void PlayOrder::SetPlayOrder(AudioManager* ptr, uint16_t source)
	{
		OrderFormat fmt = { source , 0};
		ptr->SetAudioOrder(ORDERTYPE::PLAY,fmt);
	}

	void PlayOrder::SetPlayOrder(AudioManager* ptr, uint16_t source, double latency)
	{
		OrderFormat fmt = { source , latency };
		ptr->SetAudioOrder(ORDERTYPE::PLAY, fmt);
	}


}