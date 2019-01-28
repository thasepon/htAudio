#pragma once
#include"AudioData.h"
#include"ChronoTimer.h"

namespace htAudio
{
	class AudioCommand
	{
	public:
		virtual ~AudioCommand() {}
		virtual bool Execute() {}

	protected:
		AudioCommand();
		virtual bool TimeCtrlCmd();

		OrderFormat OrderFmt;
		ChronoTimer* Timer;

	};

}