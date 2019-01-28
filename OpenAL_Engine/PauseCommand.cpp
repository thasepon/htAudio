#include "PauseCommand.h"
#include<AL/efx.h>
#include<AL/efx-creative.h>


namespace htAudio {


	PauseCommand::PauseCommand(OrderFormat fmt) : AudioCommand()
	{
		OrderFmt = fmt;
	}

	PauseCommand::~PauseCommand()
	{
	}

	bool PauseCommand::Pause(int source)
	{

		if (TimeCtrlCmd() == false)
			return false;

		alSourcePause(source);
		return true;
	}

}