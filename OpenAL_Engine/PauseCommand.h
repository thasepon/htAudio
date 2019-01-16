#pragma once
#include "AudioCommand.h"

namespace htAudio {

	class PauseCommand : public AudioCommand
	{
	public:
		PauseCommand(OrderFormat fmt);
		~PauseCommand();
		virtual bool Execute() { return Pause(OrderFmt.SourceID); }

	private:
		bool Pause(int source);
	};

}