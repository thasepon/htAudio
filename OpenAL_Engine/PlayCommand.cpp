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

		//Play(OrderFmt.SourceID);

		ALuint _source = (ALuint)OrderFmt.SourceID;
		alSourcePlay(_source);

		return true;
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