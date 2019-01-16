#pragma once
#include"AudioData.h"

namespace htAudio
{

	class AudioCommand
	{
	public:
		virtual ~AudioCommand() {}
		virtual bool Execute() {}

	protected:
		OrderFormat OrderFmt;

	};

}