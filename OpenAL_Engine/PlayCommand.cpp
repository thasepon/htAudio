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

		Play(OrderFmt.SourceID);

		return true;
	}

	/// <summary>
	/// 再生オーディオの再生
	/// </summary>
	/// <param name="source"></param>
	/// <returns></returns>
	bool PlayCommand::Play(int source)
	{
		if (alIsSource(source) == false)
		{
			printf("%d ソースが有効ではありません。\n", source);
			return false;
		}

		ALuint _source = (ALuint)source;
		alSourcePlay(_source);

		printf("%d を再生します。\n", source);

		return true;
	}

}