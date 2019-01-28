#include"AudioCommand.h"

namespace htAudio
{

	bool AudioCommand::TimeCtrlCmd()
	{
		if (OrderFmt.Latency >= Timer->GetElapsedTime())
			return false;
		else
			return true;
	}

	AudioCommand::AudioCommand()
	{
		Timer = new ChronoTimer();
	}

}