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
		std::list<AudioSpeaker> SpeakerList;	// AudioSpeaker‚ğˆêŠ‡•ÏX‚©‚¯‚½‚è‚·‚é‚Ég—p‚·‚élist

	};

}