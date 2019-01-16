#include "PauseCommand.h"
#include<AL/efx.h>
#include<AL/efx-creative.h>


namespace htAudio {


	PauseCommand::PauseCommand(OrderFormat fmt)
	{
		OrderFmt = fmt;
	}

	PauseCommand::~PauseCommand()
	{
	}

	bool PauseCommand::Pause(int source)
	{
		alSourcePause(source);
		return true;
	}

}