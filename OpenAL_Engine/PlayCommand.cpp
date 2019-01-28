#include "PlayCommand.h"

#include<AL/efx.h>

namespace htAudio {


	PlayCommand::PlayCommand(OrderFormat fmt) : AudioCommand()
	{
		OrderFmt = fmt;
	}

	PlayCommand::~PlayCommand()
	{

	}

	bool PlayCommand::Execute() 
	{ 
		if (TimeCtrlCmd() == false)
			return false;

		return Play(OrderFmt.SourceID); 
	}

	/// <summary>
	/// 再生オーディオの再生
	/// </summary>
	/// <param name="source"></param>
	/// <returns></returns>
	bool PlayCommand::Play(int source)
	{
		ALuint _source = (ALuint)source;
		alSourcePlay(_source);
		return true;
	}

}