#pragma once

#include<list>

#include"OpenAL\AudioSpeaker\AudioSpeaker.h"

namespace htAudio
{
	class SpeakerManager
	{
	public:
		SpeakerManager();
		~SpeakerManager();

	private:
		std::list<AudioSpeaker> SpeakerList;	// AudioSpeakerを一括変更かけたりする時に使用するlist

	};

}