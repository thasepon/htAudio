#pragma once
#include "AudioCommand.h"

namespace htAudio {

	class StopCommand : public AudioCommand
	{
	public:
		StopCommand(OrderFormat fmt);
		~StopCommand();
		virtual bool Execute();
	private:
		bool Stop(int source);
	};

}