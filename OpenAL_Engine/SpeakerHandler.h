#pragma once
#include"AudioData.h"
#include"AudioCommand.h"

namespace htAudio {

	class SpeakerHandler
	{
	public:
		SpeakerHandler();
		~SpeakerHandler();

		AudioCommand* ExcuteHandle(COMMANDNUM cmd,int source);

	private:

	};

}