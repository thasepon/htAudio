#include "PlayOrder.h"
#include"AudioData.h"

namespace htAudio
{
	PlayOrder::~PlayOrder()
	{

	}

	void PlayOrder::SetOrder(AudioManager* ptr, int source)
	{
		OrderFormat fmt = { source , 0};
		ptr->SetAudioOrder(ORDERTYPE::PLAY,fmt);
	}

	void PlayOrder::SetOrder(AudioManager* ptr, int source, int latency)
	{
		OrderFormat fmt = { source , latency };
		ptr->SetAudioOrder(ORDERTYPE::PLAY, fmt);
	}


}