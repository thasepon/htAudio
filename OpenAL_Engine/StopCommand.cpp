#include "StopCommand.h"
#include<AL/efx.h>
#include<AL/efx-creative.h>

namespace htAudio {


	StopCommand::StopCommand(OrderFormat fmt) : AudioCommand()
	{
		OrderFmt = fmt;
	}

	StopCommand::~StopCommand()
	{
	}

	bool StopCommand::Execute()
	{
		if (TimeCtrlCmd() == false)
			return false;

		return Stop(OrderFmt.SourceID);
	}

	bool StopCommand::Stop(int source)
	{
		alSourceStop(source);

		return true;
	}

}