#include "PlayOrder.h"
#include"AudioData.h"
#include"AudioManager.h"
#include"Singleton.h"

namespace htAudio
{
	PlayOrder::~PlayOrder()
	{

	}

	void PlayOrder::SetPlayOrder(uint16_t source)
	{
		OrderFormat fmt = { source , 0};
		Singleton<AudioManager>::get_Instance()->SetAudioOrder(ORDERTYPE::PLAY,fmt);
	}

	void PlayOrder::SetPlayOrder(uint16_t source, double latency)
	{
		OrderFormat fmt = { source , latency };
		Singleton<AudioManager>::get_Instance()->SetAudioOrder(ORDERTYPE::PLAY, fmt);
	}


}