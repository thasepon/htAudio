#include "StopCommand.h"
#include<AL/efx.h>
#include<AL/efx-creative.h>

namespace htAudio {


	StopCommand::StopCommand(OrderFormat fmt)
	{
		OrderFmt = fmt;
	}

	StopCommand::~StopCommand()
	{
	}

	bool StopCommand::Execute()
	{
		return Stop(OrderFmt.SourceID);
	}

	bool StopCommand::Stop(int source)
	{
		alSourceStop(source);

		return true;
	}

}