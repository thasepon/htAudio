#pragma once
#include "AudioCommand.h"

namespace htAudio
{
	class SetBufCommand : public AudioCommand
	{
	public:
		~SetBufCommand();
		virtual bool Execute(int bufNumb, int channel, void* bufdata, int fq, int bufsize) { return SetDataBuffer(bufNumb, channel, bufdata, fq, bufsize); }
	private:
		bool SetDataBuffer(int bufNumb, int channel, void* bufdata, int fq, int bufsize);
	};

}