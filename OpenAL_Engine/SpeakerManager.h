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
		std::list<AudioSpeaker> SpeakerList;	// AudioSpeaker���ꊇ�ύX�������肷�鎞�Ɏg�p����list

	};

}